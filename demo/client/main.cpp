#include <iostream>
#include <net.h>
#include <memory>

int main(int argc, char** argv)
{
    std::cout << "hello world\n";
    std::shared_ptr<Net> net(new Net);

    net->createClient("127.0.0.1", "44431");
    return 0;
}