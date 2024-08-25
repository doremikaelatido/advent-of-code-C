//
//  day-1.c
//  advent-of-code
//
//  Created by Mikaela Nicole Ramos on 8/11/24.
//

#include "day1.h"
#include <string.h>

void day1part2(void){
    char* numbers[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    char* realNumbers[9] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
    
    FILE* file;
    file = fopen("/Users/mikaelanicoleramos/Documents/GitHub/advent-of-code/resources/day-1.txt", "r");
    
    int sum = 0;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("Line: %s", line);
        int first = -1, last = -1;
        int firstIndex = (int)strlen(line), lastIndex = -1;
        
        for (int n = 0; n < 9; n++){
            char *tmp1 = line;
            char *tmp2 = line;
            
            int l = (int)strlen(numbers[n]);
            while ((tmp1 = strstr(tmp1, numbers[n]))){
                int index = (int)(line - tmp1) * -1;
                if (index < firstIndex){
                    firstIndex = index;
                    first = n+1;
                }
                if (index > lastIndex){
                    lastIndex = index;
                    last = n+1;
                }
                tmp1 = &tmp1[l];
            }
            while ((tmp2 = strstr(tmp2, realNumbers[n]))){
                int index = (int)(line - tmp2) * -1;
                if (index < firstIndex){
                    firstIndex = index;
                    first = n+1;
                }
                if (index > lastIndex){
                    lastIndex = index;
                    last = n+1;
                }
                tmp2 = &tmp2[1];
            }
        }
        
        int curr = (10 * first) + last;
        sum += curr;
        printf("Number found: %i\n", curr);
    }

    printf("The sum of all the lines is: %i\n", sum);
    fclose(file);
}

void day1part1(void){
    FILE* file;
    file = fopen("/Users/mikaelanicoleramos/Documents/GitHub/advent-of-code/resources/day-1.txt", "r");
    
    int sum = 0;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("Line: %s", line);
        char first = '\0', last = '\0';
        for (int c = 0; line[c] != '\r' && line[c] != '\n' && line[c] != '\0'; c++ ){
            if (line[c] >= '0' && line[c] <= '9'){
                if (first == '\0') first = line[c];
                last = line[c];
            }
        }
        int curr = (10 * (first - '0')) + (last - '0');
        sum += curr;
        printf("Number found: %i\n", curr);
    }

    printf("The sum of all the lines is: %i\n", sum);
    fclose(file);
}
