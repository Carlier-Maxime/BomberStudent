using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class ServerButton : MonoBehaviour
{
    private int serverIdx;
    public Button button;

    private ServeurList serveurList;
    public void selectServer()
    {
        serveurList.setButtons(serverIdx);
    }

    public void setServerIdx(int idx)
    {
        this.serverIdx = idx;
    }
    public void setServeurList(ServeurList serveurList)
    {
        this.serveurList = serveurList;
    }

}
