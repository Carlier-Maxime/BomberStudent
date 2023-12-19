using System.Net;
using System.Collections.Generic;
using UnityEngine;

public interface IMessageReceiver
{
    public void foundBomberStudentServer(IPAddress iPAddress);
    public void addMapList(List<Map> mapList);
    public void addGameList(List<Partie> gameList);
    public void gameCreate(PartieInitialState partieInitialState);
    public void joinGame(PartieInitialState partieInitialState);
    public void poseBomb(Bomb bomb);
    public void getItem(PlayerState playerState);
    public void addNewPlayer(Player player);
    public void displayReady(int time);
    public void updatePlayerPos(string playerName, string dir);
    public void startGame();
    public void bombPosed(PlayerState playerState);
    public void bombExplode(Vector2Int coord, BombType bombType, int impactDist, string newMap);
    public void bombAffect(PlayerState playerState);

}
