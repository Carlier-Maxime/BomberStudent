
using UnityEngine;
using UnityEngine.UI;

public class MapButton : MonoBehaviour
{
    private int mapIdx;

    private MapList mapList;
    public void selectMap()
    {
        mapList.setButtons(mapIdx);
    }

    public void setMapIdx(int idx)
    {
        this.mapIdx = idx;
    }
    public void setMapList(MapList mapList)
    {
        this.mapList = mapList;
    }

}
