rm -rf bin
mkdir bin
pushd bin

cmake.exe ..
cmake.exe --build . --config Release

# cmake.exe --build . --config Release --target PACKAGE

popd
