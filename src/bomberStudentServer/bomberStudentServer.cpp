#include <unistd.h>

#include "Server.h"
#include "../utils/Utils.h"
#include "../utils/Log.h"
#include "../utils/BomberStudentExceptions.h"

int main(int argc, char* argv[]) {
    Utils::processName = "Server";
    Log::open();
    bool launchClient=false;
    int pid=1;
    if (argc>1) {
        if ("dev"==std::string(argv[1])) {
            launchClient=true;
        } else {
            Log::error("Argument not recognised");
            goto exit;
        }
    }

    try {
        if (launchClient && (pid=fork())==0) {
            char* args[] = {(char*) "./clientDev", nullptr};
            execv(args[0], args);
            throw SystemException("Launching client failed (exec)");
        } else if (pid==-1) {
            throw SystemException("Launching client failed (fork)");
        } else {
            Log::info("start");
            Server().run();
        }
    } catch (std::exception const& e) {
        Log::error(e.what());
        Log::error("abnormally exit");
    }
    exit:
    Log::info("stopped");
    Log::close();
}