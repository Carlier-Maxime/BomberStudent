using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ServeurList : MonoBehaviour
{
    public GameObject buttonPrefab;
    public RectTransform rectTransform;
    private RectTransform prefabRectTransform;
    public int maxButton;
    public Sprite selectionButton;
    private List<GameObject> buttonList = new List<GameObject>();
    private List<string> serverList = new List<string>();
    private int idx = 0;

    public Button connexionButton;

    private bool changed = false;

    private void Awake()
    {
        initButton();
        setButtons(0);
        connexionButton.interactable = false;


        
      /*  addServer("Keine");
        addServer("Mokou");
        addServer("Cirno");*/
    }

    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.DownArrow))
        {
            this.down();
        }else if (Input.GetKeyDown(KeyCode.UpArrow))
        {
            this.up();
        }
        if (changed)
        {
            changed = false;
            updateButton();
        }
    }

    private void initButton()
    {
        prefabRectTransform = buttonPrefab.GetComponent<RectTransform>();
        float height = prefabRectTransform.rect.height;
        float width = prefabRectTransform.rect.width;

        float posX = rectTransform.rect.width / 2;
        for (int i = 0; i < maxButton; i++)
        {
            GameObject instance = Instantiate(buttonPrefab, this.transform);
            instance.GetComponent<RectTransform>().anchoredPosition = new Vector3(posX, i * height, 0);
            if(i == maxButton / 2)
            {
                instance.GetComponent<Image>().sprite = selectionButton;
            }
            instance.GetComponent<ServerButton>().setServerIdx(0);
            instance.GetComponent<ServerButton>().setServeurList(this);
            buttonList.Add(instance);
        }
    }

    public void setButtons(int idx)
    {
        this.idx = idx;
        changed = true;
        
    }

    public void updateButton()
    {
        if (serverList.Count == 0)
        {
            for (int i = 0; i < buttonList.Count; i++)
            {
                buttonList[i].GetComponentInChildren<Text>().text = "";
                buttonList[i].GetComponent<ServerButton>().setServerIdx(0);
            }

            connexionButton.interactable = false;
        }
        else
        {

            connexionButton.interactable = true;
            int centerIdx = buttonList.Count / 2;
            for (int i = 0; i < buttonList.Count; i++)
            {
                int tmp = i - centerIdx;
                int serverIdx = ((tmp + serverList.Count + idx) % serverList.Count + serverList.Count) % serverList.Count;
                string text = serverList[serverIdx];
                buttonList[i].GetComponentInChildren<Text>().text = text;
                buttonList[i].GetComponent<ServerButton>().setServerIdx(serverIdx);
            }
        }
    }

    private void setButtons()
    {
        this.setButtons(idx);
    }

    public void addServer(string serv)
    {
        if (!this.serverList.Contains(serv))
        {
            this.serverList.Add(serv);
            this.setButtons();

        }
    }

    public string getCurrentServerIp()
    {

        return this.serverList.Count > 0? this.serverList[this.idx] : "";
    }

    public void down()
    {
        if (serverList.Count > 0)
        {
            int idx = (this.idx + 1) % serverList.Count;
            setButtons(idx);
        }
    }
    public void up()
    {
        if (serverList.Count > 0)
        {
            int idx = this.idx - 1;
            idx = (idx % serverList.Count + serverList.Count) % serverList.Count;
            setButtons(idx);
        }
    }
    public void resetServeurList()
    {
        this.serverList.Clear();
        this.setButtons(0);
    }

}
