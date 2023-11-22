#include "Client.h"
#include "../utils/Utils.h"
#include "../utils/Log.h"

int main() {
    Utils::processName = "ClientDev";
    Log::open();
    try {
        Log::info("Launching BomberStudent client dev...");
        Client().run();
        Log::info("BomberStudent client dev launched");
    } catch (std::exception const& e) {
        Log::error(e.what());
        Log::error("BomberStudent client dev failed");
    }
    Log::info("BomberStudent client dev stopped");
    Log::close();
}