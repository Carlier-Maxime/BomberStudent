using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PartieManager : MonoBehaviour
{
    private List<Map> mapList = new List<Map>();
    private List<Partie> partieList = new List<Partie>();
    public MapList mapListUI;
    public GameList gameListUI;
    private string playerName="player1";
    private PartieInitialState partieInitialState;

    private static PartieManager instance;
    

    private void Awake()
    {
        if (PartieManager.instance != null)
        {
            GameObject.Destroy(this.gameObject);
        }
        else
        {
            PartieManager.instance = this;
            DontDestroyOnLoad(this);
        }

    }

    public static PartieManager getInstance()
    {
        return instance;
    }

    public Map getMapFromId(int id)
    {
        for(int i=0; i < mapList.Count; i++)
        {
            if (mapList[i].getId() == id)
                    return mapList[i];
        }
        return null;
    }

    public void addMap(Map map)
    {
        this.mapList.Add(map);
        mapListUI.addMap(map);
        

    }
    public void addPartie(Partie partie)
    {
        this.partieList.Add(partie);
        gameListUI.addGame(partie);

    }
    public void resetAll()
    {
        resetMapList();
        resetGameList();
    }
    public void resetMapList()
    {
        this.mapList.Clear();
        mapListUI.resetMapList();
    }
    public void resetGameList()
    {
        this.gameListUI.resetGameList();
        partieList.Clear();
    }

    public string getPlayerName()
    {
        return playerName;
    }
    public void setPlayerName(string playerName)
    {
        this.playerName = playerName;
    }
    public void setPartieInitialState(PartieInitialState partieInitialState)
    {
        this.partieInitialState = partieInitialState;
    }
    public PartieInitialState GetPartieInitialState()
    {
        return partieInitialState;
    }
    
}
