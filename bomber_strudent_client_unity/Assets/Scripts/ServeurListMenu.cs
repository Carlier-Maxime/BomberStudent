using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ServeurListMenu : MonoBehaviour
{
    public GameObject mainMenu;
    public ServeurList serveurList;
    
    public void returnToMainMenu()
    {
        this.mainMenu.SetActive(true);
        this.gameObject.SetActive(false);
        NetworkManager.getInstance().stopListeningUDP();
    }

    private void OnEnable()
    {
        serveurList.resetServeurList();
        NetworkManager.getInstance().startListeningUDP(42069);
        MenuMessageSender.getInstance().sendLookForServer();
        

    }
    private void OnDisable()
    {
        NetworkManager.getInstance().stopListeningUDP();
    }
}
