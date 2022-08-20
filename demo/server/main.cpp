#include <iostream>
#include <net.h>
#include <memory>
int main(int argc, char** argv)
{
    std::cout << "server start...\n";
    std::shared_ptr<Net> net(new Net);

    std::string serverAddr;
    std::string serverPort("44431");
    net->createServer(serverAddr, serverPort);

    return 0;
}