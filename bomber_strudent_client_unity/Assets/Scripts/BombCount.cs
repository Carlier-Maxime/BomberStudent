
using UnityEngine;
using UnityEngine.UI;

public class BombCount : MonoBehaviour
{
    public Image classicBomb;
    public Image remoteBomb;
    public Image mine;

    public Color selectColor;
    public Color unselectColor;

    public Text classicCount;
    public Text remoteCount;
    public Text mineCount;
    // Start is called before the first frame update
    void Start()
    {
        selectBomb(BombType.classic);
    }

    public void selectBomb(BombType bombType)
    {
        classicBomb.color = bombType == BombType.classic ? selectColor : unselectColor;
        remoteBomb.color = bombType == BombType.remote? selectColor : unselectColor;
        mine.color = bombType == BombType.mine ? selectColor : unselectColor;
    }

    public void setClassicCount(int nbBomb)
    {
        this.classicCount.text = nbBomb.ToString();
    }
    public void setRemoteCount(int nbBomb)
    {
        this.remoteCount.text = nbBomb.ToString();
    }
    public void setMineCount(int nbBomb)
    {
        this.mineCount.text = nbBomb.ToString();
    }
}
