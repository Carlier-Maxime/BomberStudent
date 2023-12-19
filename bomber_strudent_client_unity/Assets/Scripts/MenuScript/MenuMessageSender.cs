using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MenuMessageSender : MonoBehaviour
{
    private static MenuMessageSender instance;


    private void Awake()
    {
        if (instance != null)
        {
            GameObject.Destroy(this.gameObject);
        }
        else
        {
            MenuMessageSender.instance = this;
        }
    }

    public static MenuMessageSender getInstance()
    {
        return instance;
    }
    public void sendLookForServer()
    {
        NetworkManager.getInstance().initUpdClient("255.255.255.255");
        NetworkManager.getInstance().sendUDPMessage("looking for bomberstudent servers");
    }

    public void getGameList()
    {
        string message = "GET game/list";
        NetworkManager.getInstance().sendTCPMessage(message);
    }

    public void getMapList()
    {
        string message = "GET maps/list";
        NetworkManager.getInstance().sendTCPMessage(message);
    }
    public void joinGame(Partie partie)
    {
        string message = "POST game/join\n{\"name\":\""+partie.getNameGame()+"\"}\n";

        NetworkManager.getInstance().sendTCPMessage(message);
    }

    public void createGame(string name, Map map)
    {
        string message = "POST game/create\n{\"name\":\"" + name + "\",\"mapId\":" + map.getId() + "}\n";
        NetworkManager.getInstance().sendTCPMessage(message);
    }
}
