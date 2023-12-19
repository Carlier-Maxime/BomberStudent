using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class MainMenu : MonoBehaviour
{
    public ServeurListMenu serverMenu;

    public Camera mainCamera;
    public Vector3 cameraPos;
    public float cameraSize;

    public Text textField;
    public GameObject warningText;
    public void goToServerMenu()
    {
        string nom = textField.text.Trim();
        if (nom.Length > 0)
        {
            warningText.SetActive(false);
            PartieManager.getInstance().setPlayerName(nom);
            serverMenu.gameObject.SetActive(true);
            serverMenu.setCamera();
            this.gameObject.SetActive(false);
        }
        else
        {
            warningText.SetActive(true);
        }
    }

    public void quitGame()
    {
        Application.Quit();
    }

    public void setCamera()
    {
        mainCamera.transform.position = cameraPos;
        mainCamera.orthographicSize = cameraSize / 2;
    }

    
}
