//
//  main.c
//  advent-of-code
//
//  Created by Mikaela Nicole Ramos on 8/10/24.
//

#include <stdio.h>
#include <stdlib.h>

void day1(void){
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

int main(int argc, const char * argv[]) {
    // insert code here...
    day1();
    return 0;
}
