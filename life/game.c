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
int display(int board[LENGTH][WIDTH]);
int update(int board[LENGTH][WIDTH]);
int survive(int nb[3][3]);


int main(){
	WIDTH = 20;
	LENGTH = 20;
	int board[LENGTH][WIDTH];
	int status = 0;
	FILE *fp;
	char buffer [BUFFLEN];


	/* get file */
	fp = fopen("map.txt", "r");
	if(fp == NULL){
		fprintf(stderr, "cannot read from file\n");
		return -1;	
	}

	/* intialize State */
	//TODO
	int maxlen = 0;
	int hIndex = 0;

	while(hIndex < LENGTH){
		if( fgets(buffer, BUFFLEN, fp) != buffer)
		break;
		
		int index = 0;
		int linelen = 0;

		while((buffer[index] != '\0') || (linelen < maxlen)){
			linelen++;
			if((buffer[index] != '1')||(buffer[index] != '0')){
				board[hIndex][linelen] = 0;
			}
			else{
				board[hIndex][linelen] = 1;
			}
			linelen++;
		}
		hIndex++;
	

	}

	/* malloc board */
	//TODO
	//*board = (int)malloc((LENGTH*WIDTH) * sizeof(int));

	

	/* begin run */
	while(status != -1){
		status = display(board);
		status = update(board);
	}
	return 0;

}
/* Pints out board in a color coordinated fashion */
int display(int board[LENGTH][WIDTH]){
	int l = LENGTH;
	int w = WIDTH;	
	
	/* quick and easy print */
	for(int iterL = 0; iterL < l; iterL++){
		for (int iterW = 0; iterW < w; iterW++){
			if(board[iterL][iterW] == 2){
				board[iterL][iterW] = 1; // new children become adults, helps simul death+life
			}
			printf("%d",board[iterL][iterW]);
		}
		printf("\n");
	}
	return 0;	
}
/* runs through and updates each cell */
int update(int board[LENGTH][WIDTH]){
	int l = LENGTH;
	int w = WIDTH;	
	int nb[3][3];

	/* quick and easy print */
	for(int iterL = 0; iterL < l; iterL++){
		for (int iterW = 0; iterW < w; iterW++){
			int nBool[4] = {1,1,1,1};
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
				}
				else{
					nb[0][0] = '#';
					nb[2][0] = '#';
					nb[1][0] = '#';
				}
				if( nBool[3]){
					nb[0][2] = board[iterL-1][iterW+1];
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
				}
				else{
					nb[0][0] = '#';
					nb[2][0] = '#';
					nb[1][0] = '#';
				}
				if( nBool[3]){
					nb[2][2] = board[iterL+1][iterW+1];
				}
				else{
					nb[2][2] = '#';
					nb[1][2] = '#';
					nb[0][2] = '#';
				}
			}						// middle
			nb[1][1] = board[iterL][iterW];


			


			int status = survive(nb);
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
					board[iterL][iterW] = 5;	// Death age here
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
/* Survive, returns 1 if the cell lives and 0 if it dies */
int survive(int nb[3][3]){
	int alive = 0;

	for (int iterL = 0; iterL < 3; iterL++){
		for (int iterW = 0; iterW < 3; iterW++){
			if(nb[iterL][iterW] == 1){
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
	return 1;
}
