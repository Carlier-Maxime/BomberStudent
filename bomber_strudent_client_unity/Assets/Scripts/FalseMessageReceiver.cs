using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FalseMessageReceiver : MonoBehaviour
{
    public PlayerManager playerManager;
    public BombManager bombManager;
    public PlayerState playerState;
    
    public void updatePositionPlayer(string playerName,string dir)
    {
        Player[] players = playerManager.getPlayers();
        int idxPlayer=-1;
        for(int i=0; i < players.Length; i++)
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
}
