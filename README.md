

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

