using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerManager : MonoBehaviour
{
    public MapGenerator mapGenerator;
    public Color[] playerColors;
    private GameObject[] playersObjects;
    public Player[] players;
    public GameObject playerPrefab;

    // Start is called before the first frame update
    void Start()
    {
        Player[] players = new Player[2];
        players[0] = new Player("Steven", 0, 1);
        players[1] = new Player("Oscar", 3, 2);
        initPlayers(players);
    }

    // Update is called once per frame
    void Update()
    {
        updatePlayer();
    }

    public void updatePlayer()
    {
        for (int i = 0; i < players.Length; i++)
        {

            playersObjects[i].transform.position = mapGenerator.getPosForCoord(players[i].getPos());
        }
    }

    public void initPlayers(Player[] players)
    {
        this.players = players;
        playersObjects = new GameObject[players.Length];
        for(int i = 0; i < players.Length;i++)
        {

            playersObjects[i] = GameObject.Instantiate(playerPrefab, mapGenerator.getPosForCoord(players[i].getPos()), Quaternion.identity, this.transform);
            playersObjects[i].GetComponent<SpriteRenderer>().color = playerColors[i];
        }

    }

    public void setPlayers(Player[] players)
    {
        this.players = players;

    }
    public Player[] getPlayers()
    {
        return this.players;
    }

    public Player getPlayer(string playerName)
    {
        for (int i = 0; i < players.Length; i++)
        {
            if (players[i].getName().Equals(playerName))
            {
                return players[i];
            }
        }
        return null;
    }
}
