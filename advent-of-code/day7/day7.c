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

void printRank(int rank){
    printf("rank obtained: %i -> ", rank);
    switch(rank){
        case 6:
            printf("five of a kind\n");
            break;
        case 5:
            printf("four of a kind\n");
            break;
        case 4:
            printf("full house\n");
            break;
        case 3:
            printf("three of a kind\n");
            break;
        case 2:
            printf("two pair\n");
            break;
        case 1:
            printf("one pair\n");
            break;
        default:
            printf("high card\n");
            break;
    }
}
int getRank1(int *counted){
    if (counted[4] == 1) return 6;
    else if (counted[3] == 1) return 5;
    else if (counted[2] == 1){
        if (counted[1] == 1) return 4;
        else return 3;
    } else if (counted[1] == 2) return 2;
    else if (counted[1] == 1) return 1;
    else return 0;
}

int getRank2(int *counted, int jokerCount, int maxCount){
    int joked = maxCount + jokerCount;
    
    //6TT6J
    if (counted[4] == 1 || joked ==  5) return 6;
    else if (counted[3] == 1 || joked == 4) return 5;
    else if (counted[2] == 1){
        if (counted[1] == 1) return 4;
        else return 3;
    } else if (joked == 3){
        if (jokerCount == 1 && counted[1] == 2) return 4;
        else return 3;
    } else if (counted[1] == 2 || (counted[1] ==  1 && jokerCount == 1 && joked == 2)) return 2;
    else if (counted[1] == 1 || joked == 2) return 1;
    else return 0;
}

void addToTrie1(TrieNode *node, char* card, int score, char* order){
    TrieNode *tmp = node;
    int counts[13] = {0};
    int counted[5] = {0};
    int jokerCount = 0;
    int maxCount = 0;
    
    printf("word: %s -> ", card);
    
    for (int i=0; i<5; i++){
        for (int c=0; c<13; c++){
            if (card[i] == order[c]){
                if (counts[c] > 0) counted[counts[c]-1]--;
                if (card[i] == 'J') jokerCount++;
                counts[c]++;
                if (counts[c] > maxCount && card[i] != 'J') maxCount = counts[c];
                counted[counts[c]-1]++;

                if (tmp->children[c] == NULL){
                    tmp->children[c] = initTrie(card[i]);
                }
                tmp = tmp->children[c];
                break;
            }
        }
    }

    tmp->rank = getRank1(counted);
    printRank(tmp->rank);
    typeCounts[tmp->rank]++;
    tmp->cardScore = score;
    tmp->isLeaf = true;
}

void addToTrie2(TrieNode *node, char* card, int score, char* order){
    TrieNode *tmp = node;
    int counts[13] = {0};
    int counted[5] = {0};
    int jokerCount = 0;
    int maxCount = 0;
    
    printf("word: %s -> ", card);
    
    for (int i=0; i<5; i++){
        for (int c=0; c<13; c++){
            if (card[i] == order[c]){
                //part 2
                if (card[i] == 'J') jokerCount++;
                else {
                    if (counts[c] > 0) counted[counts[c]-1]--;
                    counts[c]++;
                    if (counts[c] > maxCount) maxCount = counts[c];
                    counted[counts[c]-1]++;
                }

                if (tmp->children[c] == NULL){
                    tmp->children[c] = initTrie(card[i]);
                }
                tmp = tmp->children[c];
                break;
            }
        }
    }

    tmp->rank = getRank2(counted, jokerCount, maxCount);
    printRank(tmp->rank);
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

    TrieNode cardTrie1 = *initTrie('*');
    TrieNode cardTrie2 = *initTrie('*');
    
    char order1[13] = {'A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2'};
    char order2[13] = {'A', 'K', 'Q', 'T', '9', '8', '7', '6', '5', '4', '3', '2', 'J'};

    while(fgets(line, sizeof(line), file)){
        char* hand = strtok(line, " ");
        int points = atoi(strtok(NULL, " "));
        //part 1
        //addToTrie1(&cardTrie1, hand, points, order1);
        addToTrie2(&cardTrie2, hand, points, order2);
    }
    
    char hand[6];
    long ans=0;
    createIndexMonitor();
    
    for (int c=12; c>-1; c--){
        //part 1
        //ans += getTotalScore(*cardTrie1.children[c], hand, 0);
        ans += getTotalScore(*cardTrie2.children[c], hand, 0);
    }
    printf("total score: %ld\n", ans);
}
