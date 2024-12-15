# 2270-Final-Project
## Real-Time Leaderboard System
### Project Data Structure Implemented

This project implements a Red-Black Tree (RBT) to create a real-time leaderboard system. The RBT is used to efficiently manage players and their scores while supporting operations such as insertion, deletion, rank queries, top-k queries, and range queries.

## Short Explanation of the Data Structure

A **Red-Black Tree** is a type of self-balancing binary search tree that ensures logarithmic time complexity for operations like insertion, deletion, and search. The key properties of a Red-Black Tree are:

**Node Colors**: Each node is either red or black.

**Root is Black**: The root node is always black.

**Red Node Constraints**: Red nodes cannot have red children (no two consecutive red nodes).

**Black Height**: Every path from a node to its descendant leaves contains the same number of black nodes.

These properties ensure the tree remains balanced, providing efficient performance even as the number of nodes grows.

Each node in the leaderboard's RBT represents a player and stores:

**Player ID**: A unique identifier for each player.

**Score**: The player’s current score.

**Subtree Size**: The size of the subtree rooted at the node, used for efficient rank calculations.

The leaderboard supports the following key operations:

**Insert or Update**: Add a new player or update an existing player’s score.

**Rank Query**: Retrieve a player’s current rank based on their score.

**Top-k Query**: Retrieve the top-k players.

## Instructions to Run the Project
### Prerequisites

**C++ Compiler**: Ensure you have a C++ compiler installed, such as g++.

**Development Environment**: Use any code editor or IDE like Visual Studio Code, CLion, or a simple text editor with terminal access.

Steps to Compile and Run

**Clone or Download the Project**:

Clone the repository or download the project folder.

**Navigate to the Project Directory**:

cd <project-directory>

**Compile the Code**:
Use the g++ compiler to compile the program:

g++ -o leaderboard leaderboard_rbt.cpp

**Run the Executable**:
Execute the compiled program:
```
./leaderboard
```

### Sample Outputs

**Insert Players**:
The program will insert players with their scores into the leaderboard.

**Rank Queries**:
Retrieve the rank of a player based on their score.

**Top-k Queries**:
Display the top-k players from the leaderboard.

### Example Usage

Sample input/output interaction from the program:

**Inserted players**: Player 1 (Score: 100), Player 2 (Score: 200), Player 3 (Score: 150).

**Rank Query**:
```
Rank of player with score 150: 2
```
**Top-k Query**:
```
Top 2 players:
Player ID: 2, Score: 200
Player ID: 3, Score: 150
```


