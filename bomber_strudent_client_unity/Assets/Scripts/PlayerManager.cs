using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerManager : MonoBehaviour
{
    public MapGenerator mapGenerator;
    public Color[] playerColors;
    private List<GameObject> playersObjects;
    public List<Player> players = new List<Player>();
    public GameObject playerPrefab;

    public Color playerColor;
    public Color ennemiColor;

    private bool changePlayer = false;

    // Start is called before the first frame update
    void Start()
    {
        /*Player[] players = new Player[2];
        players[0] = new Player("Steven", 0, 1);
        players[1] = new Player("Oscar", 3, 2);
        initPlayers(players);*/
    }

    // Update is called once per frame
    void Update()
    {
        updatePlayer();
    }

    public void updatePlayer()
    {
        if (changePlayer)
        {
            changePlayer = false;
            updatePlayerObject();
        }
        for (int i = 0; i < players.Count; i++)
        {

            playersObjects[i].transform.position = mapGenerator.getPosForCoord(players[i].getPos());
        }
    }

    public void initPlayers(List<Player> players)
    {
        this.players = players;
        playersObjects = new List<GameObject>();
        for(int i = 0; i < players.Count;i++)
        {

            playersObjects.Add(GameObject.Instantiate(playerPrefab, mapGenerator.getPosForCoord(players[i].getPos()), Quaternion.identity, this.transform));
            
            playersObjects[i].GetComponent<SpriteRenderer>().color = players[i].getName() == PartieManager.getInstance().getPlayerName()? playerColor : ennemiColor;
            Debug.Log(players[i].getName());
        }
        

    }

    public void addPlayer(Player player)
    {
        Debug.Log("J'ajoute le joueur " + player.getName());
        this.players.Add(player);
        changePlayer = true;
        
    }
    public void updatePlayerObject()
    {
        while(playersObjects.Count > 0)
        {
            GameObject o = playersObjects[0];
            playersObjects.RemoveAt(0);
            Destroy(o);
        }
        initPlayers(this.players);
    }
    /*public void initPlayers(List<Player> players)
    {
        initPlayers(players.ToArray());
    }*/

    /*public void setPlayers(Player[] players)
    {
        this.players = players;

    }*/

    public void setPlayers(List<Player> players)
    {
        this.players = players;
    }
    public List<Player> getPlayers()
    {
        return this.players;
    }

    public Player getPlayer(string playerName)
    {
        for (int i = 0; i < players.Count; i++)
        {
            if (players[i].getName().Equals(playerName))
            {
                return players[i];
            }
        }
        return null;
    }
}
