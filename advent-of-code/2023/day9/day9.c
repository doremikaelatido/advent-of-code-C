//
//  day9.c
//  advent-of-code
//
//  Created by Mikaela Nicole Ramos on 9/15/24.
//

#include "day9.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
#include "stdbool.h"

long parseInputEnd(char* strInput){
    char* tok = strtok(strInput, " ");
    int i = 20;
    char *end;
    
    long levels[20][21] = {{0}};
    do
        levels[0][i--] = strtol(tok, &end, 10);
    while ((tok = strtok(NULL, " ")));
    
    int indexes[20] = {0};
    int lengths[20] = {0};
    lengths[0] = 21;
    long lastVal = 0;

    int zerosFound = 0;
    
    while (true){
        for (int level=0; level<19; level++){
            int levelIndex = indexes[level];
            if (level != 0 && lengths[level] != levelIndex + 2)
                break;
            else
                lengths[level+1]++;
            
            if (indexes[level] > 21 - level - 1){
                zerosFound = 4;
                break;
            }
            levels[level+1][levelIndex] = levels[level][levelIndex] - levels[level][levelIndex+1];
            lastVal = levels[level+1][levelIndex];
            indexes[level]++;
        }
        
        if (lastVal == 0)
            break;
    }
    
    long nextVal = levels[0][0];
    for (int l=1; l<20; l++){
        nextVal += levels[l][0];
    }
    
    printf("Next value: %ld\n", nextVal);
    return nextVal;
}

long parseInputStart(char* strInput){
    char* tok = strtok(strInput, " ");
    int i = 0;
    char *end;
    
    long levels[21][21] = {{0}};
    do
        levels[0][i++] = strtol(tok, &end, 10);
    while ((tok = strtok(NULL, " ")));
        
    int indexes[21] = {0};
    int lengths[21] = {0};
    lengths[0] = 21;
    int levelWhereZero = 0;
    bool breakLoop = false;
    
    while (!breakLoop){
        breakLoop = false;
        for (int level=0; level<21; level++){
            int levelIndex = indexes[level];
            if (level != 0 && levelIndex == 0 && lengths[level] < 2)
                break;
            else
                lengths[level+1]++;
            
            levels[level+1][levelIndex] = levels[level][levelIndex+1] - levels[level][levelIndex];
            indexes[level] += 1;
            levelWhereZero = level;
            
            if (levelIndex > 1)
                breakLoop = levels[level][0] == 0 && levels[level][1] == 0;
            if (breakLoop) break;
        }
    }
    
    long prevVal = 0;
    for (int l=levelWhereZero-1; l>-1; l--){
        prevVal = levels[l][0] - prevVal;
    }
    
    /*for (int r=0; r<21; r++){
        for (int c=0; c<21-r; c++){
            printf(" %ld", levels[r][c]);
        }
        printf("\n");
    }*/

    printf("Previous value: %ld\n", prevVal);
    return prevVal;
}

void day9(void){
    FILE* file = fopen("/Users/mikaelanicoleramos/Documents/GitHub/advent-of-code/resources/day-9.txt", "r");
    char line[256];
    
    long answer = 0;

    while (fgets(line, sizeof(line), file)) {
        line[strlen(line)-1] = '\0';
        printf("line: %s\n", line);
        
        answer += parseInputEnd(line);
        //answer += parseInputStart(line);
    }
    
    printf("sum of all endings: %ld\n", answer);
    //printf("sum of all beginnings: %ld\n", answer);
}
