using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bomb : MonoBehaviour
{
    private Vector2Int coord;
    private BombType bombType;
    private bool hasExploded = false;
    public GameObject explosionPrefab;
    private int impactDist;
    public Bomb() { }
    public Bomb(Vector2Int coord, BombType bombType)
    {
        this.coord = coord;
        this.bombType = bombType;
    }

    private void Update()
    {
        if (hasExploded)
        {
            Explosion explosion = Instantiate(explosionPrefab).GetComponent<Explosion>();
            explosion.setExplosion(coord, impactDist, MapGenerator.getInstance());
            GameObject.Destroy(this.gameObject);
        }
    }
    public void setExplosionPrefab(GameObject prefab)
    {
        this.explosionPrefab = prefab;
    }
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
    public void explode(int impactDist)
    {
        this.impactDist = impactDist;
        this.hasExploded = true;
    }

}
