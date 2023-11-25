using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BombManager : MonoBehaviour
{
    List<Bomb> classicBombList = new List<Bomb>();
    List<Bomb> remoteBombList = new List<Bomb>();
    List<Bomb> mineList = new List<Bomb>();

    public GameObject classicBombPrefab;
    public GameObject minePrefab;
    public GameObject remoteBombPrefab;

    public MapGenerator mapGenerator;


    public void addClassicBomb(Vector2Int coord)
    {
        GameObject instance = Instantiate(classicBombPrefab, this.transform);
        Bomb bomb = instance.GetComponent<Bomb>();
        bomb.setBombType(BombType.classic);
        bomb.setCoord(coord, mapGenerator);
        classicBombList.Add(bomb);
    }
    public void addRemoteBomb(Vector2Int coord)
    {
        GameObject instance = Instantiate(remoteBombPrefab, this.transform);
        Bomb bomb = instance.GetComponent<Bomb>();
        bomb.setBombType(BombType.remote);
        bomb.setCoord(coord, mapGenerator);
        remoteBombList.Add(bomb);
    }
    public void addMine(Vector2Int coord)
    {
        GameObject instance = Instantiate(minePrefab, this.transform);
        Bomb bomb = instance.GetComponent<Bomb>();
        bomb.setBombType(BombType.mine);
        bomb.setCoord(coord, mapGenerator);
        mineList.Add(bomb);
    }
}
