//
//  day5.h
//  advent-of-code
//
//  Created by Mikaela Nicole Ramos on 8/21/24.
//

#ifndef day5_h
#define day5_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

static char *mappingLabels[] = {"seed-to-soil map:", "soil-to-fertilizer map:", "fertilizer-to-water map:", "water-to-light map:", "light-to-temperature map:", "temperature-to-humidity map:", "humidity-to-location map:"};

typedef struct mapping{
    long destinationRange;
    long sourceRange;
    long range;
} Mapping;

void day5part1(void);
void day5part2(void);
int compLongs (const void * first, const void * second);
int compMappings(const void *first, const void *second);
void printWithCommas(long n);

#endif /* day5_h */
