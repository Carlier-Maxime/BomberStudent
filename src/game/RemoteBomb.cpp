#include "RemoteBomb.h"

RemoteBomb::RemoteBomb(Case &case_, Game &game, u_int16_t pos, u_char impactDist) : Bomb(case_, game, "remote", pos, impactDist) {}
