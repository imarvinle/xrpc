

## 依赖

### muduo

选择 muduo 作为底层网络库，通过 git 子模块管理

```
# 在项目根目录执行
git submodule add https://github.com/chenshuo/muduo.git third_party/muduo
git submodule update --init --recursive
```

CMake 集成：

1. 添加子模块
add_subdirectory(third_party/muduo)

2. 编译依赖
target_link_libraries(xrpc PUBLIC muduo_net muduo_base)



### 添加 muduo 依赖 boost
 
```
Linux (Ubuntu/Debian)
# 安装预编译版本
sudo apt-get update
sudo apt-get install libboost-all-dev  # 安装所有模块

# 验证安装
dpkg -s libboost-dev | grep Version
```

### 编译 muduo

muduo本身依赖较少，但是 example 等可能有额外依赖（protobuf 等），所以如果不是需要测试，可以开启关闭选项

```
mkdir -p build && cd build && cmake -DMUDUO_BUILD_EXAMPLES=OFF .. && make
```