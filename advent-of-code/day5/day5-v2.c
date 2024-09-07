//
//  day5-v2.c
//  advent-of-code
//
//  Created by Mikaela Nicole Ramos on 9/1/24.
//

#include "day5-v2.h"

void printRange(Mapping mapping){
    printf("source mapping: ");
    printWithCommas(mapping.sourceRange);
    printf("-");
    printWithCommas(mapping.sourceRange + mapping.range);
    printf("\n");
}

void printDestinationRange(Mapping mapping){
    printf("destination mapping: ");
    printWithCommas(mapping.destinationRange);
    printf("-");
    printWithCommas(mapping.destinationRange + mapping.range);
    printf("\n");
}

long min(const long l1, const long l2){
    if (l1 < l2) return l1;
    return l2;
}

int getSeedsv2(char* seedsArr, Mapping **seeds){
    *seeds = malloc(10 * sizeof(Mapping));
    
    strtok(seedsArr, ":");
    char* rawSeeds = strtok(NULL, ":");
    char* rawSeed = strtok(rawSeeds, " ");
    
    int i = 0;
    while (i < 10){
        long start = strtol(rawSeed, NULL, 10);
        rawSeed = strtok(NULL, " ");
        long range = strtol(rawSeed, NULL, 10);
        (*seeds)[i].sourceRange = start;
        (*seeds)[i].range = range;
        i++;
        rawSeed = strtok(NULL, " ");
    }
     
    qsort(*seeds, 10, sizeof(Mapping), compMappings);
    
    Mapping *mergedSeeds = malloc(10 * sizeof(Mapping));
    mergedSeeds[0] = (*seeds)[0];
    
    int mSInd = 0;
    /*printf("SEEDS\n");
    for (int n=0; n<10; n++){
        printWithCommas((*seeds)[n].sourceRange);
        printf("-");
        printWithCommas((*seeds)[n].sourceRange + (*seeds)[n].range);
        printf("\n");
    }*/
    
    for (int m=1; m<10; m++){
        if (mergedSeeds[mSInd].sourceRange >= (*seeds)[m].sourceRange && (*seeds)[m].sourceRange + (*seeds)[m].range < mergedSeeds[mSInd].range){
            //do nothing, in range
            continue;
        } else if (mergedSeeds[mSInd].sourceRange + mergedSeeds[mSInd].range > (*seeds)[m].sourceRange){
            mergedSeeds[mSInd].range = (*seeds)[m].sourceRange + (*seeds)[m].range - mergedSeeds[mSInd].sourceRange;
        } else {
            mSInd++;
            mergedSeeds[mSInd].sourceRange = (*seeds)[m].sourceRange;
            mergedSeeds[mSInd].range = (*seeds)[m].range;
        }
    }
    *seeds = mergedSeeds;
    
    /*printf("NEW SEEDS\n");
    for (int n=0; n<mSInd+1; n++){
        printRange((*seeds)[n]);
    }*/
    
    return mSInd + 1;
}

int processMappingv2(FILE* file, Mapping** previousValues, long valuesLength){
    char line[256];
    
    Mapping mappings[50];
    int mappingsLength = 0, ithMapping = 0;
    
    printf("\nProcessing mappings batch\n\n");
    while (fgets(line, sizeof(line), file) && strcmp(line, "\n") != 0){
        mappings[ithMapping].destinationRange = strtol(strtok(line, " "), NULL, 10);
        mappings[ithMapping].sourceRange = strtol(strtok(NULL, " "), NULL, 10);
        mappings[ithMapping].range = strtol(strtok(NULL, " "), NULL, 10);
        mappingsLength++;
        //printf("%ld %ld %ld\n", mappings[ithMapping].destinationRange, mappings[ithMapping].sourceRange, mappings[ithMapping].range);
        ithMapping++;
    }
    qsort(mappings, mappingsLength, sizeof(Mapping), compMappings);

    int nValToMap = 0;
    int nNewVal = 0;
    Mapping *newValues = calloc(100, sizeof(Mapping));
    
    printf("mappings found: \n");
    for (int n=0; n<mappingsLength; n++){
        printRange(mappings[n]);
        printDestinationRange(mappings[n]);
    }
    printf("\n");
    
    printf("processing the ranges: \n\n");
    for (int n=0; n < valuesLength; n++){
        //means there are values that are not mapped
        long remainSrcRange = (*previousValues)[n].sourceRange;
        long entireRange = (*previousValues)[n].sourceRange + (*previousValues)[n].range;

        if (nValToMap < mappingsLength){
            while (nValToMap < mappingsLength && remainSrcRange < entireRange){
                long upperBoundRange = mappings[nValToMap].sourceRange + mappings[nValToMap].range;

                //some range of values that cannot be mapped
                if(remainSrcRange < mappings[nValToMap].sourceRange){
                    //printf("keep the values\n");
                    //retain values
                    newValues[nNewVal].sourceRange = remainSrcRange;
                    //but we want to make sure to only map to the same value if it's not part of a range
                    newValues[nNewVal].range = min(mappings[nValToMap].sourceRange - remainSrcRange, (*previousValues)[n].range);
                }
                //check next mapping
                else if (remainSrcRange >= upperBoundRange){
                    //printf("use the next mapping\n");
                    nValToMap++;
                    continue;
                }
                //use up the entire range
                else if (remainSrcRange == mappings[nValToMap].sourceRange){
                    //printf("use the entire current mapping\n");
                    newValues[nNewVal].range = min(upperBoundRange - remainSrcRange, entireRange - remainSrcRange);
                    newValues[nNewVal].sourceRange = mappings[nValToMap].destinationRange;
                }
                //in that specific range
                else {
                    printf("use partial mapping\n");
                    newValues[nNewVal].range = min(upperBoundRange - remainSrcRange, entireRange - remainSrcRange);
                    newValues[nNewVal].sourceRange = mappings[nValToMap].destinationRange + remainSrcRange - mappings[nValToMap].sourceRange;
                }
                
                printf("current range: ");
                printWithCommas(remainSrcRange);
                printf("-");
                printWithCommas(remainSrcRange + newValues[nNewVal].range);
                printf("\n");
                
                printRange(mappings[nValToMap]);
                printDestinationRange(mappings[nValToMap]);

                printf("new range: ");
                printRange(newValues[nNewVal]);
                printf("\n");
                
                remainSrcRange += newValues[nNewVal].range;
                nNewVal++;
            }
        } else {
            printf("no more mappings available for this range\n");
            newValues[nNewVal].range = entireRange - remainSrcRange;
            newValues[nNewVal].sourceRange = remainSrcRange;
        }
    }
    
    printf("\n");
    *previousValues = newValues;
    return nNewVal;
}

void day5part2v2(void){
    FILE* file = fopen("/Users/mikaelanicoleramos/Documents/GitHub/advent-of-code/resources/day-5.txt", "r");
    char line[256];
    
    int nthMapping = 0;
    
    fgets(line, sizeof(line), file);
    Mapping* previousMappings;
    int mapCount = getSeedsv2(line, &previousMappings);

    while (fgets(line, sizeof(line), file)) {
        line[strlen(line)-1] = '\0';
        qsort(previousMappings, mapCount, sizeof(Mapping), compMappings);
        
        if (strcmp(line, mappingLabels[nthMapping]) == 0){
            printf("=================Sorted previous mappings\n");
            for (int o=0; o<mapCount; o++){
                printRange(previousMappings[o]);
            }
            
            mapCount = processMappingv2(file, &previousMappings, mapCount);
            nthMapping++;
        }
    }
    
    qsort(previousMappings, mapCount, sizeof(Mapping), compMappings);
    printf("\n LAST MAPPINGS\n");
    for (int u=0; u<mapCount; u++){
        printRange(previousMappings[u]);
    }
    printf("lowest value: \n");
    printWithCommas(previousMappings[0].sourceRange);
    printf("\n");
}
