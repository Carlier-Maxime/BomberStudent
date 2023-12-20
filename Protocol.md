# Protocol Client/Server

reference all protocol used for communication client / server.  
All messages finish by a '\0' for prevent multiple messages sending in one. (except UDP)

## Error message

TCP Bad request
```json
{
"statut": 400,
"message": "Bad request"
}
```

Internal Error
```json
{
"statut": 520,
"message": "Unknown Error"
}
```

Action error

```json
{
"action":"the/action", "statut":501, "message":"cannot action"
}
```

## Search Server

client request (UDP):  
``looking for bomberstudent servers``

server response:  
``hello i'm a bomberstudent server``

## Get map list

client request (TCP):  
``GET maps/list``

server response:  
```json
{
"action":"maps/list", "statut":200, "message":"ok",
"nbMapsList": 1,
"maps":[
{
"id":0,
"width":6,
"height":6,
"content":"******=-==-==--*-==-*--==-==-=******"
}
]
}
```

## Get game list

client request (TCP):  
``GET game/list``

server response:  
```json
{
"action":"game/list", "statut":200, "message":"ok", "nbGamesList": 2,
"games":[ {
"name":"game1",
"nbPlayer":2,
"mapId":0
},
{
"name":"game2",
"nbPlayer":2,
"mapId":1
}]
}
```

## Create Game

client request (TCP):  
```
POST game/create
{
"name":"game1",
"mapId": 1
}
```

server response:  
```json
{
"action":"game/create", "statut":201, "message":"game created",
"nbPlayers":0,
"mapId" : 1,
"startPos":"3,2", "player":{
"life":100,
"speed":1,
"nbClassicBomb":2,
"nbMine":0,
"nbRemoteBomb":1,
"impactDist":2,
"invincible":false
}
}
```

## Join Game

client request (TCP):  
```
POST game/join
{
"name":"game"
}
```

server response:  
```json
{
"action":"game/join", "statut":201, "message":"game joined",
"nbPlayers":2,
"mapId" : 1,
"players":[{"name":"player1","pos":"0,0"}, {"name":"player2","pos":"0,79"}],
"startPos":"5,3",
"player":{
    "life":100,
    "speed":1,
    "nbClassicBomb":1,
    "nbMine":0,
    "nbRemoteBomb":0,
    "impactDist":2,
    "invincible":false
}
}
```

server send to other players:
```
POST player/new
{
    "name:" "nom",
    "pos":"x,y"
}
```

## Start Game

All players join a game before game start.  
For start a game, the player created the game send request:  
``POST game/start``

Server responds to all players:  
```
POST game/ready
{
"time": 3
}
```

After time cool down, the server send to all players:  
``POST game/go``

## Move Player

For player move, client send request:  
```
POST player/move
{
"move":"up" // down, left, right
}
```

if move successful, server responds to all players:  
```
POST player/position/update
{
"player":"player2",
"dir":"up"
}
```

## Pose Bomb

for player pose a bomb, client send request:  
```
POST attack/bomb
{
"type":"classic" //mine, remote
}
```

if bomb posed successful, server respond to a client:  
```json
{
"action":"attack/bomb", "statut":201, "message":"bomb is armed at pos x,y",
"player":{
    "life":100,
    "speed":1,
    "nbClassicBomb":1,
    "nbMine":0,
    "nbRemoteBomb":0,
    "impactDist":2,
    "invincible":false
}
}
```
and send to other players:  
```
POST attack/newbomb
{
"pos":"x,y",
"type":"classic" //mine, remote
}
```

## Explode Bomb

when bomb explode a server send of all player:
```
POST attack/explose
{
"pos":"5,3",
"type":"classic",
"impactDist":2,
"map":"..."
}
```
map string is the new content of map.

If bomb explosion touch player, server send to player:
```
POST attack/affect
{
"life":70,
"speed":1,
"nbClassicBomb":1,
"nbMine":0,
"nbRemoteBomb":0,
"impactDist":2,
"invincible":false,
}
```

for explode remote bomb the owner of remote bomb send:  
```POST attack/remote/go```

## Leave Game

For player leave the game, a client close socket TCP.  
And a server send to other players:  
```
POST player/leave
{
"name": playerName
}
```
