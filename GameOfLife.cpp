/* 
 * File:   GameOfLife.cpp
 * Author: Daniela
 *
 * Created on February 18, 2013, 10:30 AM
 */
#include <iostream>
#include <fstream>



int rows;
int columns;
int generations;

using namespace std;

void buildInitialPattern(int** source) {
    int tmp;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            scanf("%d", &tmp);
            source[i][j] = (tmp > 0);
        }
    }
}

void printMatrix(int** source) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("|%d|", source[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void copy(int** source, int** target) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            target[i][j] = source[i][j];
        }
    }
}

int countNeighbours(int** source, int row, int column) {
    int res = 0;
    int endRow = row + 1;
    int endColumn = column + 1;

    for (int startRow = row - 1; startRow <= endRow; startRow++) {
        for (int startColumn = column - 1; startColumn <= endColumn; startColumn++) {
            if (startRow >= 0 && startRow < rows) {
                if (startColumn >= 0 && startColumn < columns) {
                    if (startColumn != column || startRow != row) {
                        res += source[startRow][startColumn] == 1 ? 1 : 0;
                    }
                }
            }
        }
    }
    return res;
}

void buildGeneration(int** matrix, int** backup) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            int neighbours = countNeighbours(matrix, i, j);

            if (neighbours < 2) {
                backup[i][j] = 0;
            }
            if (neighbours == 3) {
                backup[i][j] = 1;
            }
            if (neighbours > 3) {
                backup[i][j] = 0;
            }
        }
    }
    copy(backup, matrix);
}

int** buildMatrix() {
    int** matrix = (int**) malloc(rows * sizeof (int*));

    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*) calloc(columns, sizeof (int));
    }

    return matrix;
}

void destroyMatrix(int** matrix) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }

    free(matrix);
}

int play() {
    int** matrix = buildMatrix();
    int** backup = buildMatrix();

    buildInitialPattern(matrix);
    copy(matrix, backup);

    while (generations--) {
        buildGeneration(matrix, backup);        
    }
    
    printMatrix(matrix);

    destroyMatrix(matrix);
    destroyMatrix(backup);
}

int main() {
    freopen("GameOfLife.in", "r", stdin);

    int testCases;
    scanf("%d", &testCases);

    while (testCases--) {
        printf("----------------------Test---------------------\n");
        scanf("%d %d %d", &rows, &columns, &generations);
        play();
        printf("\n");
    }

    return 0;
}

