//
//  day10.c
//  advent-of-code
//
//  Created by Mikaela Nicole Ramos on 11/2/24.
//

#include "day10.h"
#include "string.h"
#include "stdbool.h"

//40927 - too high
//27281 - too high
//13639 - too high
///Users/mikaelanicoleramos/Library/Developer/Xcode/DerivedData/advent-of-code-hkwimnpfjnxzkagbqvpdyrdebwgv

typedef struct position{
    int row;
    int col;
    char pipe;
    long distance;
    bool visited;
} Position;

Position positions[140][143];
long maxDistance = 0;
long nodesVisited = 0;

void findTheEndOfPipeLoop(Position* currentPosition, int rowsNum, int colsNum){
    int row = currentPosition->row;
    int col = currentPosition->col;
    
    if (maxDistance < currentPosition->distance){
        maxDistance = currentPosition->distance;
    }
    
    currentPosition->visited = true;
    nodesVisited++;
        
    // check row above
    if (row > 0 && (currentPosition->pipe == '|' || currentPosition->pipe == 'J' || currentPosition->pipe == 'L')){
        Position above = positions[row-1][col];
        if (currentPosition->row > 0 && above.pipe != '-' && above.pipe != 'J' && above.pipe != 'L'){
            if (above.visited == false){
                positions[row-1][col].distance = positions[row][col].distance + 1;
                findTheEndOfPipeLoop(&positions[row-1][col], rowsNum, colsNum);
            }
        }
    }
    // check row below
    if (row < 139 && (currentPosition->pipe == '|' || currentPosition->pipe == 'F' || currentPosition->pipe == '7')){
        Position below = positions[row+1][col];
        if (currentPosition->row < rowsNum && below.pipe != '-' && below.pipe != 'F' && below.pipe != '7'){
            if (below.visited == false){
                positions[row+1][col].distance = positions[row][col].distance + 1;
                findTheEndOfPipeLoop(&positions[row+1][col], rowsNum, colsNum);
            }
        }
    }
    // check left
    if (col > 0 && (currentPosition->pipe == '-' || currentPosition->pipe == 'J' || currentPosition->pipe == '7')){
        Position left = positions[row][col-1];
        if (currentPosition->col > 0 && left.pipe != '|' && left.pipe != 'J' && left.pipe != '7'){
            if (left.visited == false){
                positions[row][col-1].distance = positions[row][col].distance + 1;
                findTheEndOfPipeLoop(&positions[row][col-1], rowsNum, colsNum);
            }
        }
    }
    // check right
    if (col < 142 && (currentPosition->pipe == '-' || currentPosition->pipe == 'F' || currentPosition->pipe == 'L')){
        Position right = positions[row][col+1];
        if (currentPosition->col < colsNum && right.pipe != '|' && right.pipe != 'F' && right.pipe != 'L'){
            if (right.visited == false){
                positions[row][col+1].distance = positions[row][col].distance + 1;
                findTheEndOfPipeLoop(&positions[row][col+1], rowsNum, colsNum);
            }
        }
    }
}

int getTilesInBetweenPipes(int row){
    int pipesInBetween = 0;
    
    for (int c = 0; c < 143; c++){
        if (positions[row][c].visited == true){
            printf("pipe found: %i\n", c);
            c++;
            while (c < 143 && positions[row][c].visited == false){
                pipesInBetween++;
                c++;
            }
            printf("pipe closed at %i\n", c);
        }
    }
    printf("unvisited pipes in between row %i is %i\n", row, pipesInBetween);
    return pipesInBetween;
}
void getFarthest(int row, int col, int rowsNum, int colsNum){
    /*
     0 -6820
     1 - 1
     2 - 6820
     3 - 6820
     4 -6820
     5 -6820
     */
    char possiblePipes[6] = { '|', '-', 'F', 'J', 'L', '7'};
    for (int p =0; p<6; p++)
    {
        printf("using pipe %c\n", possiblePipes[p]);
        positions[row][col].pipe = possiblePipes[p];
        findTheEndOfPipeLoop(&positions[row][col], rowsNum, colsNum);
        printf("maximum distance using pipe %c is %ld\n", possiblePipes[p], maxDistance);
        
        for (int r=0; r<140; r++){
            for (int c=0; c<143; c++){
                if (r == row && c == col){
                    printf("\033[1;31m%c\033[0m", positions[r][c].pipe);
                }else if (positions[r][c].distance > 0){
                    printf("\033[35;106m%c\033[m", positions[r][c].pipe);
                } else {
                    printf("%c", positions[r][c].pipe);
                }
            }
            printf("\n");
        }
        printf("total nodes visited: %ld\n", nodesVisited);
    }
}

void day10(void){
    FILE* file = fopen("/Users/mikaelanicoleramos/Documents/GitHub/advent-of-code/resources/day-10.txt", "r");
    
    char line[143];
    int rows = 0;
    int startRow = 0, startCol = 0;
    
    while (fgets(line, sizeof(line), file)) {
        line[strlen(line)-1] = '\0';
        for (int c=0; c<strlen(line); c++){
            positions[rows][c].pipe = line[c];
            positions[rows][c].row = rows;
            positions[rows][c].col = c;
            positions[rows][c].distance = 0;
            positions[rows][c].visited = false;
            
            if (line[c] == 'S'){
                startRow = rows;
                startCol = c;
            }
        }
        rows++;
    }
    
    getFarthest(startRow, startCol, 140, 143);
    
    printf("position of S %i-%i\n", startRow, startCol);
    printf("maximum distance from the start pipe: %ld\n", maxDistance);
    printf("distance = %ld\n", (maxDistance + 1) / 2);
    
    int pipesInBetween = 0;
    for (int r = 0; r<140; r++){
        pipesInBetween += getTilesInBetweenPipes(r);
    }
    printf("all unvisited nodes in between pipes: %i\n", pipesInBetween);
}
