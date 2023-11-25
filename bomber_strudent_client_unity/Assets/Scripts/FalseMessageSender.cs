using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FalseMessageSender :MonoBehaviour,  MessageSender
{
    public FalseMessageReceiver messageReceiver;
    public PlayerManager playerManager;
    public PlayerState playerState;
    public void Up()
    {
        messageReceiver.updatePositionPlayer(playerState.namePlayer,"up");
    }
    public void Down()
    {
        messageReceiver.updatePositionPlayer(playerState.namePlayer, "down");
    }
    public void Left()
    {
        messageReceiver.updatePositionPlayer(playerState.namePlayer, "left");
    }
    public void Right()
    {
        messageReceiver.updatePositionPlayer(playerState.namePlayer, "right");
    }

    public void PlaceBomb(BombType bombType)
    {
        Player player = playerManager.getPlayer(playerState.namePlayer);
        if (bombType == BombType.classic && playerState.getNbClassicBomb() > 0)
        {
            playerState.setNbClassicBomb(playerState.getNbClassicBomb() - 1);

            messageReceiver.placeBomb(bombType, player.getPos(),playerState);
        }
        else if (bombType == BombType.remote && playerState.getNbRemoteBomb() > 0)
        {
            playerState.setNbRemoteBomb(playerState.getNbRemoteBomb() - 1);

            messageReceiver.placeBomb(bombType, player.getPos(), playerState);
        }
        else if (bombType == BombType.mine && playerState.getNbMine() > 0)
        {
            playerState.setNbMine(playerState.getNbMine() - 1);

            messageReceiver.placeBomb(bombType, player.getPos(), playerState);
        }
    }
}
