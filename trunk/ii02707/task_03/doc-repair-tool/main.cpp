#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <regex>
#include <vector>

namespace fs = std::filesystem;

class HTMLProcessor {
public:
    struct ProcessingStats {
        int filesProcessed = 0;
        int filesWithErrors = 0;
        std::vector<std::string> errorMessages;
    };

    static ProcessingStats processDirectory(const std::string& directoryPath) {
        ProcessingStats stats;
        
        if (!fs::exists(directoryPath)) {
            stats.errorMessages.push_back("Directory does not exist: " + directoryPath);
            stats.filesWithErrors++;
            return stats;
        }

        for (const auto& entry : fs::directory_iterator(directoryPath)) {
            if (entry.is_regular_file() && entry.path().extension() == ".html") {
                if (processFile(entry.path())) {
                    stats.filesProcessed++;
                } else {
                    stats.filesWithErrors++;
                    stats.errorMessages.push_back("Failed to process: " + entry.path().string());
                }
            }
        }
        
        return stats;
    }

private:
    static bool processFile(const fs::path& filePath) {
        try {
            // Read file
            std::ifstream inputFile(filePath, std::ios::binary);
            if (!inputFile) return false;

            std::string content((std::istreambuf_iterator<char>(inputFile)),
                               std::istreambuf_iterator<char>());
            inputFile.close();

            // Process content
            std::string processed = processHTMLContent(content);

            // Write back
            std::ofstream outputFile(filePath, std::ios::binary);
            if (!outputFile) return false;

            outputFile << processed;
            outputFile.close();

            return true;
        } catch (const std::exception& e) {
            std::cerr << "Exception processing " << filePath << ": " << e.what() << std::endl;
            return false;
        }
    }

    static std::string processHTMLContent(const std::string& content) {
        std::string result = content;

        // Remove name="*" (case insensitive)
        result = std::regex_replace(result, 
            std::regex(R"(name\s*=\s*["'][^"']*["'])", std::regex_constants::icase), "");
       
            // Remove cellspacing="0" (case insensitive)
        result = std::regex_replace(result, 
            std::regex(R"(cellspacing\s*=\s*["']0["'])", std::regex_constants::icase), "");

        // Remove cellpadding="0" (case insensitive)
        result = std::regex_replace(result, 
            std::regex(R"(cellpadding\s*=\s*["']0["'])", std::regex_constants::icase), "");

        // Remove valign="*" (any value, case insensitive)
        result = std::regex_replace(result, 
            std::regex(R"(valign\s*=\s*["'][^"']*["'])", std::regex_constants::icase), "");

        // Remove align="*" (any value, case insensitive)
        result = std::regex_replace(result, 
            std::regex(R"(align\s*=\s*["'][^"']*["'])", std::regex_constants::icase), "");

        // Add <th></th> after <table> (case insensitive)
        result = std::regex_replace(result, 
            std::regex(R"(<table(\s[^>]*)?>)", std::regex_constants::icase), "<table$1><th></th>");

        return result;
    }
};

int main() {
    std::string targetDirectory = "doc/html";
    
    std::cout << "HTML File Processor" << std::endl;
    std::cout << "===================" << std::endl;
    std::cout << "Target directory: " << targetDirectory << std::endl;
    std::cout << "Processing..." << std::endl << std::endl;

    auto stats = HTMLProcessor::processDirectory(targetDirectory);

    // Print results
    std::cout << "Processing Results:" << std::endl;
    std::cout << "  Successfully processed: " << stats.filesProcessed << " files" << std::endl;
    std::cout << "  Files with errors: " << stats.filesWithErrors << std::endl;

    if (!stats.errorMessages.empty()) {
        std::cout << "\nErrors:" << std::endl;
        for (const auto& error : stats.errorMessages) {
            std::cout << "  - " << error << std::endl;
        }
    }

    if (stats.filesProcessed == 0 && stats.filesWithErrors == 0) {
        std::cout << "No HTML files found in the specified directory." << std::endl;
    }

    return stats.filesWithErrors > 0 ? 1 : 0;
}