/* Created by kieran Devany 
 * Game of life
 * 5/10/2020
 */

/* includes */
#define EXTERN
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>

#include "lifeDef.h"

#define BUFFLEN 1024

/* Prototypes */
int display(int **boardp);
int update(int **boardp);
int survive(int nb[3][3], int id);
void printHood(int nb[3][3]);

int main(){
	WIDTH = 5;
	LENGTH = 5;
	int status = 0;
	FILE *fp;
	char buffer [BUFFLEN];


	/* get file */
	fp = fopen("smallMap.txt", "r");
	if(fp == NULL){
		fprintf(stderr, "cannot read from file\n");
		return -1;	
	}
	/* malloc board */
	//TODO
	int **arrPointer = malloc(LENGTH * sizeof(arrPointer));
	for(int i = 0; i<LENGTH;i++){
		arrPointer[i]= malloc(WIDTH*sizeof(*arrPointer[i]));
	}

	/* intialize State */
	//TODO
	int hIndex = 0;
	while(hIndex < LENGTH){
		if( fgets(buffer, BUFFLEN, fp) != buffer)
		break;
		
		int index = 0;
		

		while((buffer[index] != '\0') || (index < WIDTH)){
			if((buffer[index] != '1')||(buffer[index] == '0')){
				arrPointer[hIndex][index] = 0;
			}
			else{
				arrPointer[hIndex][index] = 1;
			}
			index++;
		}
		if (index < WIDTH){
			while(index < WIDTH){
				arrPointer[hIndex][index] = 0;
				index++;
			}
		}
		hIndex++;
	}
	
	/* begin run */
	int count= 0;
	while(status != -1){
		printf("Year %d\n", count);
		status = display(arrPointer);
		status = update(arrPointer);
		count++;
	}

	/* always gotta free */
	for(int i = 0; i<LENGTH; i++){
		free(arrPointer[i]);
	}
	free(arrPointer);
	return 0;

}
/* Pints out board in a color coordinated fashion */
int display(int **board){
	int l = LENGTH;
	int w = WIDTH;	
	
	/* quick and easy print */
	for(int iterL = 0; iterL < l; iterL++){
		for (int iterW = 0; iterW < w; iterW++){
			if(board[iterL][iterW] == 2){
				board[iterL][iterW] = 1; // new children become adults, helps simul death+life
			}
			if(board[iterL][iterW] == 3){
				board[iterL][iterW] = 5;
			}
			printf("%d",board[iterL][iterW]);
		}
		printf("\n");
	}
	printf("\n");
	return 0;	
}
/* runs through and updates each cell */
int update(int **board){
	int l = LENGTH;
	int w = WIDTH;	
	int nb[3][3];

	/* quick and easy print */
	for(int iterL = 0; iterL < l; iterL++){
		for (int iterW = 0; iterW < w; iterW++){
			int nBool[4] = {1,1,1,1};
			int id = (l*iterL) + iterW+1; 
			if(iterL == 0){
				nBool[0] = 0; 	// No top row
			}
			if(iterL == (w -1)){
				nBool[1] = 0; // No bottom row
			}
			if( iterW == 0){
				nBool[2] = 0; // no left column
			}
			if(iterW == (l - 1)){
				nBool[3] = 0; // no right column
			}
			
			//TODO create neighborhood array
			
			if(nBool[0]){					// top row
				nb[0][1] = board[iterL-1][iterW];
				if(nBool[2]){
					nb[0][0] = board[iterL-1][iterW-1];
					nb[1][0] = board[iterL][iterW-1];
				}
				else{
					nb[0][0] = '#';
					nb[2][0] = '#';
					nb[1][0] = '#';
				}
				if( nBool[3]){
					nb[0][2] = board[iterL-1][iterW+1];
					nb[1][2] = board[iterL][iterW+1];
				}
				else{
					nb[0][2] = '#';
					nb[1][2] = '#';
					nb[2][2] = '#';
				}
			}
			if(nBool[1]){					// bottom row
				nb[2][1] = board[iterL+1][iterW];
				if(nBool[2]){
					nb[2][0] = board[iterL+1][iterW-1];
					nb[1][0] = board[iterL][iterW-1];
				}
				else{
					nb[0][0] = '#';
					nb[2][0] = '#';
					nb[1][0] = '#';
				}
				if( nBool[3]){
					nb[2][2] = board[iterL+1][iterW+1];
					nb[1][2] = board[iterL][iterW+1];
				}
				else{
					nb[2][2] = '#';
					nb[1][2] = '#';
					nb[0][2] = '#';
				}
			}						// middle
			nb[1][1] = '#'; 

			int status = survive(nb, id);
			int prev = board[iterL][iterW];
			if(status == 1){
				if (prev != 1){
					board[iterL][iterW] = 2;	//child, will become adult next round
				}				
				else{
					board[iterL][iterW] = 1;	//still alive, age here
				}
			}
			else if(status == 0){
				if( prev == 1){
					board[iterL][iterW] = 3;	// Death age here
				}
				else if((prev > 4) && (prev < 8)){
					board[iterL][iterW] = prev+1;	//death aging
				}
				else{
					board[iterL][iterW] = 0; 	//dead for 2 ticks 
				}
			}
		}
	}
	return 0;
}
/* Survive, returns 1 if the cell lives and 0 if it dies, -1 if no change */
int survive(int nb[3][3], int id){
	int alive = 0;
	id = id;

	for (int iterL = 0; iterL < 3; iterL++){
		for (int iterW = 0; iterW < 3; iterW++){
			if((nb[iterL][iterW] == 1)||(nb[iterL][iterW] == 3)){
				alive++;
			}
		}	
	}
	if (alive < 2){
		return 0;
	}
	else if( alive > 3){
		return 0;
	}
	else if(alive == 3){
		return 1;
	}
	return -1;
}

void printHood(int nb[3][3]){
	int x = 0;
	int y = 0;

	while(x < 3){
		while(y < 3){
			printf("%d",nb[x][y]);
			y++;
		}
		x++;
		y = 0;
	}
}
