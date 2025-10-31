#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>

namespace fs = std::filesystem;

class HTMLAccessibilityRepair {
public:
    static bool processFile(const std::string& filename) {
        // Read entire file
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Cannot open file " << filename << std::endl;
            return false;
        }
        
        std::string content((std::istreambuf_iterator<char>(file)),
                           std::istreambuf_iterator<char>());
        file.close();
        
        // Process content
        std::string processed = repairHTML(content);
        
        // Write back
        std::ofstream outfile(filename);
        if (!outfile.is_open()) {
            std::cerr << "Error: Cannot write to file " << filename << std::endl;
            return false;
        }
        
        outfile << processed;
        outfile.close();
        return true;
    }

private:
    static std::string repairHTML(const std::string& content) {
        std::string result;
        result.reserve(content.size() + 2000); // Reserve extra space
        
        size_t pos = 0;
        size_t len = content.size();
        
        while (pos < len) {
            // 1. Remove cellspacing="0"
            if (caseInsensitiveCompare(content, pos, "cellspacing=\"0\"")) {
                pos += 15;
                continue;
            }
            
            // 2. Remove valign="..." (any value)
            if (caseInsensitiveCompare(content, pos, "valign=")) {
                size_t end = findAttributeEnd(content, pos + 7);
                if (end != std::string::npos) {
                    pos = end;
                    continue;
                }
            }
            
            // 3. Remove align="..." (any value)
            if (caseInsensitiveCompare(content, pos, "align=")) {
                size_t end = findAttributeEnd(content, pos + 6);
                if (end != std::string::npos) {
                    pos = end;
                    continue;
                }
            }
            
            // 4. Add <th></th> after <table>
            if (caseInsensitiveCompare(content, pos, "<table")) {
                size_t tableEnd = findTagEnd(content, pos);
                if (tableEnd != std::string::npos) {
                    result.append(content, pos, tableEnd - pos + 1);
                    result.append("<th></th>");
                    pos = tableEnd + 1;
                    continue;
                }
            }
            
            // 5. NEW: Fix empty anchor tags for accessibility
            if (caseInsensitiveCompare(content, pos, "<a ")) {
                size_t anchorStart = pos;
                size_t anchorEnd = findTagEnd(content, pos);
                
                if (anchorEnd != std::string::npos) {
                    // Check if this is an empty anchor tag
                    size_t nextTag = content.find('<', anchorEnd + 1);
                    if (nextTag != std::string::npos && 
                        caseInsensitiveCompare(content, nextTag, "</a>")) {
                        // Empty anchor found - we need to add accessible content
                        result.append(content, pos, anchorEnd - pos + 1);
                        
                        // Extract existing attributes to preserve them
                        std::string anchorContent = extractAnchorContent(content, anchorStart, anchorEnd);
                        
                        // Add accessible content
                        if (shouldAddLinkText(content, anchorStart, anchorEnd)) {
                            result.append("[Link]");
                        }
                        
                        pos = anchorEnd + 1;
                        continue;
                    }
                }
            }
            
            // 6. NEW: Fix anchors with only images (add alt text if missing)
            if (caseInsensitiveCompare(content, pos, "<a ")) {
                size_t anchorStart = pos;
                size_t anchorEnd = findTagEnd(content, pos);
                size_t closeAnchor = findCloseTag(content, anchorEnd, "a");
                
                if (anchorEnd != std::string::npos && closeAnchor != std::string::npos) {
                    // Check if anchor contains only an image
                    size_t imgPos = content.find("<img", anchorEnd + 1);
                    if (imgPos != std::string::npos && imgPos < closeAnchor) {
                        // Check if image has alt text
                        size_t imgEnd = findTagEnd(content, imgPos);
                        if (imgEnd != std::string::npos && imgEnd < closeAnchor) {
                            if (!hasAltText(content, imgPos, imgEnd)) {
                                // Image missing alt text - we'll need to modify
                                result.append(content, pos, imgPos - pos);
                                result.append(fixImageAltText(content, imgPos, imgEnd));
                                pos = imgEnd;
                                continue;
                            }
                        }
                    }
                }
            }
            
            result += content[pos];
            pos++;
        }
        
        return result;
    }
    
    static bool caseInsensitiveCompare(const std::string& str, size_t pos, const std::string& pattern) {
        if (pos + pattern.length() > str.length()) return false;
        
        for (size_t i = 0; i < pattern.length(); ++i) {
            if (std::tolower(str[pos + i]) != std::tolower(pattern[i])) {
                return false;
            }
        }
        return true;
    }
    
    static size_t findAttributeEnd(const std::string& content, size_t start) {
        if (start >= content.size()) return std::string::npos;
        
        char quote = content[start];
        if (quote != '"' && quote != '\'') {
            // Attribute without quotes - find space or >
            size_t end = content.find_first_of(" >", start);
            return (end == std::string::npos) ? std::string::npos : end;
        }
        
        size_t end = content.find(quote, start + 1);
        return (end == std::string::npos) ? std::string::npos : end + 1;
    }
    
    static size_t findTagEnd(const std::string& content, size_t start) {
        return content.find('>', start);
    }
    
    static size_t findCloseTag(const std::string& content, size_t start, const std::string& tagName) {
        std::string closeTag = "</" + tagName + ">";
        for (size_t i = 0; i < closeTag.length(); ++i) {
            closeTag[i] = std::tolower(closeTag[i]);
        }
        
        size_t pos = start;
        while ((pos = content.find('<', pos)) != std::string::npos) {
            if (caseInsensitiveCompare(content, pos, closeTag.c_str())) {
                return pos;
            }
            pos++;
        }
        return std::string::npos;
    }
    
    static std::string extractAnchorContent(const std::string& content, size_t anchorStart, size_t anchorEnd) {
        // Extract href for potential link text
        size_t hrefPos = content.find("href=", anchorStart);
        if (hrefPos != std::string::npos && hrefPos < anchorEnd) {
            size_t hrefEnd = findAttributeEnd(content, hrefPos + 5);
            if (hrefEnd != std::string::npos) {
                // Extract URL and use filename as link text
                std::string url = content.substr(hrefPos + 5, hrefEnd - hrefPos - 5);
                // Remove quotes
                url.erase(std::remove(url.begin(), url.end(), '"'), url.end());
                url.erase(std::remove(url.begin(), url.end(), '\''), url.end());
                
                // Extract filename from URL
                size_t lastSlash = url.find_last_of('/');
                if (lastSlash != std::string::npos) {
                    std::string filename = url.substr(lastSlash + 1);
                    // Remove extension
                    size_t dotPos = filename.find_last_of('.');
                    if (dotPos != std::string::npos) {
                        filename = filename.substr(0, dotPos);
                    }
                    // Convert to readable text
                    if (!filename.empty()) {
                        filename[0] = std::toupper(filename[0]);
                        std::replace(filename.begin(), filename.end(), '-', ' ');
                        std::replace(filename.begin(), filename.end(), '_', ' ');
                        return filename;
                    }
                }
            }
        }
        return "Link";
    }
    
    static bool shouldAddLinkText(const std::string& content, size_t anchorStart, size_t anchorEnd) {
        // Check if there's already some content between <a> and </a>
        size_t closeAnchor = findCloseTag(content, anchorEnd, "a");
        if (closeAnchor == std::string::npos) return false;
        
        // Check if there's any non-whitespace content between anchor tags
        for (size_t i = anchorEnd + 1; i < closeAnchor; ++i) {
            if (!std::isspace(content[i])) {
                return false; // There's already content
            }
        }
        return true; // No content found, need to add some
    }
    
    static bool hasAltText(const std::string& content, size_t imgStart, size_t imgEnd) {
        size_t altPos = content.find("alt=", imgStart);
        return (altPos != std::string::npos && altPos < imgEnd);
    }
    
    static std::string fixImageAltText(const std::string& content, size_t imgStart, size_t imgEnd) {
        std::string fixedImg = content.substr(imgStart, imgEnd - imgStart + 1);
        
        // Find where to insert alt attribute (before the closing >)
        size_t insertPos = fixedImg.find_last_of('>');
        if (insertPos != std::string::npos && insertPos > 0) {
            // Try to extract src for meaningful alt text
            std::string altText = "Decorative image";
            size_t srcPos = content.find("src=", imgStart);
            if (srcPos != std::string::npos && srcPos < imgEnd) {
                size_t srcEnd = findAttributeEnd(content, srcPos + 4);
                if (srcEnd != std::string::npos) {
                    std::string src = content.substr(srcPos + 4, srcEnd - srcPos - 4);
                    // Extract filename for alt text
                    size_t lastSlash = src.find_last_of('/');
                    if (lastSlash != std::string::npos) {
                        std::string filename = src.substr(lastSlash + 1);
                        size_t dotPos = filename.find_last_of('.');
                        if (dotPos != std::string::npos) {
                            filename = filename.substr(0, dotPos);
                            if (!filename.empty()) {
                                filename[0] = std::toupper(filename[0]);
                                std::replace(filename.begin(), filename.end(), '-', ' ');
                                std::replace(filename.begin(), filename.end(), '_', ' ');
                                altText = filename + " image";
                            }
                        }
                    }
                }
            }
            
            fixedImg.insert(insertPos, " alt=\"" + altText + "\"");
        }
        
        return fixedImg;
    }
};

int main() {
    std::cout << "HTML Accessibility Repair Tool" << std::endl;
    std::cout << "==============================" << std::endl;
    std::cout << "Fixes:" << std::endl;
    std::cout << "  1. Removes cellspacing=\"0\"" << std::endl;
    std::cout << "  2. Removes valign attributes" << std::endl;
    std::cout << "  3. Removes align attributes" << std::endl;
    std::cout << "  4. Adds <th></th> after <table>" << std::endl;
    std::cout << "  5. Adds content to empty anchor tags" << std::endl;
    std::cout << "  6. Adds alt text to images in links" << std::endl;
    std::cout << std::endl;
    
    std::string folderPath = "doc/html";
    
    // Create directory if it doesn't exist
    if (!fs::exists(folderPath)) {
        std::cout << "Creating directory: " << folderPath << std::endl;
        fs::create_directories(folderPath);
    }
    
    if (!fs::is_directory(folderPath)) {
        std::cerr << "Error: '" << folderPath << "' is not a directory." << std::endl;
        std::cout << "Press Enter to exit...";
        std::cin.get();
        return 1;
    }
    
    int processedCount = 0;
    int errorCount = 0;
    
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.is_regular_file()) {
            std::string ext = entry.path().extension().string();
            std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
            
            if (ext == ".html" || ext == ".htm") {
                std::cout << "Processing: " << entry.path().filename().string() << "... ";
                
                if (HTMLAccessibilityRepair::processFile(entry.path().string())) {
                    std::cout << "OK" << std::endl;
                    processedCount++;
                } else {
                    std::cout << "FAILED" << std::endl;
                    errorCount++;
                }
            }
        }
    }
    
    std::cout << std::endl << "Processing completed:" << std::endl;
    std::cout << "  Successfully processed: " << processedCount << " files" << std::endl;
    std::cout << "  Errors: " << errorCount << " files" << std::endl;
    
    if (processedCount == 0 && errorCount == 0) {
        std::cout << "No HTML files found in '" << folderPath << "'" << std::endl;
    }
    
    std::cout << std::endl << "Press Enter to exit...";
    std::cin.get();
    
    return errorCount > 0 ? 1 : 0;
}