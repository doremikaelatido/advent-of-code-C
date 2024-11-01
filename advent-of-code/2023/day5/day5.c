//
//  day5.c
//  advent-of-code
//
//  Created by Mikaela Nicole Ramos on 8/21/24.
//

#include "day5.h"

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
    *seeds = malloc(20 * sizeof(long));
    
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

long getSeedsPart2(char* seedsArr, long **seeds){
    strtok(seedsArr, ":");
    char* rawSeeds = strtok(NULL, ":");
    char* rawSeed = strtok(rawSeeds, " ");
    
    int i = 0;
    Mapping seedRanges[10];
    while (i < 10){
        long start = strtol(rawSeed, NULL, 10);
        rawSeed = strtok(NULL, " ");
        long range = strtol(rawSeed, NULL, 10);
        seedRanges[i].sourceRange = start;
        seedRanges[i].range = range;
        i++;
    }
    
    qsort(seedRanges, 10, sizeof(Mapping), compMappings);
    long ranges[10][2] = { {seedRanges[0].sourceRange, seedRanges[0].sourceRange + seedRanges[0].range - 1} };
    int rP = 0;
    
    long seedsSize = 0;
    for (int i =1; i<10; i++){
        printf("%ld - %ld\n", seedRanges[i].sourceRange, seedRanges[i].sourceRange+seedRanges[i].range);
        if (seedRanges[i].sourceRange > ranges[rP][1]){
            seedsSize += ranges[rP][1] - ranges[rP][0];
            rP++;
            ranges[rP][0] = seedRanges[i].sourceRange;
            ranges[rP][1] = seedRanges[i].sourceRange + seedRanges[i].range;
        } else{
            //only change the upper bound if it's really bigger than the last upper bound
            if (ranges[rP][1] < seedRanges[i].sourceRange + seedRanges[i].range)
                ranges[rP][1] = seedRanges[i].sourceRange + seedRanges[i].range;
        }
    }
    seedsSize += ranges[rP][1] - ranges[rP][0];
    printf("Seed size: %ld\n", seedsSize);
    *seeds = malloc(seedsSize * sizeof(long));

    long sInd = 0;
    for (int u = 0; u <= rP; u++){
        long seed = ranges[u][0];
        while (seed < ranges[u][1]){
            (*seeds)[sInd] = seed;
            seed++;
            sInd++;
        }
    }
    
    return seedsSize;
}

void processMapping(FILE* file, long** previousValues, long valuesLength){
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
    
    long newValues[valuesLength];
    for (int u=0; u<valuesLength; u++){
        bool found = false;
        //skip all where no chance of overlap
        while (ithMapping < mappingsLength && (mappings[ithMapping].sourceRange + mappings[ithMapping].range - 1) < (*previousValues)[u]){
            ithMapping++;
        }
        
        if (ithMapping < mappingsLength && mappings[ithMapping].sourceRange <= (*previousValues)[u]){
            //printWithCommas((*previousValues)[u]);
            //printf(" => WITH RANGE ");
            //printWithCommas(mappings[ithMapping].sourceRange);
            //printf("-");
            //printWithCommas(mappings[ithMapping].sourceRange + mappings[ithMapping].range - 1);
            //printf("\n");
            
            found = true;
            newValues[u] = mappings[ithMapping].destinationRange + ((*previousValues)[u] - mappings[ithMapping].sourceRange);
            
            //printf("FORMULA: ");
            //printWithCommas(mappings[ithMapping].destinationRange);
            //printf(" + (");
            //printWithCommas((*previousValues)[u]);
            //printf(" - ");
            //printWithCommas(mappings[ithMapping].sourceRange);
            //printf(") = ");
        }
        
        if(found == false){
            //printf("NO RANGE MATCH: KEEPING ");
            newValues[u] = (*previousValues)[u];
        }
        
        //printWithCommas(newValues[u]);
        //printf("\n\n");
    }
    
    *previousValues = newValues;
}

void day5part2(void){
    FILE* file = fopen("/Users/mikaelanicoleramos/Documents/GitHub/advent-of-code/resources/day-5.txt", "r");
    char line[256];
    
    fgets(line, sizeof(line), file);
    long* previousMappings;
    long seedsCount = getSeedsPart2(line, &previousMappings);

    while (fgets(line, sizeof(line), file)) {
        line[strlen(line)-1] = '\0';
        
        qsort(previousMappings, (sizeof(long)*seedsCount)/sizeof(*previousMappings), sizeof(*previousMappings), compLongs);

        if (strcmp(line, mappingLabels[nthMapping]) == 0){
            processMapping(file, &previousMappings, seedsCount);
            nthMapping++;
        }
    }
    
    long lowestLocation = previousMappings[0];
    for(int i=1; i<seedsCount; i++){
        if (previousMappings[i] < lowestLocation) lowestLocation = previousMappings[i];
    }
    
    printf("Lowest location value = %ld\n", lowestLocation);
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
