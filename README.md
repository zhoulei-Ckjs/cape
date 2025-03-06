# 编译环境
操作系统: ubuntu20.04

# 编译准备
## cpprestsdk
版本：v2.10.15

```shell
git clone --recurse-submodule --depth=1 -b v2.10.15 git@github.com:microsoft/cpprestsdk.git
cd cpprestsdk
```
CMakeLists.txt
```cmake
add_compile_options(-Wno-redundant-move)
```

```shell
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local -DBUILD_SHARED_LIBS=OFF
cmake --build build
cmake --install build
```

