#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <vector>
#include <windows.h>
#include <time.h>

const int GRID_SIZE = 7;
const char BACKGROUND_CHAR = '-';
const char SNAKE_BODY_CHAR = 'O';
const char EGG_CHAR = 'X';

std::vector<int> snakePosRows;
std::vector<int> snakePosCols;
int snakePosRow = 5;
int snakePosCol = 5;
int eggPosRow = 2;
int eggPosCol = 2;
int snakeLength = 3;
bool isEggSpawned = false;

char direction = 'd';
char grid[GRID_SIZE][GRID_SIZE];

// Function declarations
void printGrid();
void wrapIndices();
void storeSnakePosition();
void removeTail();
void growSnake();
void handleMovement();
void spawnEgg();
void checkGameOver();
void initializeGrid();
void showMainMenu();
void gameLoop();

// Entry point of the program
int main() {
    showMainMenu();
    initializeGrid();
    gameLoop();
    return 0; // Added return statement for main
}

// Game loop for the Snake game
void gameLoop() {
    do {
        system("cls");
        storeSnakePosition(); // Keep track of the snake's body
        handleMovement();
        wrapIndices(); // Ensure snake stays within bounds
        checkGameOver();
        growSnake();
        spawnEgg(); // Generate egg position
        grid[snakePosRow][snakePosCol] = SNAKE_BODY_CHAR; // Draw snake head
        removeTail(); // Move the snake
        system("cls");
        printGrid();
        Sleep(650); // Control the speed of the game
    } while (direction != '0'); // Exit condition
}

// Function to show the main menu
void showMainMenu() {
    do {
        system("cls");
        printf(R"(
  /$$$$$$                      /$$                
 /$$__  $$                    | $$                
| $$  \__/ /$$$$$$$   /$$$$$$ | $$   /$$  /$$$$$$ 
|  $$$$$$ | $$__  $$ |____  $$| $$  /$$/ /$$__  $$ 
 \____  $$| $$  \ $$  /$$$$$$$| $$$$$$/ | $$$$$$$$ 
 /$$  \ $$| $$  | $$ /$$__  $$| $$_  $$ | $$_____/  
|  $$$$$$/| $$  | $$|  $$$$$$$| $$ \  $$|  $$$$$$$  
 \______/ |__/  |__/ \_______/|__/  \__/ \_______/  
                                                    
    Made By Faiz(Helped by GPT and Google))");
        printf("\n\n\t\tPress Enter to START\n\t\t");
    } while (getch() != 13); // Wait for Enter key
}

// Check if the game is over
void checkGameOver() {
    if (grid[snakePosRow][snakePosCol] == SNAKE_BODY_CHAR) {
        printf("\n\nGAME OVER, Your Score was %d, Maximum Possible was %d\n\n",snakeLength,GRID_SIZE*GRID_SIZE);
        Sleep(5000);
        main();
        // Restart the game
    }
}

// Grow the snake if an egg is eaten
void growSnake() {
    if (grid[snakePosRow][snakePosCol] == EGG_CHAR) {
        isEggSpawned = false;
        snakeLength++;
    }
}

// Handle snake movement and direction changes
void handleMovement() {
    if (kbhit()) { // Check if a key is pressed
        char inputKey = getch(); // Get the latest key pressed
        inputKey = tolower(inputKey); // Handle lowercase for WASD keys

        if (inputKey == 'w' || inputKey == 'a' || inputKey == 's' || inputKey == 'd') {
            if (!((inputKey == 'w' && direction == 's') || 
                   (inputKey == 's' && direction == 'w') || 
                   (inputKey == 'a' && direction == 'd') || 
                   (inputKey == 'd' && direction == 'a'))) {
                direction = inputKey; // Update direction if valid
            }
        }
    }

    // Move the snake based on the current direction
    switch (direction) {
        case 'a': snakePosCol--; break;
        case 'd': snakePosCol++; break;
        case 'w': snakePosRow--; break;
        case 's': snakePosRow++; break;
    }
}

// Spawn an egg at a random position
void spawnEgg() {
    if (!isEggSpawned) { // If no egg is currently spawned
        do {
            eggPosRow = rand() % GRID_SIZE;
            eggPosCol = rand() % GRID_SIZE;
        } while (grid[eggPosRow][eggPosCol] == SNAKE_BODY_CHAR); // Ensure it doesn't spawn on the snake

        grid[eggPosRow][eggPosCol] = EGG_CHAR; // Place the egg on the grid
        isEggSpawned = true; // Mark that an egg is spawned
    }
}

// Remove the tail of the snake
void removeTail() {
    if (snakePosRows.size() >= snakeLength) {
        int tailRow = snakePosRows[0];
        int tailCol = snakePosCols[0];
        grid[tailRow][tailCol] = BACKGROUND_CHAR; // Remove tail from the grid

        snakePosRows.erase(snakePosRows.begin());
        snakePosCols.erase(snakePosCols.begin());
    }
}

// Store the current position of the snake
void storeSnakePosition() {
    snakePosRows.push_back(snakePosRow);
    snakePosCols.push_back(snakePosCol); // Storing snake positions
}

// Wrap snake position indices around the grid
void wrapIndices() {
    snakePosRow = (snakePosRow + GRID_SIZE) % GRID_SIZE;
    snakePosCol = (snakePosCol + GRID_SIZE) % GRID_SIZE; // Wrapping logic
}

// Print the game grid
void printGrid() {
    printf("WASD to move (press '0' to quit): \n\n");
    for (int i = 0; i < GRID_SIZE; i++) {
        printf("       ");
        for (int j = 0; j < GRID_SIZE; j++) {
            printf("%c ", grid[i][j]);
        }
        printf("\n");
    }
}

// Initialize the game grid
void initializeGrid() {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = BACKGROUND_CHAR; // Fill grid with background character
        }
    }
}
