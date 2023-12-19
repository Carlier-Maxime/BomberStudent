
public class Partie
{
    private string nameGame;
    private int nbPlayer;
    private int mapId;

    public Partie(string nameGame, int nbPlayer, int mapId)
    {
        this.nameGame = nameGame;
        this.nbPlayer = nbPlayer;
        this.mapId = mapId;
    }
    public int getNbPlayer()
    {
        return nbPlayer;
    }
    public string getNameGame()
    {
        return nameGame;
    }
    public int getMapId()
    {
        return mapId;
    }
}
