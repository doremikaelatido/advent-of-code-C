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
#include <math.h>

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

long getMinimumSpeed(long time, long distance){
    long low = 0;
    long high = time;
    printf("total time: %ld record distance: %ld\n", time, distance);
    
    while (low != high){
        long mid = (low + high) / 2;
        if ((time - mid) * mid > distance){
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    
    printf("lowest possible speed: %ld\n", low);
    return low;
}

long getWinCount(long time, long distance){
    long minSpeed = getMinimumSpeed(time, distance);
    return time - (2 * (minSpeed)) + 1;
}

long joinIntArray(int* array){
    long outLong = array[0];
    for (int i=1; i<4; i++){
        long zerosToAdd = log10(array[i])+ 1;
        long multiplyWithCurrent = pow(10, zerosToAdd);
        outLong *= multiplyWithCurrent;
        outLong += array[i];
    }
    
    return outLong;
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
    
    //day 6 part 1
    long ans1 = 1;
    for (int i=0; i<4; i++)
        ans1 *= getWinCount(totalTime[i], recordDistance[i]);
    printf("DAY 1 product of all ways to wins per game: %ld\n", ans1);
    printf("\n");
    
    //day 6 part 2
    long totalTimeLong = joinIntArray(totalTime);
    long recordDistanceLong = joinIntArray(recordDistance);
    long ans2 = getWinCount(totalTimeLong, recordDistanceLong);
    printf("DAY 2 product of all ways to wins per game: %ld\n", ans2);
}
