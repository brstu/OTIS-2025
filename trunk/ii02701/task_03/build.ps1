$VCPKG_PATH = "C:/vcpkg/scripts/buildsystems/vcpkg.cmake"

Write-Host "Cleaning previous build"
Remove-Item -Recurse -Force build -ErrorAction SilentlyContinue

Write-Host "Creating build directory"
New-Item -ItemType Directory build | Out-Null
Set-Location build

Write-Host "Configuring project (CMake)"
cmake .. "-DCMAKE_TOOLCHAIN_FILE=$VCPKG_PATH"

Write-Host "Building project"
cmake --build .

Write-Host "Running tests"
ctest -C Debug --output-on-failure

Write-Host "Build finished successfully"