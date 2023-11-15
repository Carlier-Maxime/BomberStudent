#ifndef BOMBER_STUDENT_PLAYER_STATE_JSON
#define BOMBER_STUDENT_PLAYER_STATE_JSON
#define PLAYER_STATE_JSON_STRING_PROTOTYPE "{\"life\":%d,\"speed\":%d,\"nbClassicBomb\":%d,\"nbMine\":%d,\"nbRemoteBomb\":%d,\"impactDist\":%d,\"invincible\":%s}"



class PlayerStateJSON{
private:
	int life;
	int speed;
	int nbClassicBomb;
	int nbMine;
	int nbRemoteBomb;
	int impactDist;
	bool invincible;
public:
	PlayerStateJSON(int lifeValue, int speedValue, int nbClassicBombValue, int nbMineValue, int nbRemoteBombValue, int impactDistValue, int invincibleValue);
	char* toJSON();
};

#endif