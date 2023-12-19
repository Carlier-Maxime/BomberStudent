using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PartieInitialState
{
    private Map map;
    private List<Player> playerList;
    private PlayerState playerState;

    public PartieInitialState(Map map, List<Player> playerList, PlayerState playerState)
    {
        this.map = map;
        this.playerList = playerList;
        this.playerState = playerState;
    }
    public List<Player> getPlayerList()
    {
        return playerList;
    }

    public PlayerState GetPlayerState()
    {
        return playerState;
    }
    public Map getMap()
    {
        return map;
    }

    override public string ToString()
    {
        string res = playerState.ToString()+",[";
        for(int i = 0; i < playerList.Count; i++)
        {
            res += "{" + playerList[i].getName() + "," + playerList[i].getPos().ToString() + "},";
        }
        res += "],";
        res += "{" + map.getHeight() + "," + map.getWidth() + "," + map.getContent() + "}";
        return res;
    }

}
