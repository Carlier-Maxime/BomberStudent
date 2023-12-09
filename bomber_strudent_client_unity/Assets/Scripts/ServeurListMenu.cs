using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ServeurListMenu : MonoBehaviour
{
    public GameObject mainMenu;
    public ServeurList serveurList;
    int tmp = 0;
    
    public void returnToMainMenu()
    {
        this.mainMenu.SetActive(true);
        this.gameObject.SetActive(false);
    }

    private void OnEnable()
    {
        serveurList.resetServeurList();
        if (tmp == 0)
        {
            serveurList.addServer("Reimu");
            serveurList.addServer("Yukari");
        }
        else
        {
            serveurList.addServer("Keine");
            serveurList.addServer("Mokou");

        }
        tmp++;
        MenuMessageSender.getInstance().sendLookForServer();
    }
}
