//
//  day11.c
//  advent-of-code
//
//  Created by Mikaela Nicole Ramos on 11/6/24.
//

#include "day11.h"
#include "string.h"

int minNum(int a, int b){
    if (a < b){
        return a;
    }
    return b;
}

int maxNum(int a, int b){
    if (a > b){
        return a;
    }
    return b;
}

void day11part1(void){
    FILE* file = fopen("/Users/mikaelanicoleramos/Documents/GitHub/advent-of-code/resources/day-11.txt", "r");
    
    char line[143];
    //int rowGalaxyCounts[140] = {0};
    int rowGalaxyCounts[140] = {0};
    int colGalaxyCounts[143] = {0};
    int galaxies[20020][2] = {};
    
    int realGalaxyCount = 0;
    int row = 0;
    while (fgets(line, sizeof(line), file)) {
        line[strlen(line)-1] = '\0';
        for (int c = 0; c < strlen(line); c++){
            if (line[c] == '#'){
                galaxies[realGalaxyCount][0] = row;
                galaxies[realGalaxyCount][1] = c;
                rowGalaxyCounts[row]++;
                colGalaxyCounts[c]++;
                realGalaxyCount++;
            }
        }
        row++;
    }
    
    int rowDistances[140] = {0};
    int colDistances[143] = {0};

    for (int row=1; row<140; row++){
        if (rowGalaxyCounts[row] == 0)
            rowDistances[row] = rowDistances[row-1] + 2;
        else
            rowDistances[row] = rowDistances[row-1] + 1;
    }
    
    for (int col=1; col<143; col++){
        if (colGalaxyCounts[col] == 0)
            colDistances[col] = colDistances[col-1] + 2;
        else
            colDistances[col] = colDistances[col-1] + 1;
    }
    
    long sumDistancePairs = 0;
    for (int g1=0; g1<realGalaxyCount; g1++){
        for (int g2=g1+1; g2<realGalaxyCount; g2++){
            int g1_row = galaxies[g1][0];
            int g1_col = galaxies[g1][1];
            int g2_row = galaxies[g2][0];
            int g2_col = galaxies[g2][1];
            
            int rowDistance = rowDistances[maxNum(g1_row, g2_row)] - rowDistances[minNum(g1_row, g2_row)];
            int colDistance = colDistances[maxNum(g1_col, g2_col)] - colDistances[minNum(g1_col, g2_col)];
            int totalDistance = rowDistance + colDistance;
            sumDistancePairs += totalDistance;
        }
    }
    
    printf("sum of distances: %ld\n", sumDistancePairs);
}

