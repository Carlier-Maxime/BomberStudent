#include <iostream>
#include "Log.h"
#include "Socket.h"
#include "Server.h"
#include "Client.h"
#include "Utils.h"

int main(int argc, char* argv[]) {
    Log::open();
    bool launchServer=false;
    if (argc>1) {
        if ("server"==std::string(argv[1])) {
            launchServer=true;
        } else {
            Log::error("Argument not recognised");
            goto exit;
        }
    }

    try {
        if (launchServer) {
            Utils::processName = "Server";
            Log::info("Launching BomberStudent server...");
            Server().run();
            Log::info("BomberStudent server launched");
        } else {
            Utils::processName = "Client";
            Log::info("Launching BomberStudent client...");
            Client().run();
            Log::info("BomberStudent client launched");
        }
    } catch (std::exception const& e) {
        Log::error(e.what());
        Log::error("BomberStudent launching failed");
    }
    exit:
    Log::info("BomberStudent stopped");
    Log::close();
}