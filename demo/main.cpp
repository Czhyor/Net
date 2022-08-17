#include <iostream>
#include <net.h>
int main(int argc, char** argv)
{
    std::cout << "hello world\n";
    Net* net = new Net;
    std::string serverAddr;
    std::string serverPort("44431");
    net->createServer(serverAddr, serverPort);

    net->createClient("127.0.0.1", "44430");
    return 0;
}