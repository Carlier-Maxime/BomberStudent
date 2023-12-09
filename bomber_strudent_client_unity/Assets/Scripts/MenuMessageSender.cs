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
}
