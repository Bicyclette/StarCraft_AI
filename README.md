# INF584 - Starcraft Bot

## Team Members

- Eyal Benaroche
- Sakula Hys
- Emeric Marguet
- Mathias Velo

## Project Description

The goal of this project is to create a **Protoss Bot** and beat other players in the INF584A course at Ecole Polytechnique.
The bot is developped on StarCraft : Brood War using the BWAPI library with the original codebase of [Dave Churchill](https://github.com/davechurchill/STARTcraft)

## Bot Strategy

The overall strategy of the bot is to follow a certain build oder, i.e. deterministic actions during the game. This is gradually incremented during the 
game to follow the said order, depending on what stage of the game is bot is actually in.\
Once the determined build order is completed, the bot is set on 'automatic mode' to deal with these tasks more independently.\
In parallel, a behavior tree can describe the management of units and resources. When a condition is met, the bot starts building or
creating units, depending on the other statistics, like number of units or resource. (see below for details : Data Structures)\

*use of scout ?*

For the battling strategy, we chose our bot to be rather offensive. Depending on the race of the enemy, the way of dealing with their units will
be different.
Typically, a Zerg enemy is known to be handled more easily when gated, therefore in this case, the bot should build a bottleneck at the entrance of 
the base with buildings.

### Units and Technology Branch

Following the specific build order, the exploration of the technology branch is constrained to stay efficient.
The developed technology is the vital buildings (Pylons and Assimilators), and, on the other hand, basic buildings to produce battling units.
In depth, the exploration does not go deeper than Cybernetic Cores.\
In the implemented strategy, the main units are Probes for mining and construction, and Dragoons for efficient offensive power. 

*send scout ? (impending)*

### Data Structures

The main bot is following a behaviour tree for most of his behaviour. We have developped in parallele other data structure such as Final State Machine (FSM) that are described later on with the Build-Order State Diagram.

```mermaid
flowchart TD

A{Entry Point} --> BB{Repeat Forever}
BB --> MainSelector(Main Loop Selector)
MainSelector --> WorkersActionMinerals{{Action Farm Minerals}}
MainSelector --> WorkersDecoratorGas{Send workers to gas}
WorkersDecoratorGas --> WorkersActionGas{{send worker to gas}}



MainSelector --> UnitSelector(Build Units)

UnitSelector --> ProbeDecoratorBuild{Build Probe}
ProbeDecoratorBuild --> ProbeActionBuild{{Build Probe}}

UnitSelector --> DragoonDecoratorBuild{Build Dragoon}
DragoonDecoratorBuild --> DragoonActionBuild{{Build Dragoon}}

UnitSelector --> ZealotDecoratorBuild{Build Zealot}
ZealotDecoratorBuild --> ZealotActionBuild{{Build Zealot}}



MainSelector --> BuildingSelector(Build Buildings)

BuildingSelector --> PylonDecoratorBuild{Build Pylon}
PylonDecoratorBuild --> PylonActionBuild{{Build Pylon}}

BuildingSelector --> GateDecoratorBuild{Build Gate}
GateDecoratorBuild --> GateActionBuild{{Build Gate}}


MainSelector --> ResearchSelector(Research Technology)

ResearchSelector --> ResearchDecoratorSingularity{Research Singularity Charge}
ResearchDecoratorSingularity --> ResearchActionSingularity{{Research Singularity}}


MainSelector --> BuildOrderSelector(Follow Build Order State Diagram)

```

### Debugging features

The other features are mainly for debugging and confort, which are the ones already present in the initial code :
bounding boxes and health bars display.

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
