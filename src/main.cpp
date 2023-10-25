#include <iostream>
#include "Log.h"
#include "Socket.h"

int main() {
    Log::open();
    Log::info("Launching BomberStudent...");
    try {
        Socket socket=Socket(SocketAddress("localhost",42069,Protocol::IPV6));
        Log::info("BomberStudent launched");
    } catch (std::exception const&) {
        Log::error("BomberStudent launching failed");
    }
    Log::info("BomberStudent stopped");
    Log::close();
}