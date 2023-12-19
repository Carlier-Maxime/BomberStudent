using UnityEngine;
using System.Net;
using System.Collections.Generic;
using UnityEngine.SceneManagement;

public class MenuMessageReceiver : MonoBehaviour, IMessageReceiver
{
    public ServeurList serveurList;

    private bool chargeNextScene = false;
    
    private void Start()
    {
        MessageParser.getInstance().setMessageReceiver(this);
    }

    private void Update()
    {
        if (chargeNextScene)
        {
            SceneManager.LoadScene("battleScene");
        }
    }
    public void foundBomberStudentServer(IPAddress iPAddress)
    {
        Debug.Log("Il y a un serveur bomber student là: " + iPAddress.ToString());
        serveurList.addServer(iPAddress.ToString());
    }


    public void addMapList(List<Map> mapList)
    {
        Debug.Log("nbMaps:" + mapList.Count);
        foreach(Map map in mapList){

            PartieManager.getInstance().addMap(map);
        }
    }
    public void addGameList(List<Partie> gameList)
    {
        foreach (Partie partie in gameList)
        {

            PartieManager.getInstance().addPartie(partie);
        }
    }
    public void gameCreate(PartieInitialState partieInitialState)
    {
        PartieManager.getInstance().setPartieInitialState(partieInitialState);
        Debug.Log(partieInitialState);
        chargeNextScene = true;
    }
    public void joinGame(PartieInitialState partieInitialState)
    {
        PartieManager.getInstance().setPartieInitialState(partieInitialState);
        Debug.Log(partieInitialState);
        chargeNextScene = true;
    }
    public void poseBomb(Bomb bomb)
    {
        return;
    }
    public void getItem(PlayerState playerState)
    {
        return;
    }
    public void addNewPlayer(Player player)
    {
        return;
    }

    public void displayReady(int time)
    {
        return;
    }

    public void updatePlayerPos(string playerName, string dir)
    {
        return;
    }

    public void startGame()
    {
        return;
    }

    public void bombPosed(PlayerState playerState)
    {
        return;
    }

    public void bombExplode(Vector2Int coord, BombType bombType, int impactDist, string newMap)
    {
        return;
    }

    public void bombAffect(PlayerState playerState)
    {
        return;
    }
}
