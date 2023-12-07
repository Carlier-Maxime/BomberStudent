#include "Client.h"
#include "../utils/Utils.h"
#include "../utils/Log.h"

int main() {
    Utils::processName = "ClientDev";
    Log::open();
    try {
        Log::info("start");
        Client().run();
    } catch (std::exception const& e) {
        Log::error(e.what());
        Log::error("abnormally exit");
    }
    Log::info("stopped");
    Log::close();
}