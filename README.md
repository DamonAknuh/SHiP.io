# **SHiP.io**
**_" A piece of SHiP "_**

## Summary

SHiP.io is a 2D online multiplayer space-battle game. Players start by controlling a tiny 1 square simple spaceship flying through a 2D grid. Resource icons will appear randomly on the grid for players to pick up. These resource icons allow upgrades to ship, enable weapons, and increase speed.  The objective of the game is to be the last ship standing.

## Requirements

Deliver a simple and creative computer game which showcases some form of end user 2 user interaction. 

### Objective
 -  Implement a server application which can manage and respond to requests, messages, and data from multiple clients.
 -  Implement a client application which can interact with other end-users through usage of mouse or keyboard.

### Constraints

### Requirement Engineering

## Design

## Implementation

## Building

build the program with the following command  

for Server  
```
    /c/REPOS/SHiP.io/server$ make ../SHIP_SER
```
```
    C:\REPOS\SHiP.io> .\SHIP_SER.exe
```

for client  
```
    /c/REPOS/SHiP.io/server$ make ../SHIP_SER
```
```
    C:\REPOS\SHiP.io> .\SHIP_CLI.exe
```

### TODOS:
  - [ ] - SETUP
    - [X] - Makefiles
    - [X] - Folder structure
    - [ ] - Batch script to compile both sources.
    - [ ] - Test Framework
  - [X] - GAME OUTPUT
    - [X] - Console
    - [X] - shot handler
    - [X] - Independent game width and height
    - [ ] - No need to redraw if no client inputs and no packets recieved. 
    - [ ] - Replace console with openGL or 2D game library. 
  - [ ] - INPUT OUTPUT
    - [X] - WASD Movement
    - [X] - Shoot conditions
    - [X] - player/fruit collisions
    - [X] - Game exit key 't'
    - [X] - Choose player avatar
    - [ ] - input server IP address
  - [ ] - CLIENT SERVER
    - [X] - Client ID Registration
    - [X] - Client send Avatar & and recieve enemies avatar
    - [X] - packet header struct
    - [X] - packet content struct
    - [X] - Client send data to server
    - [ ] - Server send data to clients
    - [ ] - Client recieve update data from server
    - [ ] - Game over conditions and trigger
    - [ ] - Enemy player shoots against other player. 
    - [ ] - Play again conditions and logic. . 

## Maintenance


## References && Resources

Client Server Guide:
    - http://www.codersblock.org/blog/multiplayer-fps-part-1

idk what this is
    - https://hero.handmade.network/episode/code/day001

Game Engine Web-pages:

2d sprites
    - https://www.libsdl.org/

2d game engines
    - http://www.garagegames.com/products/torque-2d
    - https://www.cocos.com/en/products#Cocos2d-x
