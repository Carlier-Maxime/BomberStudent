

public class Map
{
    private int id;
    private int width;
    private int height;
    private string content;

    public Map(int id, int width, int height, string content)
    {
        this.id = id;
        this.width = width;
        this.height = height;
        this.content = content;
    }

    public int getId()
    {
        return id;
    }
    public int getWidth()
    {
        return width;
    }
    public int getHeight()
    {
        return height;
    }
    public string getContent()
    {
        return content;
    }

}
