using UnityEngine;

public class PlayerState : MonoBehaviour
{
    public string namePlayer;
    private int life=100;
    public int nbClassicBomb=0;
    public int nbRemoteBomb=0;
    public int nbMine=0;
    private int impactDist=0;
    private bool invicible=false;


    public BombCount bombCount;

    public void updatePlayerState(PlayerState other)
    {
        this.life = other.life;
        this.nbClassicBomb = other.nbClassicBomb;
        this.nbRemoteBomb = other.nbRemoteBomb;
        this.nbMine = other.nbMine;
        this.invicible = other.invicible;
        this.impactDist = other.impactDist;
        this.bombCount.setClassicCount(this.nbClassicBomb);
        this.bombCount.setRemoteCount(this.nbRemoteBomb);
        this.bombCount.setMineCount(this.nbMine);
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



}
