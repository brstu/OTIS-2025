# build_docs.ps1
Write-Host "Generating Doxygen documentation (XML output for SonarQube)..."

$Doxyfile = "DoxyfileNG.txt"

if (-Not (Test-Path $Doxyfile)) {
    Write-Error "DoxyfileNG.xml not found!"
    exit 1
}

doxygen $Doxyfile

if ($LASTEXITCODE -eq 0) {
    Write-Host "XML documentation generated successfully at doc/xml"
} else {
    Write-Error "Documentation generation failed!"
    exit $LASTEXITCODE
}