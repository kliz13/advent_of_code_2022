#include <stdlib.h>
#include <stdio.h>

void replace_max_cals_per_elf(int *max_cals, int num_max_elves, int test_num);

int main() {

    FILE *fp;
    const int MAX_LINE_LENGTH = 10;
    char line[MAX_LINE_LENGTH];
    const int NUM_MAX_ELVES = 3;

    int max_calories_per_elf[NUM_MAX_ELVES]; 

    int sum_of_three_max_elves = 0;

    // init all max_calories to 0
    for(int i = 0; i < 3; i++) {
        max_calories_per_elf[i] = 0;
    }
    fp = fopen("./input_files/calories.txt", "r");
    if(fp == NULL) {
        printf("invalid file");
        exit(1);
    }

    int total_for_this_elf = 0;
    
    // We start out counting cals for a new elf (the first elf)
    int new_elf = 1;
    
    while(fgets(line, sizeof(line), fp)!= NULL) {
        if(*line == '\n') {
            replace_max_cals_per_elf(max_calories_per_elf, NUM_MAX_ELVES, total_for_this_elf);
            total_for_this_elf = 0;
            new_elf = 1;
        } else {
            new_elf = 0;
            total_for_this_elf += atoi(line);
        }
    }

    for(int i =0; i < NUM_MAX_ELVES; i++) {
        sum_of_three_max_elves += max_calories_per_elf[i];
    }

    printf("Sum of top three elves' calories: %d\n", sum_of_three_max_elves);
}

// The max_cals array is passed by reference, so we are modifying it real-time; no need
// to return anything
void replace_max_cals_per_elf(int *max_cals, int num_max_elves, int new_num_calories) {
    // Find the smallest max calories in the array; not maintaining order in this
    // array, so need to check each of the three elements
    int min_of_max_cals = *max_cals;

    // This gives us the smallest max in the array
    for(int i = 1; i < num_max_elves; i++) {
        if(*(max_cals + i) < min_of_max_cals) {
            min_of_max_cals = max_cals[i];
        }
    }

    // Is the new num_calories greater than the current min of the max vals?
    if(new_num_calories > min_of_max_cals) {
        for(int i = 0; i < num_max_elves; i++) {
            if(max_cals[i] == min_of_max_cals) {
                max_cals[i] = new_num_calories;
                break;
            }
        }
    }
}
