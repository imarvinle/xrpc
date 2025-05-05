#include "server.h"
#include "muduo/base/Logging.h"

XrpcServer::XrpcServer(muduo::net::EventLoop* loop,
                       const muduo::net::InetAddress& listenAddr,
                       const std::string& nameArg)
    : server_(loop, listenAddr, nameArg),
      loop_(loop) {
    // 设置连接回调
    server_.setConnectionCallback(
        std::bind(&XrpcServer::onConnection, this, std::placeholders::_1));
    // 设置消息回调
    server_.setMessageCallback(
        std::bind(&XrpcServer::onMessage, this, 
                  std::placeholders::_1, 
                  std::placeholders::_2, 
                  std::placeholders::_3));
}

void XrpcServer::start() {
    LOG_INFO << "XrpcServer starting...";
    server_.start();
}

void XrpcServer::onConnection(const muduo::net::TcpConnectionPtr& conn) {
    LOG_INFO << "Client " << conn->peerAddress().toIpPort() << " -> "
             << conn->localAddress().toIpPort() << " is "
             << (conn->connected() ? "UP" : "DOWN");
}

void XrpcServer::onMessage(const muduo::net::TcpConnectionPtr& conn,
                           muduo::net::Buffer* buf,
                           muduo::Timestamp receiveTime) {
    // 获取消息内容
    std::string msg = buf->retrieveAllAsString();
    LOG_INFO << "Received message from " << conn->peerAddress().toIpPort()
             << ": " << msg;
    
    // 简单的回显服务
    conn->send(msg);
}
