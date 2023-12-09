using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MainMenu : MonoBehaviour
{
    public GameObject serverMenu;
    public void goToServerMenu()
    {
        serverMenu.SetActive(true);
        this.gameObject.SetActive(false);
    }

    public void quitGame()
    {
        Application.Quit();
    }
}
