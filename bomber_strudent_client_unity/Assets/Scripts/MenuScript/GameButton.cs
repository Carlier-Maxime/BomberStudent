
using UnityEngine;
using UnityEngine.UI;

public class GameButton : MonoBehaviour
{
    private int gameIdx;

    private GameList gameList;
    public void selectGame()
    {
        gameList.setButtons(gameIdx);
    }

    public void setGameIdx(int idx)
    {
        this.gameIdx = idx;
    }
    public void setGameList(GameList gameList)
    {
        this.gameList = gameList;
    }

}
