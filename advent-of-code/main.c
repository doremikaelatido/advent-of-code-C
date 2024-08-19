//
//  main.c
//  advent-of-code
//
//  Created by Mikaela Nicole Ramos on 8/10/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "day-1.h"
#include "day-2.h"
#include "day-3.h"

int comp (const void * first, const void * second)
{
    int f = *((int*)first);
    int s = *((int*)second);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}

bool cardWon(int* winCards, int playedCard){
    int l = 0, r = 9;
    while (l <= r){
        int middle = l + (r - l) / 2;
        if (winCards[middle] == playedCard) return true;
        if (winCards[middle] < playedCard) l = middle + 1;
        else r = middle - 1;
    }
    return false;
}

void day4part2(void){
    FILE* file = fopen("/Users/mikaelanicoleramos/Documents/GitHub/advent-of-code/resources/day-4.txt", "r");
    char line[256];

    int answer = 0;
    int scratchcards[215];
    for (int i=0; i<215; i++){
        scratchcards[i] = 1;
    }
    int ithLine = 0;
    
    while (fgets(line, sizeof(line), file)) {
        line[strlen(line)-1] = '\0';
        
        printf("%s\n", line);
        printf("Current cards: %i\n", scratchcards[ithLine]);

        strtok(line, ":");
        char* cards = strtok(NULL, ":");
        
        char* sides;
        char* winningCards = strtok_r(cards, "|", &sides);
        int winCards[10] = {};
        
        char* winCard = strtok(winningCards, " ");
        int ithCard = 0;
        
        while (ithCard < 10 && winCard != NULL){
            winCards[ithCard++] = atoi(winCard);
            winCard = strtok(NULL, " ");
        }
        qsort(winCards, sizeof(winCards)/sizeof(*winCards), sizeof(*winCards), comp);
        
        char* playedCards = strtok_r(NULL, "|", &sides);
        char* playedCard = strtok(playedCards, " ");

        int scNext = 0;
        while (playedCard != NULL){
            if (cardWon(winCards, atoi(playedCard))){
                scNext++;
                scratchcards[ithLine + scNext] += scratchcards[ithLine];
            }
            playedCard = strtok(NULL, " ");
        }
        answer += scratchcards[ithLine];
        ithLine++;
    }
    printf("Total score: %i\n", answer);
}

void day4part1(void){
    FILE* file = fopen("/Users/mikaelanicoleramos/Documents/GitHub/advent-of-code/resources/day-4.txt", "r");
    char line[256];

    int answer = 0;
    while (fgets(line, sizeof(line), file)) {
        line[strlen(line)-1] = '\0';
        
        printf("%s\n", line);
        strtok(line, ":");
        char* cards = strtok(NULL, ":");
        
        char* sides;
        char* winningCards = strtok_r(cards, "|", &sides);
        int winCards[10] = {};
        
        char* winCard = strtok(winningCards, " ");
        int ithCard = 0;
        
        while (ithCard < 10 && winCard != NULL){
            winCards[ithCard++] = atoi(winCard);
            winCard = strtok(NULL, " ");
        }
        qsort(winCards, sizeof(winCards)/sizeof(*winCards), sizeof(*winCards), comp);
        
        char* playedCards = strtok_r(NULL, "|", &sides);
        char* playedCard = strtok(playedCards, " ");

        int sc = 0;
        while (playedCard != NULL){
            if (cardWon(winCards, atoi(playedCard))){
                printf("Number found: %s\n", playedCard);
                if (sc == 0) sc = 1;
                else sc *= 2;
            }
            playedCard = strtok(NULL, " ");
        }
        answer += sc;
    }
    printf("Total score: %i\n", answer);
}

int main(int argc, const char * argv[]) {
    day4part2();
    return 0;
}
