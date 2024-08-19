//
//  day-3.c
//  advent-of-code
//
//  Created by Mikaela Nicole Ramos on 8/18/24.
//

#include "day-3.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

void day3part2(void){
    FILE* file;
    file = fopen("/Users/mikaelanicoleramos/Documents/GitHub/advent-of-code/resources/day-3.txt", "r");
    
    char line[500];
    int lines[140][140][3];
    int lineCount[140];
    int lc = 0;
    
    while (fgets(line, sizeof(line), file)) {
        int str_len = (int)strlen(line)-1;
        line[str_len] = '\0';
        int ci = 0;
        int c = 0;
        
        while (c<str_len){
            if (line[c] == '*'){
                lines[lc][ci][0] = c-1;
                lines[lc][ci][1] = c+1;
                lines[lc][ci][2] = -1;
                c++;
                ci++;
            } else if (isdigit(line[c])){
                char number[6];
                int startIndex = c;
                while (isdigit(line[c])){
                    strncat(number, &line[c], 1);
                    c++;
                }
                lines[lc][ci][0] = startIndex;
                lines[lc][ci][1] = c-1;
                lines[lc][ci][2] = atoi(number);
                number[0] = '\0';
                ci++;
            } else {
                c++;
                continue;
            }
        }
        lineCount[lc] = ci;
        lc++;
    }
    
    int ans = 0;
    int nextPointer = 2;
    while (nextPointer < 140){
        int prevPointer = nextPointer - 2, currPointer = nextPointer - 1;
        int ciPrev = 0, ciCurr = 0, ciNext = 0;
        
        while (ciCurr < lineCount[currPointer]){
            int gearRatio = 1;
            //look for an asterisk
            while(ciCurr < lineCount[currPointer] && lines[currPointer][ciCurr][2] != -1) ciCurr++;
            if (ciCurr == lineCount[currPointer]) {
                break;
            }
            
            int adjacents = 0;
            
            //check same line - to the left and right of the asterisk found
            if (ciCurr > 0 && lines[currPointer][ciCurr-1][2] != -1 && lines[currPointer][ciCurr-1][1] == lines[currPointer][ciCurr][0]){
                gearRatio *= lines[currPointer][ciCurr-1][2];
                adjacents++;
            }
            if (ciCurr < lineCount[currPointer] && lines[currPointer][ciCurr+1][2] != -1 && lines[currPointer][ciCurr+1][0] == lines[currPointer][ciCurr][1]){
                gearRatio *= lines[currPointer][ciCurr+1][2];
                adjacents++;
            }

            //skip everything that has 0 chance of overlap with current asterisk
            while (ciPrev < lineCount[prevPointer] && lines[prevPointer][ciPrev][1] < lines[currPointer][ciCurr][0]) ciPrev++;
            //check previous line in the range of the asterisk found, and increment adjacents as needed
            while (ciPrev < lineCount[prevPointer] && lines[prevPointer][ciPrev][0] <= lines[currPointer][ciCurr][1]){
                if (lines[prevPointer][ciPrev][2] != -1){
                    gearRatio *= lines[prevPointer][ciPrev][2];
                    adjacents++;
                }
                ciPrev++;
            }
            
            //skip everything that has 0 chance of overlap with current asterisk
            while (ciNext < lineCount[nextPointer] && lines[nextPointer][ciNext][1] < lines[currPointer][ciCurr][0]) ciNext++;
            //check next line in the range of the asterisk found, and increment adjacents as needed
            while (ciNext < lineCount[nextPointer] && lines[nextPointer][ciNext][0] <= lines[currPointer][ciCurr][1]){
                if (lines[nextPointer][ciNext][2] != -1) {
                    gearRatio *= lines[nextPointer][ciNext][2];
                    adjacents++;
                }
                ciNext++;
            }
            
            //only add to final answer if adjacents = 2
            if (adjacents == 2) ans += gearRatio;
            ciCurr++;
        }
        nextPointer++;
    }
    printf("Sum of gear ratios is %i\n", ans);
}

void day3part1(void){
    FILE* file;
    file = fopen("/Users/mikaelanicoleramos/Documents/GitHub/advent-of-code/resources/day-3.txt", "r");
    
    char line[500];
    int up[140][3];
    int curr[140][3];
    int upLength = 0;
    
    int sum = 0;
    
    char *upLine = line;
    while (fgets(line, sizeof(line), file)) {
        int str_len = (int)strlen(line)-1;

        line[str_len] = '\0';
        int ci = 0;
        int upPointer = 0;
        
        int c = 0;
        printf("%s\n", upLine);
        printf("%s\n", line);
        
        while (c<str_len){
            if (line[c] == '.') {
                c++;
                continue;
            } else if (isdigit(line[c])){
                char number[6];
                int startIndex = c;
                while (isdigit(line[c])){
                    strncat(number, &line[c], 1);
                    c++;
                }
                
                curr[ci][0] = startIndex;
                curr[ci][1] = c-1;
                curr[ci][2] = atoi(number);
                
                //check for symbols adjacent in the current line
                if ((startIndex > 1 && line[startIndex-1] != '.') || (c < 140 && line[c] != '.')){
                    printf("%i + ", curr[ci][2]);
                    sum += curr[ci][2];
                    curr[ci][2] = 0;
                } else if (upLength > 0){
                    //skip where upper bound < startIndex - no chance of overlap
                    while(upPointer < upLength && up[upPointer][1] < curr[ci][0]){
                        upPointer++;
                    }
                    //check all while lower bound <= current c index
                    while (upPointer < upLength && up[upPointer][0] <= curr[ci][1]){
                        if (up[upPointer][2] == -1){
                            printf("%i + ", curr[ci][2]);
                            sum += curr[ci][2];
                            curr[ci][2] = 0;
                            break;
                        }
                        upPointer++;
                    }
                }
                number[0] = '\0';
                ci++;
            } else {
                curr[ci][0] = c-1;
                curr[ci][1] = c+1;
                curr[ci][2] = -1;
                
                if (upLength > 0){
                    //skip where upper bound < startIndex - no chance of overlap
                    while(upPointer < upLength && up[upPointer][1] < curr[ci][0]){
                        upPointer++;
                    }
                    //check all while lower bound <= current c index
                    while (upPointer < upLength && up[upPointer][0] <= curr[ci][1]){
                        if (up[upPointer][2] != -1){
                            printf("%i + ", up[upPointer][2]);
                            sum += up[upPointer][2];
                        }
                        //in the event that 2 symbols are overlapping at the ends
                        //we don't want to move the uppointer - we still want to use it for the next number
                        if (up[upPointer][0] < curr[ci][1]) upPointer++;
                        else break;
                    }
                }
                ci++;
                c++;
            }
        }
        
        //replace the values of up with the current array
        //and then reset curr to default values for next iteration
        for (int i = 0; i<140; i++){
            up[i][0] = curr[i][0];
            up[i][1] = curr[i][1];
            up[i][2] = curr[i][2];

            curr[i][0] = 0;
            curr[i][1] = 0;
            curr[i][2] = 0;
        }
        upLength = ci;
        upLine = strdup(line);
        printf("\n\n");
    }
    
    printf("Sum is %i\n", sum);
}
