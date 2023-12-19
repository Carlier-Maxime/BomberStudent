#include <thread>
#include "ClassicBomb.h"
#include "../utils/Config.h"

ClassicBomb::ClassicBomb(Case &case_, Game &game, u_int16_t pos, u_char impactDist) : Bomb(case_, game, "classic", pos, impactDist), th(nullptr) {}

void ClassicBomb::explode() {
    if (th) return;
    th = new std::thread([this](){
        std::this_thread::sleep_for(std::chrono::seconds(Config::getDetonationTime()));
        Bomb::explode();
    });
}

ClassicBomb::~ClassicBomb() {
    if (th) th->join();
    delete th;
}
