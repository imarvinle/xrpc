#include "muduo/base/Logging.h"
#include "muduo/net/EventLoop.h"
#include "muduo/net/InetAddress.h"
#include "xrpc-core/server.h"
#include <iostream>

int main(int argc, char *argv[]) {
  LOG_INFO << "xrpc server starting...";
  std::cout << "Hello from xrpc!!!!" << std::endl;

  // 创建事件循环
  muduo::net::EventLoop loop;
  // 创建服务器，监听 8080 端口
  muduo::net::InetAddress listenAddr(8080);
  XrpcServer server(&loop, listenAddr, "XrpcServer");
  server.start();

  // 启动事件循环
  loop.loop();

  return 0;
}