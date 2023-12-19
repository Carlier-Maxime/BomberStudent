using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ServeurListMenu : MonoBehaviour
{
    public MainMenu mainMenu;
    public ServeurList serveurList;
    public GameMenu partieMenu;

    public Camera mainCamera;
    public Vector3 cameraPos;
    public float cameraSize;
    public void returnToMainMenu()
    {
        this.mainMenu.gameObject.SetActive(true);
        this.gameObject.SetActive(false);
        mainMenu.setCamera();
        NetworkManager.getInstance().stopListeningUDP();

    }

    public void goToPartieMenu()
    {
        print("okok\n");
        string ip = serveurList.getCurrentServerIp();
        print("ip: " + ip + "\n");
        if(ip != "")
        {

            print("okok2\n");
            NetworkManager.getInstance().stopListeningUDP();
            NetworkManager.getInstance().setTargetIpAddress(ip);
            /////
            NetworkManager.getInstance().startTCP();
            NetworkManager.getInstance().sendTCPMessage("H\n");
            NetworkManager.getInstance().sendTCPMessage("Hello\n");
            ////
            partieMenu.gameObject.SetActive(true);
            partieMenu.setCamera();
            this.gameObject.SetActive(false);
        }
    }

    private void OnEnable()
    {
        
        PartieManager.getInstance().resetAll();
        serveurList.resetServeurList();
        NetworkManager.getInstance().startListeningUDP(42069);
        MenuMessageSender.getInstance().sendLookForServer();
        
        

    }
    private void OnDisable()
    {
        NetworkManager.getInstance().stopListeningUDP();
    }

    public void setCamera()
    {
        mainCamera.transform.position = cameraPos;
        mainCamera.orthographicSize = cameraSize / 2;
    }
}
