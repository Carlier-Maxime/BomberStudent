#include <vector>

#include "Log.h"
#include "Socket.h"
#include "Server.h"
#include "Client.h"
#include "Utils.h"

int main(int argc, char* argv[]) {
    Utils::processName = "Server";
    Log::open();
    bool launchClient=false;
    if (argc>1) {
        if ("client-dev"==std::string(argv[1])) {
            launchClient=true;
        } else {
            Log::error("Argument not recognised");
            goto exit;
        }
    }

    try {
        if (launchClient) {
            Utils::processName = "Client";
            Log::info("Launching BomberStudent client dev...");
            Client().run();
            Log::info("BomberStudent client dev launched");
        } else {
            Log::info("Launching BomberStudent server...");
            Server().run();
            Log::info("BomberStudent server launched");
        }
    } catch (std::exception const& e) {
        Log::error(e.what());
        Log::error("BomberStudent launching failed");
    }
    exit:
    Log::info("BomberStudent stopped");
    Log::close();
}