/* This file written 2021 by Ruimin Ma and Duosi Dai */

#include <stdbool.h>
#include <stdlib.h>

const int CENTERPIECEx = 20;
const int CENTERPIECEy = 5;


//2 bits = starting location offset from centerpiece for block 1 // 4*3 bits = block 0,2,3 offset from block 1. //4*4 bits = offset for rotation points
//rotation points won't be filled in by the block after rotation, but has to be rotated across when rotating.
//points have 4 bits, first 2 bits represent X. Last 2 represents Y.
//Generally 00 = -1, 01 = 0, 10 = 1. For block 3, and rotationpoints 3 and 4, it's instead (for x) 00=-1 01=0 10=1 11=2 (for y) 00=-2 01=-1 10=0 11=1

														//offs b0   b2   b3   
const int JBlock0def = 0b010100011000110000000000000000; //01 0100 0110 0011 -----------
const int JBlock1def = 0b011001000100010000000000000000; //01 1001 0001 0001 -----------
const int JBlock2def = 0b010110010010010000000000000000; //01 0110 0100 1001 -----------
const int JBlock3def = 0b010001100110110000000000000000; //01 0001 1001 1011 -----------

const int LBlock0def = 0b010110010000010000000000000000; //01 0110 0100 0001 -----------
const int LBlock1def = 0b010001100110010000000000000000; //01 0001 1001 1001 -----------
const int LBlock2def = 0b010100011010110000000000000000; //01 0100 0110 1011 -----------
const int LBlock3def = 0b011001000100110000000000000000; //01 1001 0001 0011 -----------

const int SBlock0def = 0b010110000100010000000000000000; //01 0110 0001 0001 -----------
const int SBlock1def = 0b011001011000110000000000000000; //01 1001 0110 0011 -----------

const int ZBlock0def = 0b010100000100110000000000000000; //01 0100 0001 0011 -----------
const int ZBlock1def = 0b010001011010110000000000000000; //01 0001 0110 1011 -----------

const int TBlock0def = 0b000100011000100000000000000000; //00 0100 0110 0010 -----------
const int TBlock1def = 0b011001000101010000000000000000; //01 1001 0001 0101 -----------
const int TBlock2def = 0b010110010010100000000000000000; //01 0110 0100 1010 -----------
const int TBlock3def = 0b010001100101110000000000000000; //01 0001 1001 0111 -----------

const int IBlock0def = 0b000110010001000000000000000000; //00 0110 0100 0100 -----------
const int IBlock1def = 0b100001100111100000000000000000; //10 0001 1001 1110 -----------

const int OBlockdef = 0b0001100010001000000000000000000; //00 0110 0010 0010 -----------

//create a definition of a block that has an x and a y value
typedef struct {
	int x;
	int y;
}Block;

//create a definition of a shape
typedef struct {
	Block block[4];
	int state[4];
}Shape;

//create bool array to contain all the fallen blocks
bool fallenblocks[20][10];

//create object shape
static Shape shape;

int nextshape;

//extern to be able to use score and difficulty declared in other file
extern int score;
extern int difficulty;/////////////


void createShape(int random) {

	nextshape = (rand() % (7-0))+ 7;; // choose random value between [0,7)-------------------
	
	//check which shape to create and use respective shape definition integer
	switch(random) {
	case 0:
	shape.state[0] = JBlock0def;
	shape.state[1] = JBlock1def;
	shape.state[2] = JBlock2def;
	shape.state[3] = JBlock3def;
	break;
	
	case 1:
	shape.state[0] = LBlock0def;
	shape.state[1] = LBlock1def;
	shape.state[2] = LBlock2def;
	shape.state[3] = LBlock3def;
	break;
	
	case 2:
	shape.state[0] = SBlock0def;
	shape.state[1] = SBlock1def;
	shape.state[2] = SBlock0def;
	shape.state[3] = SBlock1def;
	break;
	
	case 3:
	shape.state[0] = ZBlock0def;
	shape.state[1] = ZBlock1def;
	shape.state[2] = ZBlock0def;
	shape.state[3] = ZBlock1def;
	break;
	
	case 4:
	shape.state[0] = TBlock0def;
	shape.state[1] = TBlock1def;
	shape.state[2] = TBlock2def;
	shape.state[3] = TBlock3def;
	break;
	
	case 5:
	shape.state[0] = IBlock0def;
	shape.state[1] = IBlock1def;
	shape.state[2] = IBlock0def;
	shape.state[3] = IBlock1def;
	break;
	
	case 6:
	shape.state[0] = OBlockdef;
	shape.state[1] = OBlockdef;
	shape.state[2] = OBlockdef;
	shape.state[3] = OBlockdef;
	break;
	
	default:
	shape.state[0] = IBlock0def;
	shape.state[1] = IBlock1def;
	shape.state[2] = IBlock0def;
	shape.state[3] = IBlock1def;
	
	}
	
	//define what blocks a shape contains
	shape.block[1].x = CENTERPIECEx-(((shape.state[0])>>28)&0b0011);
	shape.block[1].y = CENTERPIECEy;
	shape.block[0].x = (shape.block[1].x)+(((shape.state[0])>>26)&0b0011) - 1;
	shape.block[0].y = (shape.block[1].y)+(((shape.state[0])>>24)&0b0011) - 1;
	shape.block[2].x = (shape.block[1].x)+(((shape.state[0])>>22)&0b0011) - 1;
	shape.block[2].y = (shape.block[1].y)+(((shape.state[0])>>20)&0b0011) - 1;
	shape.block[3].x = (shape.block[1].x)+(((shape.state[0])>>18)&0b0011) - 1;
	shape.block[3].y = (shape.block[1].y)+(((shape.state[0])>>16)&0b0011) - 2;
	
	
	shape.currentState = 0; //set current state of shape
	
		
}
//use the method drawblock from func.c
void drawShape(void) {
	int i;
	int j;
	for (i=0;i<4;i++) {
		drawBlock(shape.block[i].x, shape.block[i].y); //loop through each block of a shape and draw them
	}
}

void drawNextShape(void) {
	switch(nextshape) {
		
		//J
		case 0:
		drawBlock(23,6);
		drawBlock(23,5);
		drawBlock(23,7);
		drawBlock(22,7);
		break;
		
		//L
		case 1:
		drawBlock(23,6);
		drawBlock(23,5);
		drawBlock(23,7);
		drawBlock(22,5);
		break;
		
		//S
		case 2:
		drawBlock(22,5);
		drawBlock(22,6);
		drawBlock(23,6);
		drawBlock(23,7);
		break;
		
		//Z
		case 3:
		drawBlock(23,5);
		drawBlock(23,4);
		drawBlock(22,5);
		drawBlock(22,6);
		break;
		
		//T
		case 4:
		drawBlock(23,7);
		drawBlock(22,6);
		drawBlock(23,6);
		drawBlock(23,5);
		break;
		
		//I
		case 5:
		drawBlock(23,5);
		drawBlock(23,4);
		drawBlock(23,6);
		drawBlock(23,7);
		break;
		
		//O
		case 6:
		drawBlock(22,6);
		drawBlock(23,6);
		drawBlock(22,5);
		drawBlock(23,5);
		break;
		
		default:
		drawBlock(23,5);
		drawBlock(23,4);
		drawBlock(23,6);
		drawBlock(23,7);
		
	}
}

//draw the fallen blocks on bottom of gamefield
void drawFallenblocks(void) {
	int x;
	int y;
	for(x = 0; x<20; x++){
		for(y = 0; y<10; y++){
			if(fallenblocks[x][y]){ //if a block exists at the index, draw it
				drawBlock(x+1, y+1);
			}
		}
	}
}

void breakLine(int line){
	int i;
	for(i = 0; i<10; i++){ //loop through the line and remove all blocks from that line
		fallenblocks[line][i] = 0;
	}
	line++;
	for(line; line<20; line++){
		for(i = 0; i<10; i++){
			//if exists
			if(fallenblocks[line][i]){
				//move block downwards.
				fallenblocks[line][i]=0;
				fallenblocks[line-1][i]=1;
			}
		}
	}
	
	score += 10*(difficulty+1); //increment score
}

//remove all blocks from fallenblocks
void clearBlocks(void) {
	int i;
	int j;
	for(i=0;i<20;i++) 
		for (j=0;j<10;j++) 
			if (fallenblocks[i][j]) 
				fallenblocks[i][j] = 0;
}

void checkLines(void){
	int line;
	int count;
	int y;
	for(line = 0; line<20; line++){ //loop through each row on the game field
		count = 0;
		for(y = 0; y<10; y++)
			if(!(fallenblocks[line][y])) //add count for all empty blocks on the line
				count++;

		if(count==0){ //if the count is zero, it means that there are no empty blocks on the line, its full, break line
			breakLine(line);
			line--;
			}
	}
	
}

//check if movement leads to collision.
bool collisionCheck(void){
	int x;
	int y;
	int i;
	
	//loop through each block and check if it exists in fallenblocks
	for(i = 0; i<4; i++){
		x = shape.block[i].x;
		y = shape.block[i].y;
		if(fallenblocks[x-1][y-1]){
		return 1;
		}
	}
	
	//check if any block is 0 (at the floor)
	if (shape.block[0].x == 0 || shape.block[1].x == 0 || shape.block[2].x == 0 || shape.block[3].x == 0) { 
	return 1;
	}
	
	else{
	return 0;
	}
	
}


void impact(void) {
	
	int i=0;
	int j=0;
	int xval;
	int yval;
	int q;
	
	//add shape to fallenblocks
	for(q = 0; q<4; q++){
		xval = shape.block[q].x;
		yval = shape.block[q].y;
		fallenblocks[xval-1][yval-1]=1;
	}
	
	//create a new shape, check if full line
	createShape(nextshape);
	checkLines();
	
	//if a collision is made right after the new shape is created, it means game over
	if (collisionCheck()) {
		clearBlocks();
		gameover();
	} else {
		drawShape();
	}
}

bool wallCheck(void){
	//check against left wall
	if (shape.block[0].y <= 0 || shape.block[1].y <= 0 || shape.block[2].y <= 0 || shape.block[3].y <= 0){
	return 1;
	}
	//check against right wall
	if (shape.block[0].y >= 11 || shape.block[1].y >= 11 || shape.block[2].y >= 11 || shape.block[3].y >= 11){
	return 1;
	}
	return 0;
}
//make block go one step down
void gravity(void) {
	int i;
	for (i=0;i<4;i++) 
		shape.block[i].x -= 1;
	
	//if a collision is detected, reverse the move
	if(collisionCheck()){
		for (i=0;i<4;i++) {
			shape.block[i].x += 1;	
		}
		impact();	
	}
	
}

void moveLeft(void) {
	int i;
	for (i=0;i<4;i++) {
		shape.block[i].y -= 1;	
	}	
	
	//check if trying to pass over wall.
	if(wallCheck()){
			
		//revert movement
		for (i=0;i<4;i++) {
			shape.block[i].y += 1;
		}
			
		//no wall, check for other collision
	}else if(collisionCheck()){
		
		//revert movement
		for (i=0;i<4;i++) {
			shape.block[i].y += 1;
		}
			
	}
		
}

void moveRight(void) {
	int i;
		for (i=0;i<4;i++) {
			shape.block[i].y += 1;
		}
		
		//check if trying to pass over wall.
		if(wallCheck()){
			
			//revert movement
			for (i=0;i<4;i++) {
				shape.block[i].y -= 1;
			}
			
			//no wall, check for other collision
		}else if(collisionCheck()){
			//revert movement
			for (i=0;i<4;i++) {
				shape.block[i].y -= 1;
			}
		}		
}