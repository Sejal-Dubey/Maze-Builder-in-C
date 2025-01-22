#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAZE_SIZE 5

struct node {
    int nindex;
    struct node* next;
};

struct node* addn(struct node* node, int nindex) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->nindex = nindex;
    newNode->next = NULL;

    if (node == NULL) {
        return newNode;
    }

    struct node* current = node;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    return node;
}

void inputMazeAdjacencyList(char maze[MAZE_SIZE][MAZE_SIZE], struct node* adjacencyLists, int mazeSize) {
    for (int i = 0; i < mazeSize; i++) {
        for (int j = 0; j < mazeSize; j++) {
            if (maze[i][j] == ' ') {
                int index = i * MAZE_SIZE + j;
                adjacencyLists[index].nindex = index;
                adjacencyLists[index].next = NULL;
                // Check and add neighboring cells
                if (i > 0 && maze[i - 1][j] == ' ')
                    adjacencyLists[index].next = addn(adjacencyLists[index].next, (i - 1) * MAZE_SIZE + j);
                if (j > 0 && maze[i][j - 1] == ' ')
                    adjacencyLists[index].next = addn(adjacencyLists[index].next, i * MAZE_SIZE + (j - 1));
                if (i < MAZE_SIZE - 1 && maze[i + 1][j] == ' ')
                    adjacencyLists[index].next = addn(adjacencyLists[index].next, (i + 1) * MAZE_SIZE + j);
                if (j < MAZE_SIZE - 1 && maze[i][j + 1] == ' ')
                    adjacencyLists[index].next = addn(adjacencyLists[index].next, i * MAZE_SIZE + (j + 1));
            }
        }
    }
}

void displayMazeWithHighlightedPath(char maze[MAZE_SIZE][MAZE_SIZE], int mazeSize, int* path, int pathLength) {
    printf("Maze with Highlighted Path:\n");
    for (int i = 0; i < mazeSize; i++) {
        printf("{");
        for (int j = 0; j < mazeSize; j++) {
            int cell = i * MAZE_SIZE + j;
            bool isOnPath = false;

            // Check if the current cell is on the path
            for (int k = 0; k < pathLength; k++) {
                if (cell == path[k]) {
                    isOnPath = true;
                    break;
                }
            }

            // Display the cell with appropriate highlighting
            if (isOnPath) {
                printf("'1'");
            } else if (maze[i][j] == 'W') {
                printf("'W'");
            } else {
                printf("'0'");
            }

            if (j < mazeSize - 1) {
                printf(", ");
            }
        }
        printf("},\n");
    }
}

void freeMemory(struct node* adjacencyLists, int mazeSize) {
    for (int i = 0; i < mazeSize * mazeSize; i++) {
        struct node* currentNode = adjacencyLists[i].next;
        while (currentNode != NULL) {
            struct node* temp = currentNode;
            currentNode = currentNode->next;
            free(temp);
        }
    }
}

void bfs(char maze[MAZE_SIZE][MAZE_SIZE], struct node* adjacencyLists, int mazeSize, int start, int end, int* path, int* pathLength) {
    // Initialize visited array to keep track of visited cells
    bool visited[MAZE_SIZE * MAZE_SIZE];
    for (int i = 0; i < mazeSize * mazeSize; i++) {
        visited[i] = false;
    }

    // Queue for BFS
    int queue[MAZE_SIZE * MAZE_SIZE];
    int front = -1;
    int rear = -1;

    // Parent array to store the previous cell for each cell
    int parent[MAZE_SIZE * MAZE_SIZE];

    // Mark start as visited and enqueue it
    visited[start] = true;
    queue[++rear] = start;
    parent[start] = -1;

    while (front != rear) {
        // Dequeue a cell from the queue
        int currentCell = queue[++front];

        // Check if this is the end cell
        if (currentCell == end) {
            break;
        }

        // Enqueue neighboring cells
        struct node* currentNeighbor = adjacencyLists[currentCell].next;
        while (currentNeighbor != NULL) {
            int neighborCell = currentNeighbor->nindex;
            if (!visited[neighborCell]) {
                visited[neighborCell] = true;
                queue[++rear] = neighborCell;
                parent[neighborCell] = currentCell;
            }
            currentNeighbor = currentNeighbor->next;
        }
    }

    // Backtrack to find the path
    int currentCell = end;
    int count = 0;
    while (currentCell != -1) {
        path[count++] = currentCell;
        currentCell = parent[currentCell];
    }

    // Reverse the path
    for (int i = 0; i < count / 2; i++) {
        int temp = path[i];
        path[i] = path[count - i - 1];
        path[count - i - 1] = temp;
    }

    *pathLength = count;
}

int main() {
    char maze[MAZE_SIZE][MAZE_SIZE] = {
        {'S', 'W', ' ', 'W', ' '},
        {' ', ' ', 'W', ' ', ' '},
        {' ', 'W', ' ', 'W', ' '},
        {' ', ' ', ' ', ' ', ' '},
        {'W', ' ', 'W', ' ', 'E'},
    };

    // Assuming 'S' is at the top-left corner (0, 0)
    int startCell = 0;

    // Assuming 'E' is at the bottom-right corner
    int endCell = MAZE_SIZE * MAZE_SIZE - 1;

    // Initialize adjacency lists
    struct node* adjacencyLists = (struct node*)malloc(MAZE_SIZE * MAZE_SIZE * sizeof(struct node));

    // Initialize adjacency lists
    for (int i = 0; i < MAZE_SIZE * MAZE_SIZE; i++) {
        adjacencyLists[i].nindex = -1;  // Initialize as -1 for cells with walls
        adjacencyLists[i].next = NULL;
    }

    // Create adjacency list representation of the maze
    inputMazeAdjacencyList(maze, adjacencyLists, MAZE_SIZE);

    // Perform BFS to find the path from 'S' to 'E'
    int path[MAZE_SIZE * MAZE_SIZE];
    int pathLength = 0;
    bfs(maze, adjacencyLists, MAZE_SIZE, startCell, endCell, path, &pathLength);

    // Display the maze with the highlighted path
    displayMazeWithHighlightedPath(maze, MAZE_SIZE, path, pathLength);

    // Free allocated memory
    freeMemory(adjacencyLists, MAZE_SIZE);

    return 0;
}
