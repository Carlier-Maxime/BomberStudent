using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Explosion : MonoBehaviour
{
    private List<GameObject> explosionPartList=new List<GameObject>();
    public  GameObject explosionPartPrefab;
    public float duration;
    private bool exploded = false;

    private void FixedUpdate()
    {
        if (exploded)
        {
            if ((duration -= Time.fixedDeltaTime) <= 0)
            {
                foreach (GameObject g in explosionPartList)
                {
                    GameObject.Destroy(g);
                }
                GameObject.Destroy(this.gameObject);
            }
        }
    }

    public void setExplosion(Vector2Int coord, int impactDist, MapGenerator mapGenerator)
    {
        exploded = true;
        exploseInDirection(coord, new Vector2Int(1, 0),impactDist,mapGenerator);
        exploseInDirection(coord, new Vector2Int(-1, 0), impactDist, mapGenerator);
        exploseInDirection(coord, new Vector2Int(0, -1), impactDist, mapGenerator);
        exploseInDirection(coord, new Vector2Int(0, 1), impactDist, mapGenerator);
    }

    private void exploseInDirection(Vector2Int coord, Vector2Int dir, int impactDist, MapGenerator mapGenerator)
    {
        Vector2Int currentCoord = coord;
        while (impactDist >= 0)
        {
            char mapCase= mapGenerator.getCase(currentCoord);
            if(mapCase == '_')
            {
                explosionPartList.Add(GameObject.Instantiate(explosionPartPrefab, mapGenerator.getPosForCoord(currentCoord.x, currentCoord.y), Quaternion.identity, this.transform));
                impactDist -= 1;
                currentCoord += dir;
            }
            else if(mapCase == '=')
            {
                explosionPartList.Add(GameObject.Instantiate(explosionPartPrefab, mapGenerator.getPosForCoord(currentCoord.x, currentCoord.y), Quaternion.identity, this.transform));
                impactDist -= 2;
                currentCoord += dir;
            }
            else
            {
                impactDist = -1;
            }
        }
    }
}
