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
    public GameObject explosionPrefab;

    public List<Bomb> nextBomb = new List<Bomb>();

    private bool changed = false;
    private void Update()
    {
        if (changed)
        {
            changed = false;
            updateBomb();
        }
    }
    private void updateBomb()
    {
        for(int i =0; i < nextBomb.Count; i++)
        {
            Bomb bomb = nextBomb[i];
            if (bomb.getBombType() == BombType.classic)
            {
                addClassicBomb(bomb.getCoord());
            }
            else if (bomb.getBombType() == BombType.remote)
            {
                addRemoteBomb(bomb.getCoord());
            }
            else if (bomb.getBombType() == BombType.mine)
            {
                addMine(bomb.getCoord());
            }
        }
        nextBomb.Clear();
    }
    public void addBomb(Bomb bomb)
    {
        
        nextBomb.Add(bomb);
        changed = true;
    }
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

    public void deleteBomb(Vector2Int coord, BombType bombType)
    {
        List<Bomb> bombList;
        if (bombType == BombType.classic) bombList = classicBombList;
        else if (bombType == BombType.remote) bombList = remoteBombList;
        else bombList = mineList;
        for (int i = 0; i < bombList.Count; i++)
        {
            Bomb bomb = bombList[i];
            if (bomb.getCoord().Equals(coord))
            {
                bombList.Remove(bomb);
                GameObject.Destroy(bomb.gameObject);
            }
        }
        
    }
    public void deleteBomb(Bomb bomb)
    {
        deleteBomb(bomb.getCoord(), bomb.getBombType());
    }
    public void explodeBomb(Vector2Int coord, BombType bombType, int impactDist)
    {
        List<Bomb> bombList;
        if (bombType == BombType.classic) bombList = classicBombList;
        else if (bombType == BombType.remote) bombList = remoteBombList;
        else bombList = mineList;
        for (int i = 0; i < bombList.Count; i++)
        {
            Bomb bomb = bombList[i];
            if (bomb.getCoord().Equals(coord))
            {
                bombList.Remove(bomb);
                //GameObject.Destroy(bomb.gameObject);
                bomb.explode(impactDist);
            }
        }

    }

}
