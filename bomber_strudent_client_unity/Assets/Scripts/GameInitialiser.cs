using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Threading;
using System.Net;

public class GameInitialiser : MonoBehaviour
{
    public MapGenerator mapGenerator;
    public int height;
    public int width;
    public string content;

    public Camera mainCamera;
    public Vector3 cameraPos;
    public float cameraSize;

    public PlayerManager playerManager;
    public PlayerState playerState;

    // Start is called before the first frame update
    private void Start()
    {
        PartieInitialState partieInitialState = PartieManager.getInstance().GetPartieInitialState();

        mapGenerator.initMap(partieInitialState.getMap());
        setCamera();
        playerState.updatePlayerState(partieInitialState.GetPlayerState());
        Debug.Log("avant:"+ playerState.namePlayer +","+ partieInitialState.GetPlayerState().namePlayer);
        playerState.namePlayer = partieInitialState.GetPlayerState().namePlayer;
        Debug.Log("apres:" + playerState.namePlayer + "," + partieInitialState.GetPlayerState().namePlayer);
        playerManager.initPlayers(partieInitialState.getPlayerList());
        //mapGenerator.setContentMap(content);
        Thread thread = new Thread(() => test());
       // thread.Start();
    }
    private void setCamera()
    {

        int maxSize = Mathf.Max(mapGenerator.getHeight(), mapGenerator.getWidth()/2);
        if (maxSize < 1)
            maxSize = 1;
        float currentSize = cameraSize * maxSize;
        Vector3 currentPos = mapGenerator.centerRefPoint + (((Vector2)cameraPos - mapGenerator.centerRefPoint) * maxSize);
        currentPos.z = cameraPos.z;
        mainCamera.transform.position = currentPos;//cameraPos;
        mainCamera.orthographicSize = currentSize;//cameraSize / 2;
    }

    public void test()
    {
        Thread.Sleep(500);
        MessageParser.getInstance().parseMessage("{\"action\":\"attack/bomb\", \"statut\":\"201\", \"message\":\"bomb is armed at pos 5,3\",\"player\":{\"life\":100,\"speed\":1,\"nbClassicBomb\":1,\"nbMine\":0,\"nbRemoteBomb\":0,\"impactDist\":2,\"invincible\":false,}}", IPAddress.Any);
        MessageParser.getInstance().parseMessage("POST attack/newbomb", IPAddress.Any);
        MessageParser.getInstance().parseMessage("{\"pos\":\"3,2\",\"type\":\"classic\"}", IPAddress.Any);
        Thread.Sleep(1000);
        MessageParser.getInstance().parseMessage("POST attack/explose", IPAddress.Any);
        MessageParser.getInstance().parseMessage("{\"pos\":\"3, 2\",\"type\":\"classic\",\"impactDist\":2,\"map\":\"************************-------------*********-------=-----==============----==----------****--------==------****------------==----==============----==----------------------=************************\"} ", IPAddress.Any);

        MessageParser.getInstance().parseMessage("POST attack/affect", IPAddress.Any);
        MessageParser.getInstance().parseMessage("{\"life\":70,\"speed\":1,\"nbClassicBomb\":1,\"nbMine\":0,\"nbRemoteBomb\":0,\"impactDist\":2,\"invincible\":false,}", IPAddress.Any);

    }

}
