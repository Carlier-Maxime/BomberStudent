using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class MapList : MonoBehaviour
{
    public GameObject buttonPrefab;
    public RectTransform rectTransform;
    private RectTransform prefabRectTransform;
    public int maxButton;
    public Sprite selectionButton;
    private List<GameObject> buttonList = new List<GameObject>();
    private List<Map> mapList = new List<Map>();
    public MapMenu mapMenu;
    private int idx = 0;
    

   public MapGenerator mapGenerator;

    public Button connexionButton;

    private bool changed = false;

    private void Awake()
    {
        initButton();
        setButtons(0);
        connexionButton.interactable = false;


       /* PartieManager.getInstance().addMap(new Map(1, 5, 5, "*======***==***==***======"));
        PartieManager.getInstance().addMap(new Map(0, 1, 1, "*"));
        PartieManager.getInstance().addMap(new Map(2, 24, 8, "************************=----------------------==----==============----==----------****--------==------****------------==----==============----==----------------------=******************************"));
       */
    }

    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.DownArrow))
        {
            this.down();
        }
        else if (Input.GetKeyDown(KeyCode.UpArrow))
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
            if (i == maxButton / 2)
            {
                instance.GetComponent<Image>().sprite = selectionButton;
            }
            instance.GetComponent<MapButton>().setMapIdx(0);
            instance.GetComponent<MapButton>().setMapList(this);
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
        if (mapList.Count == 0)
        {
            for (int i = 0; i < buttonList.Count; i++)
            {
                buttonList[i].GetComponentInChildren<Text>().text = "";
                buttonList[i].GetComponent<MapButton>().setMapIdx(0);
            }

            connexionButton.interactable = false;
            mapGenerator.initMap(0, 0);
            mapGenerator.setContentMap("");
        }
        else
        {

            connexionButton.interactable = true;
            int centerIdx = buttonList.Count / 2;
            for (int i = 0; i < buttonList.Count; i++)
            {
                int tmp = i - centerIdx;
                int mapIdx = ((tmp + mapList.Count + idx) % mapList.Count + mapList.Count) % mapList.Count;
                string text = mapList[mapIdx].getId().ToString();
                buttonList[i].GetComponentInChildren<Text>().text = text;
                buttonList[i].GetComponent<MapButton>().setMapIdx(mapIdx);
            }
            mapGenerator.initMap(mapList[idx].getHeight(), mapList[idx].getWidth());
            mapGenerator.setContentMap(mapList[idx].getContent());
        }
        mapMenu.setCamera();
    }

    private void setButtons()
    {
        this.setButtons(idx);
    }

    public void addMap(Map map)
    {
        for(int i = 0;i< mapList.Count; i++)
        {
            if (mapList[i].getId() == map.getId())
                return;
        }

            this.mapList.Add(map);
            this.setButtons();
    }

    public Map getCurrentMap()
    {

        return this.mapList.Count > 0 ? this.mapList[this.idx] : null;
    }

    public void down()
    {
        if (mapList.Count > 0)
        {
            int idx = (this.idx + 1) % mapList.Count;
            setButtons(idx);
        }
    }
    public void up()
    {
        if (mapList.Count > 0)
        {
            int idx = this.idx - 1;
            idx = (idx % mapList.Count + mapList.Count) % mapList.Count;
            setButtons(idx);
        }
    }
    public void resetMapList()
    {
        this.mapList.Clear();
        this.setButtons(0);
    }

}
