# wc-clone


### Building the project:


To install the dependencies, run the command below within project root directory (where main CMakeLists.txt file is located)
```
vcpkg install --x-install-root="build"
```
Then:

```
cd build &&
cmake .. -DCMAKE_TOOLCHAIN_FILE=<path-to-vcpkg-cmake> &&
cmake --build .
```
