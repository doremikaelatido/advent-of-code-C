# Advent of Code - DAY 5

### [Day 6 Part 1](https://adventofcode.com/2023/day/6#part1)
- How I see the problem 
    - We have a **total time**, which gives us a range of time values **1, 2,.., time** and the amount of time we charge a toy boat = speed, giving us a speed of **S** for the duration **time - S**
    - We can easily observe a pattern if we list down the possible (speed, time) values to this, let's say we have a total time value of 6:
        - (1, 5), (2, 4), (3, 3), (4, 2), (5, 1), (6, 0)
        - note that the **distance = speed \* time**, so (2, 4) will give us the same distance as (4, 2). the general trend is the distance covered will increase as we increase the speed, and decrease at some point again because of the decreasing time
    - Because the distance covered will be the same as before, we will only need to find the smallest possible speed *s* to beat the record distance, and then use the formula **total time - ( 2 \* s) + 1** to get the total count of values from s up to total time - s
- Can easily parse the values using fgets and strtok, and then store them to a totalTime and recordDistance arrays
- Get all of the number of ways to win each game and multiply for the final answer

### [Day 6 Part 2](https://adventofcode.com/2023/day/6#part2)
- Small adjustment - because we stored the individual values in the arrays, we can just make a new function joinIntArrays to get the concatenated value
    - Using the formula **log10(array[i]) + 1**, we can get the number of zeroes we need to add onto the current number to concatenate. It basically creates new zeroes so we can add the next values and keep the previously concatenated ones in the lefthand
- Do the same thing as above but pass on the concatenated time and record distance values to get the number of ways to beat the record
