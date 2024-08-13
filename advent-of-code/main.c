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

void day2part2(void){
    FILE* file = fopen("/Users/mikaelanicoleramos/Documents/GitHub/advent-of-code/resources/day-2.txt", "r");
    
    int sum = 0;
    char line[256];

    while (fgets(line, sizeof(line), file)) {
        //remove the white line at the end for easy parsing
        line[strlen(line)-1] = '\0';
        
        printf("%s\n", line);
        char* gamePtr;
        char* game = strtok_r(line, ":", &gamePtr);
        char* gameIdC = strtok(game, " ");
        gameIdC = strtok(NULL, " ");
        int gameIdI = atoi(gameIdC);
        
        game = strtok_r(NULL, ":", &gamePtr);
        char* turnPtr;
        char* turn = strtok_r(game, ";", &turnPtr);
        
        int maxRed = 0, maxGreen = 0, maxBlue = 0;
        while (turn) {
            char* colorTurnPtr;
            char* colorTurn = strtok_r(turn, ",", &colorTurnPtr);
            
            int red = 0, green = 0, blue = 0;
            while (colorTurn){
                int colorNum = atoi(strtok(colorTurn, " "));
                char* color = strtok(NULL, " ");
                
                if (strcmp(color, "red") == 0){
                    red += colorNum;
                    if (red > maxRed) maxRed = red;
                } else if (strcmp(color, "green") == 0){
                    green += colorNum;
                    if (green > maxGreen) maxGreen = green;
                } else {
                    blue += colorNum;
                    if (blue > maxBlue) maxBlue = blue;
                }
                
                colorTurn = strtok_r(NULL, ",", &colorTurnPtr);
            }

            turn = strtok_r(NULL, ";", &turnPtr);
        }
        
        printf("Minimum red: %i Minimum green: %i Minimum blue: %i\n", maxRed, maxGreen, maxBlue);
        sum += (maxRed * maxGreen * maxBlue);
        printf("VALID Game ID: %i - Current sum is: %i\n", gameIdI, sum);
    }
    
    printf("Total sum: %i\n", sum);
}

void day2part1(void){
    FILE* file = fopen("/Users/mikaelanicoleramos/Documents/GitHub/advent-of-code/resources/day-2.txt", "r");
    
    int sum = 0;
    char line[256];

    while (fgets(line, sizeof(line), file)) {
        //remove the white line at the end for easy parsing
        line[strlen(line)-1] = '\0';
        
        printf("%s\n", line);
        char* gamePtr;
        char* game = strtok_r(line, ":", &gamePtr);
        char* gameIdC = strtok(game, " ");
        gameIdC = strtok(NULL, " ");
        int gameIdI = atoi(gameIdC);
        
        game = strtok_r(NULL, ":", &gamePtr);
        char* turnPtr;
        char* turn = strtok_r(game, ";", &turnPtr);
        
        bool isValid = true;
        while (turn && isValid) {
            char* colorTurnPtr;
            char* colorTurn = strtok_r(turn, ",", &colorTurnPtr);
            
            int red = 0, green = 0, blue = 0;
            while (colorTurn){
                int colorNum = atoi(strtok(colorTurn, " "));
                char* color = strtok(NULL, " ");
                
                if (strcmp(color, "red") == 0){
                    red += colorNum;
                } else if (strcmp(color, "green") == 0){
                    green += colorNum;
                } else {
                    blue += colorNum;
                }
                
                colorTurn = strtok_r(NULL, ",", &colorTurnPtr);
            }
            isValid &= red <= 12 && green <= 13 && blue <= 14;
            turn = strtok_r(NULL, ";", &turnPtr);
        }
        
        if (isValid){
            sum += gameIdI;
            printf("VALID Game ID: %i - Current sum is: %i\n", gameIdI, sum);
        }
        printf("\n");
    }
    
    printf("Total sum: %i\n", sum);
}

int main(int argc, const char * argv[]) {
    day2part2();
    return 0;
}
