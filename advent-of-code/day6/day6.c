//
//  day6.c
//  advent-of-code
//
//  Created by Mikaela Nicole Ramos on 9/7/24.
//

#include "day6.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//3655808 - too high
//3000000 - too low
int totalTime[4];
int recordDistance[4];

void setTotalTime(char *timeData){
    int i = 0;
    char *timeTok = strtok(timeData, " ");
    
    while (timeTok != NULL){
        totalTime[i] = atoi(timeTok);
        timeTok = strtok(NULL, " ");
        i++;
    }
}

void setRecordedDistance(char *distanceData){
    int i = 0;
    char *distanceTok = strtok(distanceData, " ");

    i = 0;
    while (distanceTok != NULL){
        recordDistance[i] = atoi(distanceTok);
        distanceTok = strtok(NULL, " ");
        i++;
    }
}

int getMinimumSpeed(int ithGame){
    int low = 0;
    int gameTotalTime = totalTime[ithGame];
    int high = gameTotalTime;
    
    printf("total time: %i record distance: %i\n", totalTime[ithGame], recordDistance[ithGame]);
    
    while (low != high){
        int mid = (low + high) / 2;
        if ((gameTotalTime - mid) * mid > recordDistance[ithGame]){
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    
    printf("lowest possible speed: %i\n", low);
    return low;
}

int getWinCount(int ithGame){
    int minSpeed = getMinimumSpeed(ithGame);
    return totalTime[ithGame] - (2 * (minSpeed)) + 1;
}

void day6part1(void){
    FILE* file = fopen("/Users/mikaelanicoleramos/Documents/GitHub/advent-of-code/resources/day-6.txt", "r");
    char line[256];

    fgets(line, sizeof(line), file);
    line[strlen(line)-1] = '\0';
    
    strtok(line, ":");
    char *timeData = strtok(NULL, ":");
    setTotalTime(timeData);
    
    fgets(line, sizeof(line), file);
    line[strlen(line)-1] = '\0';

    strtok(line, ":");
    char *distanceData = strtok(NULL, ":");
    setRecordedDistance(distanceData);
    
    int ans = 1;
    for (int i=0; i<4; i++){
        ans *= getWinCount(i);
    }
    
    printf("product of all ways to wins per game: %i\n", ans);
}
