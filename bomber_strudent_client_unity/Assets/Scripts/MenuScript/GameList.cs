using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class GameList : MonoBehaviour
{
    public GameObject buttonPrefab;
    public RectTransform rectTransform;
    private RectTransform prefabRectTransform;
    public int maxButton;
    public Sprite selectionButton;
    private List<GameObject> buttonList = new List<GameObject>();
    private List<Partie> gameList = new List<Partie>();
    private int idx = 0;
    int tmp = 0;

    public GameMenu gameMenu;

    public MapGenerator mapGenerator;

    public Button connexionButton;
    public GamePresentation gamePresentation;

    private bool changed = false;

    private void Awake()
    {
        initButton();
        setButtons(0);
        connexionButton.interactable = false;


        /*PartieManager.getInstance().addMap(new Map(1, 5, 5, "*======***==***==***======"));
        PartieManager.getInstance().addMap(new Map(0, 1, 1, "*"));
        PartieManager.getInstance().addMap(new Map(2, 24, 8, "************************=----------------------==----==============----==----------****--------==------****------------==----==============----==----------------------=******************************"));
        *///PartieManager.getInstance().addMap(new Map(1, 5, 5, "************************=----------------------==----==============----==----------****--------==------****------------==----==============----==----------------------=******************************"));
        /*PartieManager.getInstance().addPartie(new Partie("partie1", 2, 1));
        addGame(new Partie("partie1", 2, 1));
        addGame(new Partie("partie2", 2, 2));
        addGame(new Partie("partie3", 5, 0));*/


        //addMap(new Map(1, 5, 5, "======***==***==***======"));
        //addMap(new Map(2, 5, 5, "======*_*==*_*==***======"));
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
            instance.GetComponent<GameButton>().setGameIdx(0);
            instance.GetComponent<GameButton>().setGameList(this);
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
        if (gameList.Count == 0)
        {
            for (int i = 0; i < buttonList.Count; i++)
            {
                buttonList[i].GetComponentInChildren<Text>().text = "";
                buttonList[i].GetComponent<GameButton>().setGameIdx(0);
            }

            connexionButton.interactable = false;
            mapGenerator.initMap(0, 0);
            mapGenerator.setContentMap("");
            gamePresentation.gameObject.SetActive(false);
        }
        else
        {
            gamePresentation.gameObject.SetActive(true);
            connexionButton.interactable = true;
            int centerIdx = buttonList.Count / 2;
            for (int i = 0; i < buttonList.Count; i++)
            {
                int tmp = i - centerIdx;
                int gameIdx = ((tmp + gameList.Count + idx) % gameList.Count + gameList.Count) % gameList.Count;
                string text = gameList[gameIdx].getNameGame().ToString();
                buttonList[i].GetComponentInChildren<Text>().text = text;
                buttonList[i].GetComponent<GameButton>().setGameIdx(gameIdx);
            }
            Map map = PartieManager.getInstance().getMapFromId(gameList[idx].getMapId());
            mapGenerator.initMap(map.getHeight(), map.getWidth());
            mapGenerator.setContentMap(map.getContent());
            gamePresentation.setNbJoueur(gameList[idx].getNbPlayer());
            gamePresentation.setNom(gameList[idx].getNameGame());
        }
        gameMenu.setCamera();
    }

    public void setButtons()
    {
        this.setButtons(idx);
    }

    public void addGame(Partie partie)
    {
        for (int i = 0; i < gameList.Count; i++)
        {
            if (gameList[i].getNameGame() == partie.getNameGame())
                return;
        }
        this.gameList.Add(partie);
        this.setButtons();
    }

    public Partie getCurrentGame()
    {

        return this.gameList.Count > 0 ? this.gameList[this.idx] : null;
    }

    public void down()
    {
        if (gameList.Count > 0)
        {
            int idx = (this.idx + 1) % gameList.Count;
            setButtons(idx);
        }
    }
    public void up()
    {
        if (gameList.Count > 0)
        {
            int idx = this.idx - 1;
            idx = (idx % gameList.Count + gameList.Count) % gameList.Count;
            setButtons(idx);
        }
    }
    public void resetGameList()
    {
        this.gameList.Clear();
        this.setButtons(0);
    }

}
