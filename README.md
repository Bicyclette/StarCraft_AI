# INF584 - Starcraft Bot

## Team Members

- Emeric Marguet
- Sakula Hys
- Mathias Velo
- Eyal Benaroche

## Project Description

The goal of this project is to create a **Protoss Bot** and beat other players in the course of the INF584A course at Ecole Polytechnique.
The bot is developped on starcraft Brood of War using the BWAPI library with the original codebase of [Dave Churchill](https://github.com/davechurchill/STARTcraft)

## Bot Strategy

### Units and Technology Branch

### Data Structures

*Here will follow the description and representation of the BT we have implemented*

### Debugging features

### Distribution of tasks

## Setup Instructions:

This project can only run on Windows and the Starcraft game must be downloaded separately and then put on the `/windows/starcraft/` folder.

1. git clone this repository 

```bash
git clone https://github.com/Bicyclette/StarCraft_AI.git
```

2. Download and unzip [Starcraft Broodwar 1.16.1](http://www.cs.mun.ca/~dchurchill/startcraft/scbw_bwapi440.zip) to the included `windows/starcraft` folder
3. Run `windows/bin/RunStarterBotAndStarcraft.bat` which will launch the bot executable and Starcraft / BWAPI
4. Open `windows/visualstudio/StartCraft.sln` in Visual Studio 2022 to modify / recompile the code
