
using UnityEngine;

public class Player
{
    private int x;
    private int y;
    private string playerName;

    public Player(string playerName, int x, int y)
    {
        this.playerName = playerName;
        this.x = x;
        this.y = y;
    }

    public void setPosition(int x, int y)
    {
        this.x = x;
        this.y = y;
    }
    public void setPosition(Vector2Int vector)
    {
        this.x = vector.x;
        this.y = vector.y;
    }

    public Vector2Int getPos()
    {
        return new Vector2Int(x, y);
    }
    public string getName()
    {
        return this.playerName;
    }
}
