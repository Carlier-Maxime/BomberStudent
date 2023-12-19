
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
    [SerializeField]
    private string map;
    private GameObject[] cases = new GameObject[1];

    private int width;
    private int height;
    private Vector2 refPoint;

    private bool changed = false;

    /*private void Start()
    {
        initMap(8, 7);
        setContentMap(baseContent);
        
    }*/
    private static MapGenerator instance;
    private void Awake()
    {
        if(instance != null)
        {
            GameObject.Destroy(this);
        }
        else
        {
            instance = this;
        }
    }
    public static MapGenerator getInstance()
    {
        return instance;
    }
    private void Update()
    {
        if (changed)
        {
            changed = false;
            generateMap();
        }
    }

    public void initMap(int height, int width)
    {
        for(int i = 0; i < cases.Length; i++)
        {
            GameObject.Destroy(cases[i]);
        }
        this.height = height;
        this.width = width;
        this.refPoint = /*centerRefPoint*/ new Vector2(width/-2f+0.5f, height/-2f+0.5f);
        cases = new GameObject[height * width];
        for (int lig = 0; lig < height; lig++)
        {
            for (int col = 0; col < width; col++)
            {
                int idx = lig * width + col;
                float x =  refPoint.x + col;
                float y =  refPoint.y + (-lig-1+height);
                GameObject instance = GameObject.Instantiate(casePrefab, new Vector3(x, y), Quaternion.identity, this.transform);
                instance.transform.localPosition = new Vector3(x, y);
                cases[idx] = instance;

            }
        }
        
    }
    public void generateMap()
    {
       
        for (int lig = 0; lig < height; lig++)
        {
            for(int col = 0; col < width; col++)
            {
                Sprite spriteCase;
                int idx = lig * width + col;
                
                if (map[idx] == '-')
                {
                    spriteCase = caseSol;
                }else if(map[idx] == '=')
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
    public void setContentMap(string content)
    {
        if (content.Length >= width * height)
        {
            this.map = content;
            changed = true;
        }
        
    }

    public char getCase(int x, int y)
    {
        if(x>=0 && x<width && y>=0 && y<height)
            return map[y * width + x];
        return ' ';
    }

    public char getCase(Vector2Int coord)
    {
        return getCase(coord.x, coord.y);
    }

    public int getWidth()
    {
        return width;
    }
    public int getHeight()
    {
        return height;
    }

    public void initMap(Map map)
    {
        initMap(map.getHeight(), map.getWidth());
        setContentMap(map.getContent());
    }
    
}
