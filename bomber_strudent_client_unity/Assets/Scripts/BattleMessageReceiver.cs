using System.Collections;
using System.Collections.Generic;
using System.Net;
using UnityEngine;

public class BattleMessageReceiver : MonoBehaviour, IMessageReceiver
{
    public PlayerManager playerManager;
    public PlayerState playerState;
    public InputManager inputManager;
    public BombManager bombManager;
    public MapGenerator mapGenerator;

    // Start is called before the first frame update
    void Start()
    {
        MessageParser.getInstance().setMessageReceiver(this);
    }

    // Update is called once per frame
    void Update()
    {

    }
    public void addGameList(List<Partie> gameList)
    {
        return;
    }

    public void addMapList(List<Map> mapList)
    {

        return;
    }

    public void foundBomberStudentServer(IPAddress iPAddress)
    {

        return;
    }

    public void gameCreate(PartieInitialState partieInitialState)
    {

        return;
    }

    public void getItem(PlayerState playerState)
    {
        playerState.updatePlayerState(playerState);
    }

    public void joinGame(PartieInitialState partieInitialState)
    {

        return;
    }

    public void addNewPlayer(Player player)
    {
        playerManager.addPlayer(player);
    }
    public void poseBomb(Bomb bomb)
    {
       bombManager.addBomb(bomb);
    }

    public void displayReady(int time)
    {
        
    }

    public void updatePlayerPos(string playerName, string dir)
    {
        List<Player> players = playerManager.getPlayers();
        int idxPlayer = -1;
        for (int i = 0; i < players.Count; i++)
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
                players[idxPlayer].setPosition(players[idxPlayer].getPos() + new Vector2Int(0, 1));
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

    public void startGame()
    {
        inputManager.startGame();
    }

    public void bombPosed(PlayerState playerState)
    {
        this.playerState.updatePlayerState(playerState);
    }

    public void bombExplode(Vector2Int coord, BombType bombType, int impactDist, string newMap)
    {
        bombManager.explodeBomb(coord, bombType, impactDist);
        mapGenerator.setContentMap(newMap);

    }

    public void bombAffect(PlayerState playerState)
    {
        this.playerState.updatePlayerState(playerState);
        
    }
}
