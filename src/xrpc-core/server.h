#pragma once

#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <string>
#include <functional>

class XrpcServer {
public:
    XrpcServer(muduo::net::EventLoop* loop,
               const muduo::net::InetAddress& listenAddr,
               const std::string& nameArg);

    void start();

private:
    void onConnection(const muduo::net::TcpConnectionPtr& conn);

    void onMessage(const muduo::net::TcpConnectionPtr& conn,
                   muduo::net::Buffer* buf,
                   muduo::Timestamp receiveTime);

    muduo::net::TcpServer server_;
    muduo::net::EventLoop* loop_;
};
