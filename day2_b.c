#include <stdlib.h>
#include <stdio.h>

int get_score(char other_player_move, char your_move); 

int main() {

    FILE *fp;
    const int MAX_LINE_LENGTH = 5;
    char line[MAX_LINE_LENGTH];

    // Assuming nums in file don't contain negative ints
    int your_overall_score = 0; 
    fp = fopen("suggested_moves.txt", "r");

    if(fp == NULL) {
        printf("invalid file");
        exit(1);
    }

    while(fgets(line, sizeof(line), fp)!= NULL) {
		char other_player_move = '\0';
	    char result = '\0';
	    sscanf(line, "%c %c\n", &other_player_move, &result);

		// Normalize everything 
		your_overall_score += get_score(other_player_move, result);
    }
	
    printf("\nOverall Score: %d\n", your_overall_score);
}

int get_score(char other_player_move, char result) {
	const int WIN_POINTS = 6;
	const int TIE_POINTS = 3;
	const int LOSE_POINTS = 0;
	const int SHAPE_POINTS[] = {1, 2, 3};
	const int YOU_WIN[3][2] = {{'B','A'},{'C','B'}, {'A','C'}};
	const int YOU_LOSE[3][2] = {{'C','A'},{'A','B'},{'B','C'}};

	int your_score = 0;
	int your_move = 0;
	// You tie
	if(result == 'Y') {
	    your_score = TIE_POINTS + SHAPE_POINTS[other_player_move - 'A'];
		printf("tie: %d %d\n", TIE_POINTS, SHAPE_POINTS[other_player_move -'A']);
	} else if(result == 'Z') {
		your_move = *YOU_WIN[other_player_move - 'A'];
		printf("your move: %c\n", your_move);
		printf("win: %d %d\n", WIN_POINTS, SHAPE_POINTS[(your_move - 'A')]);
	    your_score = WIN_POINTS + SHAPE_POINTS[your_move - 'A'];
	} else {
		your_move = *YOU_LOSE[other_player_move - 'A'];
		printf("your move: %c\n", your_move);
		printf("lose: %d\n", SHAPE_POINTS[your_move - 'A']);
		your_score = LOSE_POINTS + SHAPE_POINTS[your_move - 'A'];	
    }
	printf("%d\n", your_score);
    return your_score;	
}
