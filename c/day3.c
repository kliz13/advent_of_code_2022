#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char get_incorrect_item(char *compartment1, char *compartment2, int num_items);
int get_priority_for_char(char c);


int main() {

    FILE *fp;

    // Set the line length to read from the file
    // TODO: Don't want to make statically allocate too much memory,
    // but this does limit the number of items in each rucksack to 100
    const int MAX_LINE_LENGTH = 100;

    // The var to read in lines from the file
    char line[MAX_LINE_LENGTH];

    // The sum of the priorities
    int incorrect_item_priority_sum = 0;

    // Open file and ensure it's valid
    fp = fopen("./input_files/rucksack_contents.txt", "r");
    if(fp == NULL) {
        printf("invalid file");
        exit(1);
    }

    // While we aren't at the end of the file, continue to read lines
    // TODO: Don't assume input is formatted well
    while(fgets(line, sizeof(line), fp)!= NULL) {
        // Replace newline with terminating string char
        char *EOL_index = strchr(line, '\n');
        *EOL_index = '\0'; 

        int num_items_in_rucksack = (EOL_index - line);

        char *compartment1 = line;
        char *compartment2 = line + (num_items_in_rucksack/2);

        char incorrect_item = get_incorrect_item(compartment1, compartment2,
            num_items_in_rucksack);

        incorrect_item_priority_sum += get_priority_for_char(incorrect_item);
    }

    printf("Sum of incorrect item priorities: %d\n", incorrect_item_priority_sum);
    return incorrect_item_priority_sum;
}

// TODO: Not currently factoring in cases of no dups, or more than one dup
char get_incorrect_item(char *compartment1, char *compartment2, int num_items) {

    // What is the duplicate (incorrect) item?  Init to invalid val
    char duplicate = '\0';

    printf("NUM ITEMS %d\n", (num_items/2));
    for(int i = 0; i < (num_items/2); i++) {
        for(int j = 0; j < (num_items/2); j++) {
            if(compartment1[i] == compartment2[j]) { // we found the duplicate; save the value
                duplicate = compartment1[i];
                break;
            } 
        }
        if(duplicate != '\0') {
            // We found the duplicate; return; 
            break;
        }
    }

    // If the caller checks for invalid char, this might work for no dups
    return duplicate;
}

// Return 0 if the char doesn't match one we expect so that it doesn't
// add to the sum
int get_priority_for_char(char c) {
    int priority = 0;

    if((c >= 'a') && (c <= 'z')) {
        priority = c - 'a' + 1;  // Start at 1, not 0
    } else if((c >= 'A') && (c <= 'Z')) {
        priority = c - 'A' + 27; // Start at 27, not 0
    }

    return priority;
}
