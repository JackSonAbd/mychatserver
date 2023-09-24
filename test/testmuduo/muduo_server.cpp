/*tcp server*/
/*epoll + 线程池=>分离开网络I/O和业务代码区*/
/*用户的连接和断开         用户的可读写事件*/

#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <string>
#include <iostream>
#include <functional>
using namespace muduo::net;
using namespace muduo;
using namespace std;
using namespace placeholders;

/*1.组合TCPserver对象
2.创建Event_Loop事件循环对象的指针
3.明确TcpServer构造函数需要什么参数，输出chatServer的构造函数
4.在当前服务器类的构造函数中，注册处理连接的回调函数和处理读写事件的回调函数
5.设置合适的服务端线程数量，moduo库会自己分配I/O线程和worker线程
*/
class ChatServer
{
public:
    ChatServer(EventLoop *loop,
                const InetAddress &listenAddr,  //IP+PORT
                const string nameArg   //服务器名字              
                )
                :_server(loop, listenAddr, nameArg),_loop(loop)
    {
        //给服务器注册和连接和断开回调    方法一个参数需要占位符  
        _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));

        //给服务器用户读写事件回调
        _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));
    
        //设置服务端的线程数量  1个I/O线程，3个worker线程
        _server.setThreadNum(4);
    }
    
    //开启事件循环
    void start()
    {
        _server.start();
    }
private:
    //专门处理用户的连接创建和断开
    void onConnection(const TcpConnectionPtr &conn)
    {
        if (conn->connected())
        {
            cout << conn->peerAddress().toIpPort() << "->"  \
                    << conn->localAddress().toIpPort() << "state:online" <<endl;
        }
        else
        {
            cout << conn->peerAddress().toIpPort() << "->" \
                    << conn->localAddress().toIpPort() << "state:offline" << endl;
            conn->shutdown();   //close(fd)
            //_loop->quit();        //连接断开
        }
    }

    //专门处理用户的读写事件
    void onMessage(const TcpConnectionPtr &conn,       //连接
                    Buffer *buffer,    //缓冲区
                    Timestamp time)         //接收到数据的时间信息
    {
        string buf = buffer->retrieveAllAsString();
        cout << "recv data:" << buf << " time:" << time.toString() << endl;
        conn->send(buf);
    }

    TcpServer _server;
    EventLoop *_loop;   //epoll
};


int main()
{
    EventLoop loop; //epoll
    InetAddress addr("127.0.0.1", 6000);
    ChatServer server(&loop, addr, "ChatServer");

    server.start(); //listenfd epoll_ctl > epoll
    loop.loop();    //epoll_wait以阻塞的方式等待新用户的连接，已连接用户的读写事件等

    return 0;
}