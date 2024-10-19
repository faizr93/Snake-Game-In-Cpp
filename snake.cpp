#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <vector>
#include <windows.h>
#include <time.h>

const int GRID_SIZE = 8;
const char BACKGROUND_CHAR = '-';
const char SNAKE_BODY_CHAR = 'O';
const char EGG_CHAR = 'X';

std::vector<int> snakePosRows, snakePosCols;
int snakePosRow = 5, snakePosCol = 5;
int eggPosRow, eggPosCol;
int snakeLength = 3;
bool isEggSpawned = false;
char direction = 'd';
char grid[GRID_SIZE][GRID_SIZE];

// Function declarations
void initializeGrid(); // , SUPER EPIC CODE GO BRR
void printGrid();
void spawnEgg();
void handleMovement();
void growSnake();
void checkGameOver();
void gameLoop();
void showMainMenu();

// Entry point of the program
int main() {
    showMainMenu();
    initializeGrid();
    gameLoop();
    return 0;
}

// Show the main menu
void showMainMenu() {
    while (true) {
        system("cls");
        printf("Snake Game\nPress Enter to START\n");
        if (getch() == 13) break; // Wait for Enter key
    }
}

// Game loop
void gameLoop() {
    do {
        system("cls");
        handleMovement();
        spawnEgg(); // Spawn egg if needed
        growSnake();
        grid[snakePosRow][snakePosCol] = SNAKE_BODY_CHAR; // Draw snake head
        if (snakePosRows.size() >= snakeLength) {
            grid[snakePosRows.front()][snakePosCols.front()] = BACKGROUND_CHAR; // Remove tail
            snakePosRows.erase(snakePosRows.begin());
            snakePosCols.erase(snakePosCols.begin());
        }
        snakePosRows.push_back(snakePosRow);
        snakePosCols.push_back(snakePosCol);
        wrapIndices();
        checkGameOver();
        printGrid();
        Sleep(200); // Control speed
    } while (direction != '0'); // Exit condition
}

// Check if the game is over
void checkGameOver() {
    if (grid[snakePosRow][snakePosCol] == SNAKE_BODY_CHAR) {
        printf("\n\nGAME OVER\n\nPress Enter to restart.");
        getch(); // Wait for Enter key
        main(); // Restart the game
    }
}

// Handle snake movement and direction changes
void handleMovement() {
    if (kbhit()) {
        char inputKey = tolower(getch());
        if (inputKey == 'w' && direction != 's') direction = inputKey;
        else if (inputKey == 's' && direction != 'w') direction = inputKey;
        else if (inputKey == 'a' && direction != 'd') direction = inputKey;
        else if (inputKey == 'd' && direction != 'a') direction = inputKey;
    }
    switch (direction) {
        case 'a': snakePosCol--; break;
        case 'd': snakePosCol++; break;
        case 'w': snakePosRow--; break;
        case 's': snakePosRow++; break;
    }
}

// Spawn an egg at a random position
void spawnEgg() {
    if (!isEggSpawned) {
        do {
            eggPosRow = rand() % GRID_SIZE;
            eggPosCol = rand() % GRID_SIZE;
        } while (grid[eggPosRow][eggPosCol] == SNAKE_BODY_CHAR);
        grid[eggPosRow][eggPosCol] = EGG_CHAR; // Place the egg on the grid
        isEggSpawned = true; // Mark that an egg is spawned
    }
}

// Wrap snake position indices around the grid
void wrapIndices() {
    snakePosRow = (snakePosRow + GRID_SIZE) % GRID_SIZE;
    snakePosCol = (snakePosCol + GRID_SIZE) % GRID_SIZE;
}

// Print the game grid
void printGrid() {
    printf("WASD to move (press '0' to quit):\n");
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            printf("%c ", grid[i][j]);
        }
        printf("\n");
    }
}

// Initialize the game grid
void initializeGrid() {
    for (int i = 0; i < GRID_SIZE; i++)
        for (int j = 0; j < GRID_SIZE; j++)
            grid[i][j] = BACKGROUND_CHAR; // Fill grid with background character
}
