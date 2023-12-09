using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Net;

public class MessageParser : MonoBehaviour
{
    private static MessageParser instance;

    private IMessageReceiver messageReceiver;
    private void Awake()
    {
        if (instance != null)
        {
            GameObject.Destroy(this.gameObject);
        }
        else
        {
            instance = this;
        }
    }

    public static MessageParser getInstance()
    {
        return instance;
    }

    public void parseMessage(string message, IPAddress iPAddress)
    {
        if(message == "hello i'm a bomberstudent server\n")
        {
            messageReceiver.foundBomberStudentServer(iPAddress);
        }
        else
        {
            Debug.Log("mauvais message:" + message);
        }
    }



    public void setMessageReceiver(IMessageReceiver messageReceiver)
    {
        this.messageReceiver = messageReceiver;
    }

}
