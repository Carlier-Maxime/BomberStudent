using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Net;
using Newtonsoft.Json;
using System;

public class MessageParser : MonoBehaviour
{
    private static MessageParser instance;

    private IMessageReceiver messageReceiver;

    private MessageType currentType = MessageType.None;
    private void Awake()
    {
        if (instance != null)
        {
            GameObject.Destroy(this.gameObject);
        }
        else
        {
            instance = this;
        }
        /*parseMessage("{\"action\":\"maps /list\", \"statut\":\"200\", \"message\":\"ok\",\"nbMapsList\": 1,\"maps\":[{\"id\":0,\"width\":24,\"height\":8,\"content\":\"************************=----------------------==----==============----==----------****--------==------****------------==----============== ----==----------------------=************************\"}]}",IPAddress.Any);
        parseMessage("{\"statut\":\"400\",\"message\": \"Bad request\"}", IPAddress.Any);
        parseMessage("{\"statut\":\"520\",\"message\": \"Unknown Error\"}", IPAddress.Any);
        parseMessage("{\"action\":\"game/create\",\"statut\":\"501\",\"message\": \"cannot create game\"}", IPAddress.Any);*/
    }

    public static MessageParser getInstance()
    {
        return instance;
    }

    public void parseMessage(string message, IPAddress iPAddress)
    {
        int idxAccoladeOuverte = message.IndexOf('{');
        if(idxAccoladeOuverte != -1)
        {
            int idxAccoladeFermante = message.LastIndexOf('}');
            if(idxAccoladeFermante < idxAccoladeOuverte)
            {
                Debug.Log("mauvais message:" + message);
                currentType = MessageType.None;
                return;
            }
            else
            {
                string json = message.Substring(idxAccoladeOuverte, idxAccoladeFermante + 1);
                Message objet = JsonConvert.DeserializeObject<Message>(json);
                treatMessage(objet, iPAddress);
            }

        }
        else if(currentType == MessageType.None)
        {
            message = message.Trim();
            if (message == "hello i'm a bomberstudent server")
            {
                messageReceiver.foundBomberStudentServer(iPAddress);
            }else if(message == "POST player/new")
            {
                currentType = MessageType.PostPlayerNew;
            }else if (message ==  "POST game/ready")
            {
                currentType = MessageType.PostGameReady;
            }else if (message == "POST player/position/update")
            {
                currentType = MessageType.PostPlayerPositionUpdate;
            }else if (message == "POST attack/newbomb")
            {
                currentType = MessageType.PostAttackNewBomb;
            }else if (message == "POST attack/explose")
            {
                currentType = MessageType.PostAttackExplose;
            }else if (message == "POST attack/affect")
            {
                currentType = MessageType.PostAttackAffect;
            }else if (message == "POST game/go")
            {
                messageReceiver.startGame();
            }
            else
            {
                Debug.Log("mauvais message:" + message);

            }
        }
        else
        {
            Debug.Log("mauvais message:" + message);
            currentType = MessageType.None;
        }

        
    }


    public void treatMessage(Message objet, IPAddress iPAddress)
    {
        if (currentType != MessageType.None)
        {
            Debug.Log("C'ets le bon type de message");
            if (currentType == MessageType.PostPlayerNew)
            {
                Debug.Log("C'est le bon message");
                string playerName = objet._additionalData["name"].ToString();
                string coord = objet._additionalData["pos"].ToString();
                string y = coord.Substring(0, coord.IndexOf(','));
                string x = coord.Substring(coord.IndexOf(',') + 1);
                Player player = new Player(playerName, Int32.Parse(x), Int32.Parse(y));
                messageReceiver.addNewPlayer(player);
            }else if(currentType == MessageType.PostGameReady)
            {
                int time = Int32.Parse(objet._additionalData["time"].ToString());
                messageReceiver.displayReady(time);
            }else if (currentType == MessageType.PostPlayerPositionUpdate)
            {
                string playerName = objet._additionalData["player"].ToString();
                string dir = objet._additionalData["dir"].ToString();
                messageReceiver.updatePlayerPos(playerName, dir);
            }else if(currentType == MessageType.PostAttackNewBomb)
            {

                string coord = objet._additionalData["pos"].ToString();
                int y = Int32.Parse(coord.Substring(0, coord.IndexOf(',')));
                int x = Int32.Parse(coord.Substring(coord.IndexOf(',') + 1));
                string type = objet._additionalData["type"].ToString();
                BombType bombType = type == "mine" ? BombType.mine : type == "remote" ? BombType.remote : BombType.classic;
                messageReceiver.poseBomb(new Bomb(new Vector2Int(x, y), bombType));
            }else if(currentType == MessageType.PostAttackExplose)
            {
                string coord = objet._additionalData["pos"].ToString();
                int y = Int32.Parse(coord.Substring(0, coord.IndexOf(',')));
                int x = Int32.Parse(coord.Substring(coord.IndexOf(',') + 1));
                string type = objet._additionalData["type"].ToString();
                BombType bombType = type == "mine" ? BombType.mine : type == "remote" ? BombType.remote : BombType.classic;
                string map = objet._additionalData["map"].ToString();
                int impactDist = Int32.Parse(objet._additionalData["impactDist"].ToString());
                messageReceiver.bombExplode(new Vector2Int(x, y), bombType, impactDist, map);

            }else if(currentType == MessageType.PostAttackAffect)
            {
                int life = Int32.Parse(objet._additionalData["life"].ToString());
                int nbClassicBomb = Int32.Parse(objet._additionalData["nbClassicBomb"].ToString());
                int nbRemoteBomb = Int32.Parse(objet._additionalData["nbRemoteBomb"].ToString());
                int nbMine = Int32.Parse(objet._additionalData["nbMine"].ToString());
                int impactDist = Int32.Parse(objet._additionalData["impactDist"].ToString());
                bool invicible = Boolean.Parse(objet._additionalData["invincible"].ToString());
                PlayerState playerState = new PlayerState();
                playerState.initPlayerState(PartieManager.getInstance().getPlayerName(), life, nbClassicBomb, nbRemoteBomb, nbMine, invicible, impactDist);
                Debug.Log("life:" + playerState.getLife()+","+life);
                messageReceiver.bombAffect(playerState);
            }
            currentType = MessageType.None;
        } else if (Int32.Parse(objet._additionalData["statut"].ToString()) >= 400)
        {
            treatError(objet);
        }
        else
        {
            if(objet._additionalData["action"].ToString() == "map/list")
            {
                Debug.Log("c'est le resultat de l'action get map/list");
            }
            switch (objet._additionalData["action"].ToString())
            {
                case "maps/list":
                    Debug.Log("c'est le resultat de l'action get maps/list");

                    List<Map> mapList = new List<Map>();
                    int nbMaps = Int32.Parse(objet._additionalData["nbMapsList"].ToString());
                    
                    for (int i = 0; i < nbMaps; i++)
                    {
                        int id = Int32.Parse(objet._additionalData["maps"][i]["id"].ToString());
                        int height = Int32.Parse(objet._additionalData["maps"][i]["height"].ToString());
                        int width= Int32.Parse(objet._additionalData["maps"][i]["width"].ToString());
                        string content = objet._additionalData["maps"][i]["content"].ToString();
                        mapList.Add(new Map(id, width, height, content));

                    }

                    messageReceiver.addMapList(mapList);
                    break;
                case "game/list":
                    {
                        Debug.Log("c'est le resultat de l'action get game/list");
                        List<Partie> gameList = new List<Partie>();
                        int nbParties = Int32.Parse(objet._additionalData["nbGamesList"].ToString());
                        for (int i = 0; i < nbParties; i++)
                        {
                            string nameGame = objet._additionalData["games"][i]["name"].ToString();
                            int nbPlayer = Int32.Parse(objet._additionalData["games"][i]["nbPlayer"].ToString());
                            int mapId = Int32.Parse(objet._additionalData["games"][i]["mapId"].ToString());

                            gameList.Add(new Partie(nameGame, nbPlayer, mapId));
                        }
                        messageReceiver.addGameList(gameList);
                    }
                    break;
                case "game/create":
                    {
                        Debug.Log("c'est le resultat de l'action get game/create");
                        int mapId = Int32.Parse(objet._additionalData["mapId"].ToString());
                        int life = Int32.Parse(objet._additionalData["player"]["life"].ToString());
                        int nbClassicBomb = Int32.Parse(objet._additionalData["player"]["nbClassicBomb"].ToString());
                        int nbRemoteBomb = Int32.Parse(objet._additionalData["player"]["nbRemoteBomb"].ToString());
                        int nbMine = Int32.Parse(objet._additionalData["player"]["nbMine"].ToString());
                        int impactDist = Int32.Parse(objet._additionalData["player"]["impactDist"].ToString());
                        bool invicible = Boolean.Parse(objet._additionalData["player"]["invincible"].ToString());
                        PlayerState playerState = new PlayerState();
                        playerState.initPlayerState(PartieManager.getInstance().getPlayerName(), life, nbClassicBomb, nbRemoteBomb, nbMine, invicible, impactDist);
                        List<Player> playerList = new List<Player>();
                        string coord = objet._additionalData["startPos"].ToString();
                        string y = coord.Substring(0, coord.IndexOf(','));
                        string x = coord.Substring(coord.IndexOf(',') + 1);

                        playerList.Add(new Player(PartieManager.getInstance().getPlayerName(), Int32.Parse(x), Int32.Parse(y)));
                        messageReceiver.gameCreate(new PartieInitialState(PartieManager.getInstance().getMapFromId(mapId), playerList, playerState));
                    }







                    //messageReceiver.gameCreate(objet);
                    break;
                case "game/join":
                    {
                        int mapId = Int32.Parse(objet._additionalData["mapId"].ToString());
                        int life = Int32.Parse(objet._additionalData["player"]["life"].ToString());
                        int nbClassicBomb = Int32.Parse(objet._additionalData["player"]["nbClassicBomb"].ToString());
                        int nbRemoteBomb = Int32.Parse(objet._additionalData["player"]["nbRemoteBomb"].ToString());
                        int nbMine = Int32.Parse(objet._additionalData["player"]["nbMine"].ToString());
                        int impactDist = Int32.Parse(objet._additionalData["player"]["impactDist"].ToString());
                        bool invicible = Boolean.Parse(objet._additionalData["player"]["invincible"].ToString());

                        PlayerState playerState = new PlayerState();
                        playerState.initPlayerState(PartieManager.getInstance().getPlayerName(), life, nbClassicBomb, nbRemoteBomb, nbMine, invicible, impactDist);

                        int nbPlayer = Int32.Parse(objet._additionalData["nbPlayers"].ToString());
                        List<Player> playerList = new List<Player>();
                        string coord;
                        string x;
                        string y;
                        for (int i = 0; i < nbPlayer; i++)
                        {
                            coord = objet._additionalData["players"][i]["pos"].ToString();
                            y = coord.Substring(0, coord.IndexOf(','));
                            x = coord.Substring(coord.IndexOf(',') + 1);
                            string playerName = objet._additionalData["players"][i]["name"].ToString();

                            playerList.Add(new Player(playerName, Int32.Parse(x), Int32.Parse(y)));
                        }
                        coord = objet._additionalData["startPos"].ToString();
                        y = coord.Substring(0, coord.IndexOf(','));
                        x = coord.Substring(coord.IndexOf(',') + 1);

                        playerList.Add(new Player(PartieManager.getInstance().getPlayerName(), Int32.Parse(x), Int32.Parse(y)));
                        messageReceiver.joinGame(new PartieInitialState(PartieManager.getInstance().getMapFromId(mapId),playerList,playerState));
                        //messageReceiver.joinGame(objet);
                        Debug.Log("c'est le resultat de l'action get game/join");
                    }
                    break;
                case "attack/bomb":
                    {
                        int life = Int32.Parse(objet._additionalData["player"]["life"].ToString());
                        int nbClassicBomb = Int32.Parse(objet._additionalData["player"]["nbClassicBomb"].ToString());
                        int nbRemoteBomb = Int32.Parse(objet._additionalData["player"]["nbRemoteBomb"].ToString());
                        int nbMine = Int32.Parse(objet._additionalData["player"]["nbMine"].ToString());
                        int impactDist = Int32.Parse(objet._additionalData["player"]["impactDist"].ToString());
                        bool invicible = Boolean.Parse(objet._additionalData["player"]["invincible"].ToString());
                        PlayerState playerState = new PlayerState();
                        playerState.initPlayerState(PartieManager.getInstance().getPlayerName(), life, nbClassicBomb, nbRemoteBomb, nbMine, invicible, impactDist);
                        messageReceiver.bombPosed(playerState);
                        Debug.Log("c'est le resultat de l'action get attack/bomb");
                    }
                    break;
                case "objet/new":
                    //messageReceiver.getItem();
                    Debug.Log("c'est le resultat de l'action get objet/new");
                    break;
                default:
                    break;
            }
        }
    }
    public void treatError(Message objet)
    {
        Debug.Log(objet._additionalData["message"]);
    }

    

  

    public void setMessageReceiver(IMessageReceiver messageReceiver)
    {
        this.messageReceiver = messageReceiver;
    }

}
