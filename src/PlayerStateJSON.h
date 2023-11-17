#ifndef BOMBER_STUDENT_PLAYER_STATE_JSON
#define BOMBER_STUDENT_PLAYER_STATE_JSON



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
	std::string toJSON() const;
};

#endif