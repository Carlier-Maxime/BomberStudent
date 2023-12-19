using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FalseMessageReceiver : MonoBehaviour
{
    public PlayerManager playerManager;
    public BombManager bombManager;
    public PlayerState playerState;
    public MapGenerator mapGenerator;
    public LifeCount lifeCount;
    public Explosion explosion;
    public GameObject explosionPrefab;

    private void Start()
    {

        affectPlayer(playerState);
    }
    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.Space))
        {
            this.bombExplode(new Vector2Int(2, 1), BombType.classic, 3, "********_____**_===_**_____**_____**__==_**_____********");
            playerState.setLife(70);
            affectPlayer(playerState);
        }
    }

    public void updatePositionPlayer(string playerName,string dir)
    {
        List<Player> players = playerManager.getPlayers();
        int idxPlayer=-1;
        for(int i=0; i < players.Count; i++)
        {
            if (players[i].getName().Equals(playerName))
            {
                idxPlayer = i;
            }   
        }
        if (idxPlayer > -1)
        {
            if ("up".Equals(dir))
            {
                players[idxPlayer].setPosition(players[idxPlayer].getPos()+new Vector2Int(0,1));
            }
            else if ("down".Equals(dir))
            {
                players[idxPlayer].setPosition(players[idxPlayer].getPos() + new Vector2Int(0, -1));

            }
            else if ("right".Equals(dir))
            {
                players[idxPlayer].setPosition(players[idxPlayer].getPos() + new Vector2Int(1, 0));

            }
            else if ("left".Equals(dir))
            {
                players[idxPlayer].setPosition(players[idxPlayer].getPos() + new Vector2Int(-1, 0));

            }
        }
        playerManager.setPlayers(players);
    }

    public void placeBomb(BombType bombType, Vector2Int coord,PlayerState playerState)
    {
        this.playerState.updatePlayerState(playerState);
        if (bombType == BombType.classic)
        {
            bombManager.addClassicBomb(coord);
        }
        else if (bombType == BombType.remote)
        {
            bombManager.addRemoteBomb(coord);
        }
        else if (bombType == BombType.mine)
        {
            bombManager.addMine(coord); 
        }
    }

    public void bombExplode(Vector2Int coord, BombType bombType, int impactDist, string newMap)
    {
        bombManager.deleteBomb(coord, bombType);
        Explosion explosion = Instantiate(explosionPrefab).GetComponent<Explosion>();
        explosion.setExplosion(coord, impactDist,mapGenerator);
        mapGenerator.setContentMap(newMap);
    }

    public void affectPlayer(PlayerState other)
    {
        this.playerState.updatePlayerState(other);
        lifeCount.setHp(this.playerState.getLife());
    }
}
