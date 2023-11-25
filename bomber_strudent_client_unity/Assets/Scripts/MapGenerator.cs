
using UnityEngine;

public class MapGenerator : MonoBehaviour
{

    public Sprite caseSol;
    public Sprite caseMur;
    public Sprite caseMurBlinde;
    public GameObject casePrefab;
    public Vector2 centerRefPoint;
    public string baseContent = "*******" +
                            "*_____*" +
                            "*_===_*" +
                            "*_____*" +
                            "*_____*" +
                            "*_===_*" +
                            "*_____*" +
                            "*******";
    private GameObject[] cases = new GameObject[1];

    private int width;
    private int height;
    private Vector2 refPoint;

    private void Start()
    {
        initMap(8, 7);
    }
    void Update()
    {
        generateMap(baseContent);
    }


    public void initMap(int height, int width)
    {
        this.height = height;
        this.width = width;
        this.refPoint = centerRefPoint - new Vector2Int(height, width) / 2;
        cases = new GameObject[height * width];
        for (int lig = 0; lig < height; lig++)
        {
            for (int col = 0; col < width; col++)
            {
                int idx = lig * width + col;
                float x = refPoint.x + col;
                float y = refPoint.y + (height-lig-1);
                GameObject instance = GameObject.Instantiate(casePrefab, new Vector3(x, y), Quaternion.identity, this.transform);
                cases[idx] = instance;

            }
        }
    }
    public void generateMap( string content)
    {
       
        for (int lig = 0; lig < height; lig++)
        {
            for(int col = 0; col < width; col++)
            {
                Sprite spriteCase;
                int idx = lig * width + col;
                if (content[idx] == '_')
                {
                    spriteCase = caseSol;
                }else if(content[idx] == '=')
                {
                    spriteCase = caseMur;
                }
                else
                {
                    spriteCase = caseMurBlinde;
                }
                cases[idx].GetComponent<SpriteRenderer>().sprite = spriteCase;
                
            }
        }
    }

    public Vector2 getPosForCoord(int x, int y)
    {
        float posX = refPoint.x + x;
        float posY = refPoint.y + y;
        return new Vector2(posX, posY);
    }
    public Vector2 getPosForCoord(Vector2 vector)
    {
        return getPosForCoord((int)vector.x, (int)vector.y);
    }
}
