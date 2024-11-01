# Advent of Code - DAY 5

### [Day 5 Part 1](https://adventofcode.com/2023/day/5#part1)
- How I see the problem 
    - we have N initial seeds, so we will end up with N values after going through every single mapping (I will use the word "value" because it changes every round: it becomes seed -> soil -> fertilizer -> water -> light -> temperature -> humidity -> location)
    - for every batch of map, we do the following:
        - we go through each range and check sourceRange <= value <= (sourceRange + range - 1) to determine the mapping to use
        - if the value is within a range, then compute for the mapped value with the formula destinationRange + (value - sourceRange)
        - if we didn't find an appropriate mapping, then we keep the value
- Since we'll be doing a lot of comparisons between the current values and mappings, my first thought was to make use of sorting for efficient comparison. It is also important to note that the next batch of values is driven by the destination range (which is completely unrelated to the position of the source range) so it is a must to sort the values after every round of mapping processing
- I was able to conveniently parse the seed data from the 1st line of the file using strtok with ":" delimiter, followed by another strtok with " " delimeter to get the individual seed values
- There is noticeable pattern in the input file, where mapping label (such as "seed-to-soil map:", "soil-to-fertilizer map:", etc) is succeeded a by a series of values <destinationRange> <sourceRange> <range>, so what I did here is I wrote a function that accepts the file pointer and processes all of the lines until we find a blank line - signifying the end. We call the function only if we come across a mapping label while reading the file. This function should also update the values with the current mapping.
