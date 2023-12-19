using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Threading;
using System.Net;
using UnityEngine.UI;

public class MapMenu : MonoBehaviour
{
    public GameMenu gameMenu;
    public MapList mapList;

    public Camera mainCamera;
    public Vector3 cameraPos;
    public float cameraSize;
    public MapGenerator mapGenerator;
    public Text textField;
    public GameObject warningText;

    
    public void returnToGameMenu()
    {
        //mapGenerator.initMap(0, 0);
        this.gameMenu.gameObject.SetActive(true);
        gameMenu.setCamera();
        this.gameObject.SetActive(false);

    }

    public void jouer()
    {
        string nomPartie = textField.text.Trim();
        if (nomPartie.Length > 0)
        {
            warningText.SetActive(false);
            MenuMessageSender.getInstance().createGame(nomPartie,mapList.getCurrentMap());
        }
        else
        {
            warningText.SetActive(true);
        }
    }

    private void OnEnable()
    {

        /*mapList.resetMapList();

        mapList.addMap(new Map(1, 5, 5, "======***==***==***======"));
        mapList.addMap(new Map(2, 5, 5, "======*-*==*-*==***======"));*/

       /* Thread thread = new Thread(() => test());
        thread.Start();*/
    }

    private void test()
    {
        Thread.Sleep(1000);
        MessageParser.getInstance().parseMessage("{\"action\":\"game/create\", \"statut\":\"201\", \"message\":\"game created\",\"nbPlayers\":0,\"mapId\" : 1,\"startPos\":\"3,2\", \"player\":{\"life\":100,\"speed\":1,\"nbClassicBomb\":2,\"nbMine\":0,\"nbRemoteBomb\":1,\"impactDist\":2,\"invincible\":false,}}",IPAddress.Any);    
    }

    public void setCamera()
    {
        int maxSize = Mathf.Max(mapGenerator.getHeight(), mapGenerator.getWidth());
        if (maxSize < 1)
            maxSize = 1;
        float currentSize = cameraSize * maxSize;
        Vector3 currentPos = mapGenerator.centerRefPoint + (((Vector2)cameraPos - mapGenerator.centerRefPoint) * maxSize);
        currentPos.z = cameraPos.z;
        mainCamera.transform.position = currentPos;//cameraPos;
        mainCamera.orthographicSize = currentSize;//cameraSize / 2;
    }
}
