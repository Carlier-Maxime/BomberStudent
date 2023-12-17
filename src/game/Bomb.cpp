#include <utility>
#include "Game.h"
#include "Case.h"
#include "Bomb.h"
#include "../utils/Utils.h"
#include "../utils/ConstantMessages.h"

using CM = ConstantMessages;

Bomb::Bomb(Case& case_, Game &game, std::string type, u_int16_t pos, u_char impactDist) : Item(case_), game(game),
type(std::move(type)), pos(pos), impactDist(impactDist), exploded(false) {}

bool Bomb::get([[maybe_unused]] const Player *player) {
    if (exploded) {
        case_.setItem(nullptr);
        delete this;
        return true;
    }
    return false;
}

Bomb::~Bomb() = default;

float Bomb::damage(u_char distOfImpact) {
    return 20.f-3.75f*static_cast<float>(distOfImpact);
}

void Bomb::explode() {
    if (exploded) return;
    u_char x, y;
    SPLIT_POS(pos,x,y);
    game.getMap().explodeBomb(x,y,impactDist,Bomb::damage);
    exploded=true;
    std::ostringstream oss;
    oss << CM::postAttackExplode << R"({"pos":")" << std::to_string(x) << ',' << std::to_string(y)
        << R"(","type":")" << type << R"(","impactDist":)" << std::to_string(impactDist) << R"(,"map":")"
        << game.getMap().toCasesString() << "\"}";
    game.sendForAllPlayers(oss.str());
}
