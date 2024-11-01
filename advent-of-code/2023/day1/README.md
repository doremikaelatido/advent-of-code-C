# Advent of Code - DAY 1

### [Day 1 Part 1] (https://adventofcode.com/2023/day/1#part1)
- How I see the problem
    - Most straightforward approach is to loop through the strings of the input and track the first and last numbers using a "first" and "last" variable
    - Set the value of "first" if it is not set, and continuously set the numbers as "last" - this also handles the scenario where there is only one digit X in the input, and thus will result to the two digit number XX

### [Day 1 Part 2](https://adventofcode.com/2023/day/1#part2)
- Small adjustment - now we want to include the numbers spelled out in the input as well.
    - Initial idea is to create a string array of the numbers spelled out ["zero", "one", "two", ...] because we will most certainly need to look for these substrings in the input
    - With the idea of using substrings and getting their location(index) in the input, we can do the same thing with the string version of the digits, so we can also now do comparisons with ["0", "1", "2", "3", ...]
    - Using strstr, we can iterate through the strings that we have, get the lowest and highest indexes of all the numbers, and convert to the correct 2 digit number
    
##Alternately, we can do
- Regex and get the first and last captured strings
- Replace all spelled out numbers with their number literals and do the same thing done in Part 1
