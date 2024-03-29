## 第十一章 网络编程

### 网络编程
* IP地址与点分十进制之间转换: inet_pton()/inet_ntop()
* nslookup应用探究DNS映射
* /etc/services记录机器知名服务名字与知名端口之间的映射
* getaddrinfo()/getnameinfo()实现二进制套接字地址结构与主机名字、主机地址之间的转换

### Web服务器与HTTP事务
* Web服务器以两种不同的方式向客户端提供内容：
    * 静态内容(static content)，取一个磁盘文件，并将它的内容返回给客户端，其URL(universal resource locator)如：http://www.google.com:80/index.html
    * 动态内容(dynamic content)，运行一个可执行文件，并将它的输出返回给客户端。其URL如：http:/bluefish.ics.cs.cmu.edu:8000/cgi-bin/adder?1500&213，标识/cgi-bin/addr的可执行文件(称为Common Gateway Interface, CGI)，带两个参数字符串1500和213
        * ？字符分隔文件名和参数
        * & 字符分隔参数

* 服务静态内容，即将文件内容拷贝发送
* 服务动态内容，服务器将调用fork()创建子进程，并调用execve在子进程上下文中执行/cgi-bin/addr程序，子进程将环境变量QUERY_STRING设置为1500&213并进行getenv解析，传递给子进程作为程序参数。
    * 可以通过dup2()将执行结果重定向到连接上，直接将结果发送