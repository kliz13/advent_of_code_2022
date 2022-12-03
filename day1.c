#include <stdlib.h>
#include <stdio.h>

int main() {

    FILE *fp;
    const int MAX_LINE_LENGTH = 10;
    char line[MAX_LINE_LENGTH];

    // Assuming nums in file don't contain negative ints
    int max_calories_per_elf = 0; 
    fp = fopen("./input_files/calories.txt", "r");

    if(fp == NULL) {
        printf("invalid file");
        exit(1);
    }

    int total_for_this_elf = 0;
    
    // We start out counting cals for a new elf (the first elf); using this
    // as a bool TRUE
    int new_elf = 1;
    
    while(fgets(line, sizeof(line), fp)!= NULL) {
        if(*line == '\n') {
            if(total_for_this_elf > max_calories_per_elf) {
                max_calories_per_elf = total_for_this_elf;
            }
            total_for_this_elf = 0;
            new_elf = 1;
        } else {
            new_elf = 0;
            total_for_this_elf += atoi(line);
        }
    }
    
    printf("%d\n", max_calories_per_elf);
}
