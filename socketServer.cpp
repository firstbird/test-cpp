#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

int main() {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    const char* hello = "Hello from server";

    // 创建 socket 文件描述符
      	// AF_INET :   表示使用 IPv4 地址		可选参数
    // SOCK_STREAM 表示使用面向连接的数据传输方式，
    // IPPROTO_TCP 表示使用 TCP 协议
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // 设置 socket 选项
//解释一下下面代码的作用和参数setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt))

//这行代码是用于设置socket选项的，它的作用是在服务器端口被占用时，允许立即重用该端口。

//具体来说，setsockopt() 函数的第一个参数 server_fd 是一个文件描述符，表示要设置选项的socket。第二个参数 SOL_SOCKET 表示要设置的选项级别，这里是通用套接字选项。第三个参数 SO_REUSEADDR | SO_REUSEPORT 是要设置的选项名和选项值，这里使用了位运算符 | 来同时设置两个选项。SO_REUSEADDR 表示允许在 bind() 过程中本地地址处于 TIME_WAIT 状态时重复使用该地址。SO_REUSEPORT 表示允许多个套接字绑定到同一个端口号，这样可以实现负载均衡。最后两个参数 &opt 和 sizeof(opt) 分别表示指向选项值的指针和选项值的大小。

// socket的级别有哪些，上面的opt取值举一个例子

// socket的级别包括 SOL_SOCKET、IPPROTO_IP、IPPROTO_IPV6、IPPROTO_TCP、IPPROTO_UDP 等，其中 SOL_SOCKET 是通用套接字选项级别。

// 以 SOL_SOCKET 为例，opt 参数可以是以下选项之一：

// SO_REUSEADDR：允许在 bind() 过程中本地地址处于 TIME_WAIT 状态时重复使用该地址。
// SO_REUSEPORT：允许多个套接字绑定到同一个端口号，这样可以实现负载均衡。
// SO_KEEPALIVE：启用 TCP keepalive 机制，检测连接是否已断开。
// SO_RCVBUF 和 SO_SNDBUF：设置接收和发送缓冲区大小。
// SO_ERROR：获取套接字错误状态。
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET; //使用IPv4地址
    address.sin_addr.s_addr = INADDR_ANY; //具体的IP地址
    address.sin_port = htons(8080); //端口

    // 绑定 socket 到指定的地址和端口号
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // 监听 socket，等待客户端连接
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // 接受客户端连接
    // 最后需要说明的是：listen() 只是让套接字进入监听状态，并没有真正接收客户端请求，listen() 后面的代码会继续执行，直到遇到 accept()。accept() 会阻塞程序执行（后面代码不能被执行），直到有新的请求到来
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address,
                             (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    // 从客户端读取数据
    valread = read(new_socket, buffer, 1024);
    printf("%s\n", buffer);

    // 向客户端发送数据
    send(new_socket, hello, strlen(hello), 0);
    printf("Hello message sent\n");

    return 0;
}
