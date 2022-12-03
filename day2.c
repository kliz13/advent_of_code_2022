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
	    char your_move = '\0';
	    sscanf(line, "%c %c\n", &other_player_move, &your_move);

		// Normalize everything 
		your_overall_score += get_score(other_player_move+23, your_move);
    }
	
    printf("\nOverall Score: %d\n", your_overall_score);
}

int get_score(char other_player_move, char your_move) {
	const int WIN_POINTS = 6;
	const int TIE_POINTS = 3;
	const int LOSE_POINTS = 0;
	const int SHAPE_POINTS[] = {1, 2, 3};
	const int YOU_LOSE[3][2] = {{'Y','X'},{'Z','Y'}, {'X','Z'}};
	const int YOU_WIN[3][2] = {{'Z','X'},{'X','Y'},{'Y','Z'}};
	
	int your_score = 0;
	if(your_move == other_player_move) {
	    your_score = TIE_POINTS + SHAPE_POINTS[(your_move - 'X')];
		printf("tie: %d %d\n", TIE_POINTS, SHAPE_POINTS[your_move -'X']);
	} else if(*YOU_WIN[your_move - 'X'] == other_player_move) {
		printf("win: %d %d\n", WIN_POINTS, SHAPE_POINTS[(your_move - 'X')]);
	    your_score = WIN_POINTS + SHAPE_POINTS[(your_move - 'X')];
		printf("YOUR SCORE: %d\n", your_score);
	} else {
		printf("lose: %d\n", SHAPE_POINTS[your_move - 'X']);
		your_score = LOSE_POINTS + SHAPE_POINTS[(your_move - 'X')];	
    }
	printf("%d\n", your_score);
    return your_score;	
}
