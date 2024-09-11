//
//  day7.c
//  advent-of-code
//
//  Created by Mikaela Nicole Ramos on 9/9/24.
//

#include "day7.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

char order[13] = {'A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2'};
int typeCounts[7] = {0};
int indexMonitor[8] = {0};

typedef struct trieNode{
    char data;
    bool isLeaf;
    int rank;
    struct trieNode *children[13];
    int cardScore;
} TrieNode;

TrieNode* initTrie(char data){
    TrieNode *node = malloc(sizeof(TrieNode));
    for (int i=0; i<13; i++){
        node->children[i] = NULL;
    }
    node->data = data;
    node->isLeaf = false;
    return node;
}

int getRank(int *counted){
    if (counted[4] == 1) return 6;
    else if (counted[3] == 1) return 5;
    else if (counted[2] == 1){
        if (counted[1] == 1) return 4;
        else return 3;
    } else if (counted[1] == 2) return 2;
    else if (counted[1] == 1) return 1;
    else return 0;
}

void addToTrie(TrieNode *node, char* card, int score){
    TrieNode *tmp = node;
    int counts[13] = {0};
    int counted[5] = {0};
    
    for (int i=0; i<5; i++){
        for (int c=0; c<13; c++){
            if (card[i] == order[c]){
                if (counts[c] > 0) counted[counts[c]-1]--;
                counts[c]++;
                counted[counts[c]-1]++;

                if (tmp->children[c] == NULL){
                    tmp->children[c] = initTrie(card[i]);
                }
                tmp = tmp->children[c];
                break;
            }
        }
    }

    tmp->rank = getRank(counted);
    typeCounts[tmp->rank]++;
    tmp->cardScore = score;
    tmp->isLeaf = true;
}

void createIndexMonitor(void){
    int accumulating = 0;
    for (int i=0; i<7; i++){
        indexMonitor[i] = accumulating;
        accumulating += typeCounts[i];
    }
    indexMonitor[7] = accumulating;
}

long getTotalScore(TrieNode node, char* hand, int ind){
    long score=0;
    if (node.isLeaf == true){
        indexMonitor[node.rank]++;
        printf("card found: %s%c level: %i rank: %i and score: %i\n", hand, node.data, node.rank, indexMonitor[node.rank], node.cardScore);
        return node.cardScore * indexMonitor[node.rank];
    }
    for (int i=12; i>-1; i--){
        if (node.children[i] != NULL){
            hand[ind] = node.data;
            score += getTotalScore(*node.children[i], hand, ind + 1);
        }
    }
    return score;
}

void day7part1(void){
    FILE* file = fopen("/Users/mikaelanicoleramos/Documents/GitHub/advent-of-code/resources/day-7.txt", "r");
    char line[256];

    TrieNode cardTrie = *initTrie('*');
    
    while(fgets(line, sizeof(line), file)){
        char* hand = strtok(line, " ");
        int points = atoi(strtok(NULL, " "));
        
        addToTrie(&cardTrie, hand, points);
    }
    
    char hand[6];
    long ans=0;
    createIndexMonitor();
    for(int i=0; i<8; i++){
        printf("%i ", indexMonitor[i]);
    }
    printf("\n");
    for (int c=12; c>-1; c--){
        ans += getTotalScore(*cardTrie.children[c], hand, 0);
    }
    printf("total score: %ld\n", ans);
}
