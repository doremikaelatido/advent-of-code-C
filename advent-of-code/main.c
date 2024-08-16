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


int main(int argc, const char * argv[]) {
    day3part1();
    return 0;
}
