#include <csignal>

#include "../socket/SocketAddress.h"
#include "../socket/SocketUDP.h"
#include "../utils/Config.h"
#include "../utils/ConstantMessages.h"
#include "../utils/Log.h"
#include "../utils/Utils.h"
#include "../utils/BomberStudentExceptions.h"

int main() {
    Utils::processName= "Server:UDP";
    Log::open();
    SocketAddress address = SocketAddress("::1",Config::getServerPort());
    auto socketUDP = SocketUDP(address.getProtocol(), true);
    socketUDP.bind(address);
    SocketAddress client = SocketAddress("::", 0);
    const struct sigaction act = {
            {[](int){}},
            {},
            0,
            {}
    };
    sigaction(SIGINT, &act, nullptr);
    for (;;) {
        Log::info("waiting client...");
        try {
            while (socketUDP.receive(&client)!=ConstantMessages::lookingServers);
        } catch (SocketException& e) {
            break;
        }
        Log::info("client found !");
        socketUDP.send(ConstantMessages::serverHello, client);
    }
    Log::info("shutdown handler UDP");
    Log::close();
}
