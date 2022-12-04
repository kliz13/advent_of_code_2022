#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char get_badge(char items[][100]);
int get_priority_for_char(char c);


int main() {

    FILE *fp;

    // Set the line length to read from the file
    // TODO: Don't want to make statically allocate too much memory,
    // but this does limit the number of items in each rucksack to 100
    const int MAX_LINE_LENGTH = 100;

    const int NUM_ELVES_IN_GROUP = 3;

    // The var to read in lines from the file
    char line[NUM_ELVES_IN_GROUP][MAX_LINE_LENGTH];

    // The sum of the priorities
    int incorrect_item_priority_sum = 0;

    // Open file and ensure it's valid
    fp = fopen("./input_files/rucksack_contents.txt", "r");
    if(fp == NULL) {
        printf("invalid file");
        exit(1);
    }

    int num_elves_in_group_so_far = 0;
    int badge_priorities_sum = 0;

    // While we aren't at the end of the file, continue to read lines
    // TODO: Don't assume input is formatted well
    while(fgets(line[num_elves_in_group_so_far], sizeof(line[num_elves_in_group_so_far]), fp)!= NULL) {
        char badge = '\0';

        // Replace newline with terminating string char
        char *EOL_index = strchr(line[num_elves_in_group_so_far++], '\n');
        *EOL_index = '\0'; 

        if(num_elves_in_group_so_far == 3) {
            badge = get_badge(line);

            badge_priorities_sum += get_priority_for_char(badge);
            num_elves_in_group_so_far = 0;
        }
    }

    printf("Sum of badge priorities: %d\n", badge_priorities_sum);
    return badge_priorities_sum;
}

// TODO: Not currently factoring in cases of no dups, or more than one dup
char get_badge(char items[][100]) {
    char duplicates_between_first_two_elves[100];
    //memset(duplicates_between_first_two_elves, 100);
    int count = 0;

    // What is the duplicate (incorrect) item?  Init to invalid val
    char duplicate = '\0';

    for(int i = 0; i < strlen(items[0]); i++) {
        for(int j = 0; j < strlen(items[1]); j++) {
            if(items[0][i] == items[1][j]) {
                duplicates_between_first_two_elves[count++] =  items[0][i];
            } 
        }
    }
    duplicates_between_first_two_elves[count] = '\0';

    for(int k = 0; k < count; k++) {
        for(int l = 0; l < strlen(items[2]); l++) {
            if(duplicates_between_first_two_elves[k] == items[2][l]) {
                return duplicates_between_first_two_elves[k];
            }
        }
    } 

    return '\0';
}

int get_priority_for_char(char c) {
    int priority = 0;

    if((c >= 'a') && (c <= 'z')) {
        priority = c - 'a' + 1;  // Start at 1, not 0
    } else if((c >= 'A') && (c <= 'Z')) {
        priority = c - 'A' + 27; // Start at 27, not 0
    }

    return priority;
}
