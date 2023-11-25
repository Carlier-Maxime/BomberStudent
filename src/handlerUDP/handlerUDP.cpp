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
    Log::info("start");
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
            if (errno==EINTR) break;
            throw e;
        }
        Log::info("client found - "+client.toString());
        socketUDP.send(ConstantMessages::serverHello, client);
    }
    Log::info("stopped");
    Log::close();
}
