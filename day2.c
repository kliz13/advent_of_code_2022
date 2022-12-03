#include <stdlib.h>
#include <stdio.h>

int get_score(char other_player_move, char your_move); 

int main() {

    FILE *fp;

    // Use this constant to normalize between A,B,C and X,Y,Z chars
    const int NORMALIZE_TO_XYZ = 'X' - 'A'; // 23

    // Set the line length to read from the file
    const int MAX_LINE_LENGTH = 5;

    // The var to read in lines from the file
    char line[MAX_LINE_LENGTH];

    // This will be the final score
    int your_overall_score = 0;

    // Open file and ensure it's valid
    fp = fopen("suggested_moves.txt", "r");
    if(fp == NULL) {
        printf("invalid file");
        exit(1);
    }

    // While we aren't at the end of the file, continue to read lines
    // TODO: Don't assume input is formatted well
    while(fgets(line, sizeof(line), fp)!= NULL) {
        char other_player_move = '\0';
        char your_move = '\0';

        sscanf(line, "%c %c\n", &other_player_move, &your_move);

        your_overall_score += get_score((other_player_move + NORMALIZE_TO_XYZ),
            your_move);
    }

    printf("Overall Score: %d\n", your_overall_score);
}

int get_score(char other_player_move, char your_move) {
    // the number of points for your win/lose status
    const int WIN_POINTS = 6;
    const int TIE_POINTS = 3;
    const int LOSE_POINTS = 0;

    // the number of points for each shape (Rock, Paper, Scissors)
    const int SHAPE_POINTS[] = {1, 2, 3};

    // The set of pairs that result in you winning, with your move as the first element in each pair
    const int YOU_WIN[3][2] = {{'Z','X'},{'X','Y'},{'Y','Z'}};

    int your_score = 0;

    // Change char into array index for the Shape array
    int your_move_arr_index = your_move - 'X';

    // Game is a tie
    if(your_move == other_player_move) {
        your_score = TIE_POINTS;
    } else if(YOU_WIN[your_move_arr_index][0] == other_player_move) {
        // You win
        your_score = WIN_POINTS;
    } else {
        // You lose
        your_score = LOSE_POINTS;
    }

    // Your total score equals the win/lose/tie + number of points for R/P/S
    your_score += SHAPE_POINTS[your_move_arr_index];
    return your_score;
}
