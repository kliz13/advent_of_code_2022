#include <stdlib.h>
#include <stdio.h>

int get_score(char other_player_move, char your_move); 

int main() {

    FILE *fp;

    // Set the line length to read from the file
    const int MAX_LINE_LENGTH = 5;

    // The var to read in lines from the file
    char line[MAX_LINE_LENGTH];

    // This will be the final score
    int your_overall_score = 0;

    // Open file and ensure it's valid
    fp = fopen("./input_files/suggested_moves.txt", "r");
    if(fp == NULL) {
        printf("invalid file");
        exit(1);
    }

    // While we aren't at the end of the file, continue to read lines
    // TODO: Don't assume input is formatted well
    while(fgets(line, sizeof(line), fp)!= NULL) {
        char other_player_move = '\0';
        char result = '\0';

        sscanf(line, "%c %c\n", &other_player_move, &result);

        // Normalize everything 
        your_overall_score += get_score(other_player_move, result);
    }
 
    printf("Overall Score: %d\n", your_overall_score);
}

int get_score(char other_player_move, char result)
{
    // the number of points for your win/lose status
    const int WIN_POINTS = 6;
    const int TIE_POINTS = 3;
    const int LOSE_POINTS = 0;

    // the number of points for each shape (Rock, Paper, Scissors)
    const int SHAPE_POINTS[] = {1, 2, 3};

    // The set of pairs that result in you winning and losing, with the
    // other player's move as the first element in each pair
    const int YOU_WIN[3][2] = {{'B','A'},{'C','B'}, {'A','C'}};
    const int YOU_LOSE[3][2] = {{'C','A'},{'A','B'},{'B','C'}};

    int your_score = 0;

    // your move as an array index into the shape array (R/P/S)
    int your_move = 0;

    // the other player's move, as an array index into the win/lose arrays
    int other_player_move_index = other_player_move - 'A';

    if(result == 'Y') {
        // You tie; you have the same score
        your_move = other_player_move;
        your_score = TIE_POINTS;
    } else if(result == 'Z') {
        // You win
        your_move = *YOU_WIN[other_player_move - 'A']; // R/P/S
        your_score = WIN_POINTS;
    } else {
        // you lose
        your_move = *YOU_LOSE[other_player_move - 'A']; // R/P/S
        your_score = LOSE_POINTS;
    }

    // Your score equals your win/lose/tie + the points for your shape
    your_score += SHAPE_POINTS[your_move - 'A'];
    return your_score;
}
