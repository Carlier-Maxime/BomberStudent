#include <iostream>
#include "Log.h"
#include "Socket.h"

int main() {
    Log::open();
    Log::info("Launching BomberStudent...");
    try {
        SocketAddress addr1 = SocketAddress("127.0.0.1",42069,Protocol::IPV6);
        SocketAddress addr2 = SocketAddress("127.0.0.1",42469,Protocol::IPV6);
        SocketAddress addr3 = SocketAddress("127.0.0.1",42569,Protocol::IPV6);
        Socket socket1=Socket(addr1);
        Socket socket2=Socket(addr2);
        socket1.send("hello world !\n", addr2);
        std::cout << socket2.receive(&addr3);
        std::cout << addr3 << std::endl;
        Log::info("BomberStudent launched");
    } catch (std::exception const&) {
        Log::error("BomberStudent launching failed");
    }
    Log::info("BomberStudent stopped");
    Log::close();
}