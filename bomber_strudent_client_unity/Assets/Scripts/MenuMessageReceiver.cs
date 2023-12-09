using UnityEngine;
using System.Net;

public class MenuMessageReceiver : MonoBehaviour, IMessageReceiver
{
    public ServeurList serveurList;
    private void Start()
    {
        MessageParser.getInstance().setMessageReceiver(this);
    }

    public void foundBomberStudentServer(IPAddress iPAddress)
    {
        Debug.Log("Il y a un serveur bomber student là: " + iPAddress.ToString());
        serveurList.addServer(iPAddress.ToString());
    }
}
