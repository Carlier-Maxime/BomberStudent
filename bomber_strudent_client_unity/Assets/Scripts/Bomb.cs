using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bomb : MonoBehaviour
{
    private Vector2Int coord;
    private BombType bombType;
    
    public void setBombType(BombType bombType)
    {
        this.bombType = bombType;
    }

    public BombType getBombType()
    {
        return this.bombType;
    }
    public void setCoord(Vector2Int coord, MapGenerator mapGenerator)
    {
        this.coord = coord;
        this.transform.position = mapGenerator.getPosForCoord(coord);
    }

    public Vector2Int getCoord()
    {
        return this.coord;
    }

}
