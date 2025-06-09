# Warhammer10k
Space conquest game simulator

A C++17 strategy simulator where you command fleets of algorithm-based ships to conquer galaxies through pathfinding optimization and resource management.

# How to run

Open a Linux terminal in the game folder and input: ./build.sh

# Features

Galactic conquest simulation on a multipartite graph with up to 20 planets per galaxy

7 algorithm-based ship types with specialized functions

Galaxys can be added from a csv file

FLTK-based GUI for intuitive visualization and control

Eterium resource system with automated mining production

Multiple attack strategies implementing different search algorithms


# System Requirements

C++17 compatible compiler

CMake 3.10+

FLTK 1.3+ (for GUI)

OS: Linux

Clone of the repo: https://github.com/Se3as/Warhammer10k.git


# Units and algorithms

Unit	                   Algorithm	            Function

Pathfinder	               Dijkstra	Reveals        minimum A→B cost between explored nodes
StarMapper	               Floyd-Warshall	       reveals all path costs between explored nodes
Excavator		                                   extracts MINE_YIELD Étherium per interval
Light Assault	           Greedy Search	       fast attack based on partial cost
Medium Assault	           Local Search (2-opt)	   optimizes attack route by edge swapping
Heavy Assault	           Exhaustive Search	   finds optimal attack route through complete exploration
Heavy Assault+	           Exhaustive Search 	   optimized version with branch and bound
RapidSight	               BFS	                   reveals immediate neighbors of a node
DeepProbe	               DFS (up to 3 jumps)	   reveals chain of up to 3 hops from a node

# Combat System

Effective damage calculated as: EffectiveDamage = BASE_DAMAGE / (iterations_executed)²

# Economy

Mines generate MINE_YIELD Étherium per interval

Eterium is used for:

Activating probes (BFS/DFS)

Running pathfinding algorithms (Dijkstra/Floyd-Warshall)

Launching attacks

# WIn Condition

Defeat all galaxy bosses and control all Eterium mines.

# Contributors

Juan Sebastian Loaiza Ospina
Luis Alfredo Arias
Alexander Wang Wu