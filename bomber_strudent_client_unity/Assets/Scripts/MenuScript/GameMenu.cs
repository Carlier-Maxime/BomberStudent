using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//
using System.Net;
using System.Threading;


public class GameMenu : MonoBehaviour
{
    public MapMenu mapMenu;
    public ServeurListMenu serveurListMenu;

    public Camera mainCamera;
    public Vector3 cameraPos;
    public float cameraSize;

    public MapGenerator mapGenerator;
    public GameList gameList;

    public void setCamera()
    {
        int maxSize = Mathf.Max(mapGenerator.getHeight(), mapGenerator.getWidth());
        if (maxSize < 1)
            maxSize = 1;
        float currentSize = cameraSize * maxSize;
        Vector3 currentPos = mapGenerator.centerRefPoint + (((Vector2)cameraPos-mapGenerator.centerRefPoint) * maxSize);
        currentPos.z = cameraPos.z;
        mainCamera.transform.position = currentPos;//cameraPos;
        mainCamera.orthographicSize = currentSize;//cameraSize / 2;
    }

    public void returnToServeurMenu()
    {
        NetworkManager.getInstance().stoptTCP();
        serveurListMenu.setCamera();
        serveurListMenu.gameObject.SetActive(true);
        this.gameObject.SetActive(false);
    }
    public void goToMapMenu()
    {
        mapMenu.setCamera();
        mapMenu.gameObject.SetActive(true);
        this.gameObject.SetActive(false);
    }
    public void play()
    {
        MenuMessageSender.getInstance().joinGame(gameList.getCurrentGame());
    }
    private void OnEnable()
    {
        gameList.setButtons();
        
        Thread thread = new Thread(() => test());
        //thread.Start();
    }

    private void test()
    {
        Thread.Sleep(10);
        MessageParser.getInstance().parseMessage("{\"action\":\"maps/list\", \"statut\":\"200\", \"message\":\"ok\",\"nbMapsList\": 2,\"maps\":[{\"id\":0,\"width\":24,\"height\":8,\"content\":\"************************=----------------------==----==============----==----------****--------==------****------------==----==============----==----------------------=************************\"},{\"id\":1,\"width\":24,\"height\":8,\"content\":\"************************=------------****-------==----==============----==----------****--------==------****------------==----==============----==----------------------=************************\"}]}", IPAddress.Any);
        MessageParser.getInstance().parseMessage("{\"action\":\"game/list\", \"statut\":\"200\", \"message\":\"ok\", \"nbGamesList\": 2,\"games\":[ {\"name\":\"game1\",\"nbPlayer\":2,\"mapId\":0,},{\"name\":\"game2\",\"nbPlayer\":2,\"mapId\":1}],}", IPAddress.Any);
        //Thread.Sleep(10);
        //MessageParser.getInstance().parseMessage("{\"action\":\"game/join\", \"statut\":\"201\", \"message\":\"game joined\",\"nbPlayers\":2,\"mapId\" : 1,\"players\":[{ \"name\":\"player0\", \"pos\":\"0,0\"},{\"name\":\"player2\",\"pos\":\"0,79\"},],\"startPos\":\"5,3\",\"player\":{\"life\":100,\"speed\":1,\"nbClassicBomb\":10,\"nbMine\":5,\"nbRemoteBomb\":5,\"impactDist\":2,\"invincible\":false,}}", IPAddress.Any);

    }
}
