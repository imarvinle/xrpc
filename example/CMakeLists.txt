cmake_minimum_required(VERSION 3.10)
project(xrpc_example)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 包含头文件目录
include_directories(${CMAKE_SOURCE_DIR}/src)

# 添加 muduo 依赖
add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/muduo EXCLUDE_FROM_ALL)

# 编译示例服务器
add_executable(server_example server.cpp)
target_link_libraries(server_example muduo_net muduo_base pthread)

# 编译示例客户端
add_executable(client_example client.cpp)
target_link_libraries(client_example muduo_net muduo_base pthread)

# 安装目标
install(TARGETS server_example client_example
        RUNTIME DESTINATION bin)
