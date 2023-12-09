using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MenuManager : MonoBehaviour
{

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.A))
        {
            NetworkManager.getInstance().initUpdClient("255.255.255.255");
            NetworkManager.getInstance().sendUDPMessage("looking for bomberstrudent server");
        }
    }
}
