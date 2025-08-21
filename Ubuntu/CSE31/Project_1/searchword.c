#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declarations of the two functions you will implement
void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);
int bSize;

// Structure to store the location of a cell
struct location {
    int y;
    int x;
};

// Helper function to convert lowercase letters to uppercase
char biggering(char s) {
    if (s > 96) {
        s = s - 32;
    }
    return s;
}

void cheeseBlock(struct location *grater, int pathLength) {
    int **cheddar = (int**)malloc(bSize * sizeof(int*));
    for (int i = 0; i < bSize; i++) {
        *(cheddar + i) = (int*)malloc(bSize * sizeof(int));
        memset(*(cheddar + i), 0, bSize * sizeof(int));
    }

    // Mark the path on the cheddar matrix
    for (int i = 0; i < pathLength; i++) {
        int y = (grater + i)->y;
        int x = (grater + i)->x;
        *(*(cheddar + y) + x) = (*(*(cheddar + y) + x) * 10) + (i + 1);
    }

    // Print the cheddar matrix
    for (int i = 0; i < bSize; i++) {
        for (int j = 0; j < bSize; j++) {
            printf("%d\t", *(*(cheddar + i) + j));
        }
        printf("\n");
    }

    // Free allocated memory
    for (int i = 0; i < bSize; i++) {
        free(*(cheddar + i));
    }
    free(cheddar);
}

// Recursive function to search for the word in the puzzle
int look(int index, int x, int y, char **matrix, char *word, int **visited, struct location *path) {
    // Base case: If the entire word is found
    if (index == strlen(word)) {
        return 1;
    }

    // Boundary checks
    if (x < 0 || x >= bSize || y < 0 || y >= bSize) {
        return 0;
    }

    // Check if the current cell matches the current character in the word
    if (biggering(*(*(matrix + y) + x)) == biggering(*(word + index))) {
        // Temporarily mark the current cell as visited
        *(*(visited + y) + x) = 1;

        // Add the current cell to the path
        (path + index)->y = y;
        (path + index)->x = x;

        // Explore all 8 adjacent cells
        for (int i = y - 1; i <= y + 1; i++) {
            for (int j = x - 1; j <= x + 1; j++) {
                if (i == y && j == x) continue; // Skip the current cell
                if (look(index + 1, j, i, matrix, word, visited, path)) {
                    return 1; // Word found
                }
            }
        }

        // Backtrack: Unmark the current cell as visited
        *(*(visited + y) + x) = 0;
    }

    return 0; // Word not found
}


// Main function, DO NOT MODIFY
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
        return 2;
    }
    int i, j;
    FILE *fptr;

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

    // Read the size of the puzzle block
    fscanf(fptr, "%d\n", &bSize);

    // Allocate space for the puzzle block and the word to be searched
    char **block = (char**)malloc(bSize * sizeof(char*));
    char *word = (char*)malloc(20 * sizeof(char));

    // Read puzzle block into 2D arrays
    for (i = 0; i < bSize; i++) {
        *(block + i) = (char*)malloc(bSize * sizeof(char));
        for (j = 0; j < bSize - 1; ++j) {
            fscanf(fptr, "%c ", *(block + i) + j);
        }
        fscanf(fptr, "%c \n", *(block + i) + j);
    }
    fclose(fptr);

    printf("Enter the word to search: ");
    scanf("%s", word);

    // Print out original puzzle grid
    printf("\nPrinting puzzle before search:\n");
    printPuzzle(block);

    // Call searchPuzzle to search for the word in the puzzle
    searchPuzzle(block, word);

    return 0;
}

void printPuzzle(char** arr) {
    // This function will print out the complete puzzle grid (arr).
    for (int i = 0; i < bSize; i++) {
        for (int j = 0; j < bSize; j++) {
            printf("%c ", *(*(arr + i) + j));
        }
        printf("\n");
    }
    printf("\n");
}

void searchPuzzle(char** arr, char* word) {
    // This function checks if arr contains the search word.
    int i, j;
    int found = 0;

    // Allocate memory for the visited matrix
    int **visited = (int**)malloc(bSize * sizeof(int*));
    for (i = 0; i < bSize; i++) {
        *(visited + i) = (int*)malloc(bSize * sizeof(int));
        memset(*(visited + i), 0, bSize * sizeof(int)); //sets every value in line to 0
    }

    // Allocate memory for the path
    struct location *path = (struct location*)malloc(strlen(word) * sizeof(struct location));

    // Search for the word starting from each cell
    for (i = 0; i < bSize; i++) {
        for (j = 0; j < bSize; j++) {
            if (look(0, j, i, arr, word, visited, path)) {
                found = 1;
                break;
            }
        }
        if (found) break;
    }

    // Print the result
    if (found) {
        printf("Word found!\nPrinting the search path:\n");
        cheeseBlock(path, strlen(word)); // Pass the length of the word
    } else {
        printf("Word not found!\n");
    }

    // Free allocated memory
    for (i = 0; i < bSize; i++) {
        free(*(visited + i));
    }
    free(visited);
    free(path);
}