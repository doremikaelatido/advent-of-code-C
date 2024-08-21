//
//  day5.c
//  advent-of-code
//
//  Created by Mikaela Nicole Ramos on 8/21/24.
//

#include "day5.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct mapping{
    long destinationRange;
    long sourceRange;
    long range;
} Mapping;

char *mappingLabels[] = {"seed-to-soil map:", "soil-to-fertilizer map:", "fertilizer-to-water map:", "water-to-light map:", "light-to-temperature map:", "temperature-to-humidity map:", "humidity-to-location map:"};
int nthMapping = 0;

int compLongs (const void * first, const void * second)
{
    long f = *((long*)first);
    long s = *((long*)second);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}

int getSeeds(char* seedsArr, long **seeds){
    *seeds = malloc(20 * sizeof(int));
    
    strtok(seedsArr, ":");
    char* rawSeeds = strtok(NULL, ":");
    char* rawSeed = strtok(rawSeeds, " ");
    
    
    int i = 0;
    while (rawSeed != NULL){
        (*seeds)[i++] = strtol(rawSeed, NULL, 10);
        rawSeed = strtok(NULL, " ");
    }
    return i;
}

int compMappings (const void *first, const void *second)
{
    long f = (*(Mapping*)first).sourceRange;
    long s = (*(Mapping*)second).sourceRange;
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}

void printWithCommas(long n) {
    if (n < 1000) {
        printf ("%ld", n);
        return;
    }
    printWithCommas(n/1000);
    printf (",%03ld", n%1000);
}


void processMapping(FILE* file, long** previousValues, int valuesLength){
    char line[256];
    
    Mapping mappings[50];
    int mappingsLength = 0, ithMapping = 0;
    
    printf("\nProcessing mappings batch\n\n");
    while (fgets(line, sizeof(line), file) && strcmp(line, "\n") != 0){
        mappings[ithMapping].destinationRange = strtol(strtok(line, " "), NULL, 10);
        mappings[ithMapping].sourceRange = strtol(strtok(NULL, " "), NULL, 10);
        mappings[ithMapping].range = strtol(strtok(NULL, " "), NULL, 10);
        ithMapping++;
        mappingsLength++;
    }
    
    qsort(mappings, mappingsLength, sizeof(Mapping), compMappings);
    ithMapping = 0;
    
    long newValues[20];
    for (int u=0; u<valuesLength; u++){
        bool found = false;
        //skip all where no chance of overlap
        while (ithMapping < mappingsLength && (mappings[ithMapping].sourceRange + mappings[ithMapping].range - 1) < (*previousValues)[u]){
            ithMapping++;
        }
        
        if (ithMapping < mappingsLength && mappings[ithMapping].sourceRange <= (*previousValues)[u]){
            printWithCommas((*previousValues)[u]);
            printf(" => WITH RANGE ");
            printWithCommas(mappings[ithMapping].sourceRange);
            printf("-");
            printWithCommas(mappings[ithMapping].sourceRange + mappings[ithMapping].range - 1);
            printf("\n");
            
            found = true;
            newValues[u] = mappings[ithMapping].destinationRange + ((*previousValues)[u] - mappings[ithMapping].sourceRange);
            
            printf("FORMULA: ");
            printWithCommas(mappings[ithMapping].destinationRange);
            printf(" + (");
            printWithCommas((*previousValues)[u]);
            printf(" - ");
            printWithCommas(mappings[ithMapping].sourceRange);
            printf(") = ");
        }
        
        if(found == false){
            printf("NO RANGE MATCH: KEEPING ");
            newValues[u] = (*previousValues)[u];
        }
        
        printWithCommas(newValues[u]);
        printf("\n\n");
    }
    
    *previousValues = newValues;
}

void day5part1(void){
    FILE* file = fopen("/Users/mikaelanicoleramos/Documents/GitHub/advent-of-code/resources/day-5.txt", "r");
    char line[256];
    
    fgets(line, sizeof(line), file);
    long* previousMappings;
    
    int length = 20;
    
    getSeeds(line, &previousMappings);

    while (fgets(line, sizeof(line), file)) {
        line[strlen(line)-1] = '\0';
        
        qsort(previousMappings, (sizeof(long)*length)/sizeof(*previousMappings), sizeof(*previousMappings), compLongs);

        if (strcmp(line, mappingLabels[nthMapping]) == 0){
            processMapping(file, &previousMappings, length);
            nthMapping++;
        }
    }
    
    long lowestLocation = previousMappings[0];
    for(int i=1; i<length; i++){
        if (previousMappings[i] < lowestLocation) lowestLocation = previousMappings[i];
    }
    
    printf("Lowest location value = %ld\n", lowestLocation);
}
