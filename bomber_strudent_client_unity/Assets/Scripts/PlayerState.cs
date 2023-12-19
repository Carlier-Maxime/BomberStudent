using UnityEngine;

public class PlayerState : MonoBehaviour
{

    public string namePlayer;
    [SerializeField]
    private int life=100;
    public int nbClassicBomb=0;
    public int nbRemoteBomb=0;
    public int nbMine=0;
    private int impactDist=0;
    private bool invicible=false;
    public bool isActive = false;

    public BombCount bombCount;
    public LifeCount lifeCount;

    public void updatePlayerState(PlayerState other)
    {
        Debug.Log("playername:" + namePlayer);
        Debug.Log("playerState:" + other.getLife());
        this.life = other.life;
        this.nbClassicBomb = other.nbClassicBomb;
        this.nbRemoteBomb = other.nbRemoteBomb;
        this.nbMine = other.nbMine;
        this.invicible = other.invicible;
        this.impactDist = other.impactDist;
    }
    private void Update()
    {
        if (isActive)
        {
            this.lifeCount.setHp(this.getLife());
            this.bombCount.setClassicCount(this.nbClassicBomb);
            this.bombCount.setRemoteCount(this.nbRemoteBomb);
            this.bombCount.setMineCount(this.nbMine);
        }
    }

    public void initPlayerState(string namePlayer, int life, int nbClassicBomb, int nbRemoteBomb, int nbMine, bool invicible, int impactDist)
    {
        this.namePlayer = namePlayer;
        this.life = life;
        this.nbClassicBomb = nbClassicBomb;
        this.nbRemoteBomb = nbRemoteBomb;
        this.nbMine = nbMine;
        this.invicible = invicible;
        this.impactDist = impactDist;
        /*this.bombCount.setClassicCount(this.nbClassicBomb);
        this.bombCount.setRemoteCount(this.nbRemoteBomb);
        this.bombCount.setMineCount(this.nbMine);*/
    }

    public string getName()
    {
        return this.namePlayer;
    }
    public int getLife()
    {
        return this.life;
    }
    public void setLife(int life)
    {
        this.life=life;
    }
    public int getNbClassicBomb()
    {
        return this.nbClassicBomb;
    }
    public void setNbClassicBomb(int nbClassicBomb)
    {
        this.nbClassicBomb = nbClassicBomb;
    }
    public int getNbRemoteBomb()
    {
        return this.nbRemoteBomb;
    }
    public void setNbRemoteBomb(int nbRemoteBomb)
    {
        this.nbRemoteBomb = nbRemoteBomb;
    }
    public int getNbMine()
    {
        return this.nbMine;
    }
    public void setNbMine(int nbMine)
    {
        this.nbMine = nbMine;
    }

    public int getImpactDist()
    {
        return this.impactDist;
    }
    public bool isInvicible()
    {
        return this.invicible;
    }

    public override string ToString()
    {
        return "[" + life + "," + nbClassicBomb + "," + nbRemoteBomb + "," + nbMine + "," + invicible + "," + impactDist + "]";
    }

}
