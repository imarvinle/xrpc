# 指定CMake最低版本要求为3.10
cmake_minimum_required(VERSION 3.10)
# 定义项目名称为xrpc，支持C和C++语言
project(xrpc C CXX)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/)

message(STATUS "CMAKE_BINARY_DIR = ${CMAKE_BINARY_DIR}")


# 设置C++标准为C++11
set(CMAKE_CXX_STANDARD 11)
# 强制要求使用指定的C++标准
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 生成位置无关代码，这对于创建共享库很重要
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# 构建选项 - 可以通过命令行参数修改这些选项
# 例如: cmake -DBUILD_SHARED_LIBS=OFF ..
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)  # 默认构建静态库
option(BUILD_UNIT_TESTS "Build unit tests" ON)         # 默认构建单元测试
option(BUILD_EXAMPLES "Build examples" ON)             # 默认构建示例代码

# 查找依赖项

# 查找线程库，这是必需的
# 这个会根据系统和编译器自动选择合适的线程库，linux 一般是 -pthread
# 选择好了会写入到变量 CMAKE_THREAD_LIBS_INIT
find_package(Threads REQUIRED) 

# 查找protobuf库，会将结果存储在PROTOBUF_LIBRARIES变量中
find_package(Protobuf REQUIRED)
# 查找gflags库
find_package(gflags REQUIRED)

# 设置Muduo库的编译选项
# CACHE BOOL "" 表示这些变量会被缓存，可以在CMake GUI中看到
set(MUDUO_BUILD_EXAMPLES OFF CACHE BOOL "")  # 不构建Muduo的示例代码
set(MUDUO_BUILD_TESTS OFF CACHE BOOL "")     # 不构建Muduo的测试代码

# 添加第三方库Muduo作为子目录
# 这会级联编译Muduo库并用于本项目
add_subdirectory(third_party/muduo)

# 设置包含目录，这些目录中的头文件可以被直接包含
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}              # 当前源代码目录
    ${CMAKE_CURRENT_BINARY_DIR}              # 当前构建目录
    ${PROTOBUF_INCLUDE_DIRS}                 # Protobuf头文件目录
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/muduo  # Muduo头文件目录
)

# 找到所有源文件 
# GLOB_RECURSE 会递归查找所有匹配的文件
# 注意：CMake官方建议明确列出源文件而不是使用GLOB，因为新添加的文件可能不会自动触发CMake重新配置（这里偷个懒）

file(GLOB_RECURSE SOURCES "src/*.cpp")  # 收集所有cpp源文件
file(GLOB_RECURSE HEADERS "src/*.h")    # 收集所有h头文件

# 创建库目标
# 这将创建一个名为xrpc的库，可以是静态库或动态库，取决于 BUILD_SHARED_LIBS 选项
add_library(xrpc ${SOURCES})
# 为xrpc库链接所需的依赖库
target_link_libraries(xrpc
    ${CMAKE_THREAD_LIBS_INIT}  # 线程库
    ${PROTOBUF_LIBRARIES}      # Protobuf库
    gflags                     # gflags库
    muduo_net                  # Muduo网络库
    muduo_base                 # Muduo基础库
)

# 设置构建的库到 lib 目录
set_target_properties(xrpc PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)



# 创建可执行文件目标
# 创建一个名为xrpc_main的可执行文件
add_executable(xrpc_main src/main.cpp)
# 为xrpc_main可执行文件链接所需的库
target_link_libraries(xrpc_main
    xrpc                       # 我们自己的xrpc库
)

# xrpc_main 可执行文件的输出配置
set_target_properties(xrpc_main PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)


# 如果启用了单元测试，则设置测试
if(BUILD_UNIT_TESTS)
    # 启用CTest测试框架
    enable_testing()
    # 添加测试目录，目前被注释掉了
    #add_subdirectory(test)
endif()

# 如果启用了示例代码，则构建示例
if(BUILD_EXAMPLES)
    # 添加示例目录，目前被注释掉了
    #add_subdirectory(example)
endif()