#include "../include/DrawService.hpp"

#include <iostream>
#include <assert.h>
#include <math.h>

//Drawing info

// Defines
#define PI 3.14159265359

DrawService::DrawService(int width, int height, unsigned char *pixels){
	//Print
	std::cout << "DrawService.cpp\tInitializing" << std::endl;
	
	// Init
	this->width = width;
	this->height = height;
	this->pixels = pixels;
	this->CHAR_WIDTH = 5;
	this->CHAR_HEIGHT = 9;
}

DrawService::~DrawService(void){
	std::cout << "DrawService.cpp\tFinalizing" << std::endl;
}

/*
*	Fills the entire screen with color rgb
*/
void DrawService::fill(unsigned char r, unsigned char g, unsigned char b){
	int i;
    for(i = 0; i < width*height; i++){
    	pixels[i*3+2] = r;	
    	pixels[i*3+1] = g;
    	pixels[i*3+0] = b;
    }
}

/*
*	Fills the entire area with a given color, 
*/
void DrawService::fillArea(int x, int y, unsigned char r, unsigned char g, unsigned char b){
	setPixel(x, y, r, g, b);
	
	//Check neighbors (x+1, y)
	if(getRed(x+1, y) != r || getGreen(x+1, y) != g || getBlue(x+1, y) != b){
		fillArea(x+1, y, r, g, b);
	}
	
	//Check neighbors (x-1, y)
	if(getRed(x-1, y) != r || getGreen(x-1, y) != g || getBlue(x-1, y) != b){
		fillArea(x-1, y, r, g, b);
	}
	
	//Check neighbors (x, y+1)
	if(getRed(x, y+1) != r || getGreen(x, y+1) != g || getBlue(x, y+1) != b){
		fillArea(x, y+1, r, g, b);
	}
	
	//Check neighbors (x, y-1)
	if(getRed(x, y-1) != r || getGreen(x, y-1) != g || getBlue(x, y-1) != b){
		fillArea(x, y-1, r, g, b);
	}
}

/*
* TODO
*/
void DrawService::drawChar(int xc, int yc, char c, unsigned char r, unsigned char g, unsigned char b, int size, bool fill){
	drawCharCenter(xc+2, yc+4, c, r, g, b, size, fill);
}

/*
* TODO
*/
void DrawService::drawCharCenter(int xc, int yc, char c, unsigned char r, unsigned char g, unsigned char b, int size, bool fill){
	int i;

	switch(c){
		case 'A':
		{
			//Init
			int x[12];
			int y[12];
		
			x[0] = xc-2;
			y[0] = yc+4;
			x[1] = xc-1;
			y[1] = yc+4;
			x[2] = xc-1;
			y[2] = yc+2;
			x[3] = xc+1;
			y[3] = yc+2;
			x[4] = xc+1;
			y[4] = yc+4;
			x[5] = xc+2;
			y[5] = yc+4;
			x[6] = xc+2;
			y[6] = yc-4;
			x[7] = xc-2;
			y[7] = yc-4;
		
			x[8] = xc-1;
			y[8] = yc;
			x[9] = xc+1;
			y[9] = yc;
			x[10] = xc+1;
			y[10] = yc-2;
			x[11] = xc-1;
			y[11] = yc-2;
		
			//Scale
			for(i = 0; i<12; i++){
				x[i] = x[i]*size + (xc - xc*size);
				y[i] = y[i]*size + (yc - yc*size);
			}
		
			//Draw
			drawLine(x[0], y[0], x[1], y[1], r, g, b);
			drawLine(x[1], y[1], x[2], y[2], r, g, b);
			drawLine(x[2], y[2], x[3], y[3], r, g, b);
			drawLine(x[3], y[3], x[4], y[4], r, g, b);
			drawLine(x[4], y[4], x[5], y[5], r, g, b);
			drawLine(x[5], y[5], x[6], y[6], r, g, b);
			drawLine(x[6], y[6], x[7], y[7], r, g, b);
			drawLine(x[7], y[7], x[0], y[0], r, g, b);
			
			drawLine(x[8], y[8], x[9], y[9], r, g, b);
			drawLine(x[9], y[9], x[10], y[10], r, g, b);
			drawLine(x[10], y[10], x[11], y[11], r, g, b);
			drawLine(x[11], y[11], x[8], y[8], r, g, b);
			
			if(fill == 1){
				fillArea(xc, yc+1*size, r, g, b);
				fillArea(xc, yc-3*size, r, g, b);
			}
			break;
		}
		case 'B':
		{
			//Init
			int x[18];
			int y[18];
			
			x[0] = xc-2;
			y[0] = yc+4;
			x[1] = xc+1;
			y[1] = yc+4;
			x[2] = xc+2;
			y[2] = yc+2;
			x[3] = xc+1;
			y[3] = yc;
			x[4] = xc+2;
			y[4] = yc-2;
			x[5] = xc+1;
			y[5] = yc-4;
			x[6] = xc-2;
			y[6] = yc-4;
			
			x[7] = xc-1;
			y[7] = yc-3;
			x[8] = xc;
			y[8] = yc-3;
			x[9] = xc+1;
			y[9] = yc-2;
			x[10] = xc;
			y[10] = yc-1;
			x[11] = xc-1;
			y[11] = yc-1;
			
			x[12] = xc-1;
			y[12] = yc+1;
			x[13] = xc;
			y[13] = yc+1;
			x[14] = xc+1;
			y[14] = yc+2;
			x[15] = xc;
			y[15] = yc+3;
			x[16] = xc-1;
			y[16] = yc+3;
		
			//Scale
			for(i = 0; i<17; i++){
				x[i] = x[i]*size + (xc - xc*size);
				y[i] = y[i]*size + (yc - yc*size);
			}
			
			//Draw
			drawLine(x[0], y[0], x[1], y[1], r, g, b);
			drawLine(x[1], y[1], x[2], y[2], r, g, b);
			drawLine(x[2], y[2], x[3], y[3], r, g, b);
			drawLine(x[3], y[3], x[4], y[4], r, g, b);
			drawLine(x[4], y[4], x[5], y[5], r, g, b);
			drawLine(x[5], y[5], x[6], y[6], r, g, b);
			drawLine(x[6], y[6], x[0], y[0], r, g, b);
			
			drawLine(x[7], y[7], x[8], y[8], r, g, b);
			drawLine(x[8], y[8], x[9], y[9], r, g, b);
			drawLine(x[9], y[9], x[10], y[10], r, g, b);
			drawLine(x[10], y[10], x[11], y[11], r, g, b);
			drawLine(x[11], y[11], x[7], y[7], r, g, b);
			
			drawLine(x[12], y[12], x[13], y[13], r, g, b);
			drawLine(x[13], y[13], x[14], y[14], r, g, b);
			drawLine(x[14], y[14], x[15], y[15], r, g, b);
			drawLine(x[15], y[15], x[16], y[16], r, g, b);
			drawLine(x[16], y[16], x[12], y[12], r, g, b);
			
			if(fill == 1){
				fillArea(xc-size, yc, r, g, b);
			}
			break;
		}
		case 'C':
		{
			//Init
			int x[14];
			int y[14];
			
			x[0] = xc+2;
			y[0] = yc-4;
			x[1] = xc;
			y[1] = yc-4;
			x[2] = xc-1;
			y[2] = yc-3;
			x[3] = xc-2;
			y[3] = yc-1;
			x[4] = xc-2;
			y[4] = yc+1;
			x[5] = xc-1;
			y[5] = yc+3;
			x[6] = xc;
			y[6] = yc+4;
			x[7] = xc+2;
			y[7] = yc+4;
			x[8] = xc+2;
			y[8] = yc+3;
			x[9] = xc;
			y[9] = yc+3;
			x[10] = xc-1;
			y[10] = yc+1;
			x[11] = xc-1;
			y[11] = yc-1;
			x[12] = xc;
			y[12] = yc-3;
			x[13] = xc+2;
			y[13] = yc-3;
		
			//Scale
			for(i = 0; i<14; i++){
				x[i] = x[i]*size + (xc - xc*size);
				y[i] = y[i]*size + (yc - yc*size);
			}
			
			//Draw
			drawLine(x[0], y[0], x[1], y[1], r, g, b);
			drawLine(x[1], y[1], x[2], y[2], r, g, b);
			drawLine(x[2], y[2], x[3], y[3], r, g, b);
			drawLine(x[3], y[3], x[4], y[4], r, g, b);
			drawLine(x[4], y[4], x[5], y[5], r, g, b);
			drawLine(x[5], y[5], x[6], y[6], r, g, b);
			drawLine(x[6], y[6], x[7], y[7], r, g, b);
			drawLine(x[7], y[7], x[8], y[8], r, g, b);
			drawLine(x[8], y[8], x[9], y[9], r, g, b);
			drawLine(x[9], y[9], x[10], y[10], r, g, b);
			drawLine(x[10], y[10], x[11], y[11], r, g, b);
			drawLine(x[11], y[11], x[12], y[12], r, g, b);
			drawLine(x[12], y[12], x[13], y[13], r, g, b);
			drawLine(x[13], y[13], x[0], y[0], r, g, b);
			
			if(fill == 1){
				fillArea(xc-2*size+1, yc, r, g, b);
			}
			break;
		}
		case 'D':
		{
			//Init
			int x[14];
			int y[14];
			
			x[0] = xc-2;
			y[0] = yc+4;
			x[1] = xc;
			y[1] = yc+4;
			x[2] = xc+1;
			y[2] = yc+3;
			x[3] = xc+2;
			y[3] = yc+1;
			x[4] = xc+2;
			y[4] = yc-1;
			x[5] = xc+1;
			y[5] = yc-3;
			x[6] = xc;
			y[6] = yc-4;
			x[7] = xc-2;
			y[7] = yc-4;
			x[8] = xc-1;
			y[8] = yc+3;
			x[9] = xc;
			y[9] = yc+3;
			x[10] = xc+1;
			y[10] = yc+1;
			x[11] = xc+1;
			y[11] = yc-1;
			x[12] = xc;
			y[12] = yc-3;
			x[13] = xc-1;
			y[13] = yc-3;
		
			//Scale
			for(i = 0; i<14; i++){
				x[i] = x[i]*size + (xc - xc*size);
				y[i] = y[i]*size + (yc - yc*size);
			}
			
			//Draw
			drawLine(x[0], y[0], x[1], y[1], r, g, b);
			drawLine(x[1], y[1], x[2], y[2], r, g, b);
			drawLine(x[2], y[2], x[3], y[3], r, g, b);
			drawLine(x[3], y[3], x[4], y[4], r, g, b);
			drawLine(x[4], y[4], x[5], y[5], r, g, b);
			drawLine(x[5], y[5], x[6], y[6], r, g, b);
			drawLine(x[6], y[6], x[7], y[7], r, g, b);
			drawLine(x[7], y[7], x[0], y[0], r, g, b);
			
			drawLine(x[8], y[8], x[9], y[9], r, g, b);
			drawLine(x[9], y[9], x[10], y[10], r, g, b);
			drawLine(x[10], y[10], x[11], y[11], r, g, b);
			drawLine(x[11], y[11], x[12], y[12], r, g, b);
			drawLine(x[12], y[12], x[13], y[13], r, g, b);
			drawLine(x[13], y[13], x[8], y[8], r, g, b);
			
			if(fill == 1){
				fillArea(xc-2*size+1, yc, r, g, b);
			}
			break;
		}
		case 'E':
		{
			//Init
			int x[11];
			int y[11];
			
			x[0] = xc-2;
			y[0] = yc-4;
			x[1] = xc+2;
			y[1] = yc-4;
			x[2] = xc+2;
			y[2] = yc-2;
			x[3] = xc-1;
			y[3] = yc-2;
			x[4] = xc-1;
			y[4] = yc;
			x[5] = xc+2;
			y[5] = yc;
			x[6] = xc+2;
			y[6] = yc+1;
			x[7] = xc-1;
			y[7] = yc+1;
			x[8] = xc-1;
			y[8] = yc+3;
			x[9] = xc+2;
			y[9] = yc+3;
			x[10] = xc+2;
			y[10] = yc+4;
			x[11] = xc-2;
			y[11] = yc+4;
		
			//Scale
			for(i = 0; i<12; i++){
				x[i] = x[i]*size + (xc - xc*size);
				y[i] = y[i]*size + (yc - yc*size);
			}
			
			//Draw
			drawLine(x[0], y[0], x[1], y[1], r, g, b);
			drawLine(x[1], y[1], x[2], y[2], r, g, b);
			drawLine(x[2], y[2], x[3], y[3], r, g, b);
			drawLine(x[3], y[3], x[4], y[4], r, g, b);
			drawLine(x[4], y[4], x[5], y[5], r, g, b);
			drawLine(x[5], y[5], x[6], y[6], r, g, b);
			drawLine(x[6], y[6], x[7], y[7], r, g, b);
			drawLine(x[7], y[7], x[8], y[8], r, g, b);
			drawLine(x[8], y[8], x[9], y[9], r, g, b);
			drawLine(x[9], y[9], x[10], y[10], r, g, b);
			drawLine(x[10], y[10], x[11], y[11], r, g, b);
			drawLine(x[11], y[11], x[0], y[0], r, g, b);
			
			if(fill == 1){
				fillArea(xc-2*size+1, yc, r, g, b);
			}
			break;
		}
		case 'F':
		{
			//Init
			int x[10];
			int y[10];
			
			x[0] = xc-2;
			y[0] = yc-4;
			x[1] = xc+2;
			y[1] = yc-4;
			x[2] = xc+2;
			y[2] = yc-2;
			x[3] = xc-1;
			y[3] = yc-2;
			x[4] = xc-1;
			y[4] = yc;
			x[5] = xc+2;
			y[5] = yc;
			x[6] = xc+2;
			y[6] = yc+1;
			x[7] = xc-1;
			y[7] = yc+1;
			x[8] = xc-1;
			y[8] = yc+4;
			x[9] = xc-2;
			y[9] = yc+4;
		
			//Scale
			for(i = 0; i<10; i++){
				x[i] = x[i]*size + (xc - xc*size);
				y[i] = y[i]*size + (yc - yc*size);
			}
			
			//Draw
			drawLine(x[0], y[0], x[1], y[1], r, g, b);
			drawLine(x[1], y[1], x[2], y[2], r, g, b);
			drawLine(x[2], y[2], x[3], y[3], r, g, b);
			drawLine(x[3], y[3], x[4], y[4], r, g, b);
			drawLine(x[4], y[4], x[5], y[5], r, g, b);
			drawLine(x[5], y[5], x[6], y[6], r, g, b);
			drawLine(x[6], y[6], x[7], y[7], r, g, b);
			drawLine(x[7], y[7], x[8], y[8], r, g, b);
			drawLine(x[8], y[8], x[9], y[9], r, g, b);
			drawLine(x[9], y[9], x[0], y[0], r, g, b);
			
			if(fill == 1){
				fillArea(xc-2*size+1, yc, r, g, b);
			}
			break;
		}
		case 'G':
		{
			//Init
			int x[16];
			int y[16];
			
			x[0] = xc+2;
			y[0] = yc-4;
			x[1] = xc-1;
			y[1] = yc-4;
			x[2] = xc-2;
			y[2] = yc-2;
			x[3] = xc-2;
			y[3] = yc+2;
			x[4] = xc-1;
			y[4] = yc+4;
			x[5] = xc+1;
			y[5] = yc+4;
			x[6] = xc+2;
			y[6] = yc+3;
			x[7] = xc+2;
			y[7] = yc;
			x[8] = xc;
			y[8] = yc;
			x[9] = xc;
			y[9] = yc+1;
			x[10] = xc+1;
			y[10] = yc+1;
			x[11] = xc+1;
			y[11] = yc+3;
			x[12] = xc;
			y[12] = yc+3;
			x[13] = xc-1;
			y[13] = yc;
			x[14] = xc;
			y[14] = yc-3;
			x[15] = xc+2;
			y[15] = yc-3;
		
			//Scale
			for(i = 0; i<16; i++){
				x[i] = x[i]*size + (xc - xc*size);
				y[i] = y[i]*size + (yc - yc*size);
			}
			
			//Draw
			drawLine(x[0], y[0], x[1], y[1], r, g, b);
			drawLine(x[1], y[1], x[2], y[2], r, g, b);
			drawLine(x[2], y[2], x[3], y[3], r, g, b);
			drawLine(x[3], y[3], x[4], y[4], r, g, b);
			drawLine(x[4], y[4], x[5], y[5], r, g, b);
			drawLine(x[5], y[5], x[6], y[6], r, g, b);
			drawLine(x[6], y[6], x[7], y[7], r, g, b);
			drawLine(x[7], y[7], x[8], y[8], r, g, b);
			drawLine(x[8], y[8], x[9], y[9], r, g, b);
			drawLine(x[9], y[9], x[10], y[10], r, g, b);
			drawLine(x[10], y[10], x[11], y[11], r, g, b);
			drawLine(x[11], y[11], x[12], y[12], r, g, b);
			drawLine(x[12], y[12], x[13], y[13], r, g, b);
			drawLine(x[13], y[13], x[14], y[14], r, g, b);
			drawLine(x[14], y[14], x[15], y[15], r, g, b);
			drawLine(x[15], y[15], x[0], y[0], r, g, b);
			
			if(fill == 1){
				fillArea(xc-2*size+1, yc, r, g, b);
				fillArea(xc+size, yc+size, r, g, b);
			}
			break;
		}
		case 'H':
		{
			//Init
			int x[12];
			int y[12];
			
			x[0] = xc-2;
			y[0] = yc-4;
			x[1] = xc-1;
			y[1] = yc-4;
			x[2] = xc-1;
			y[2] = yc-1;
			x[3] = xc+1;
			y[3] = yc-1;
			x[4] = xc+1;
			y[4] = yc-4;
			x[5] = xc+2;
			y[5] = yc-4;
			x[6] = xc+2;
			y[6] = yc+4;
			x[7] = xc+1;
			y[7] = yc+4;
			x[8] = xc+1;
			y[8] = yc+1;
			x[9] = xc-1;
			y[9] = yc+1;
			x[10] = xc-1;
			y[10] = yc+4;
			x[11] = xc-2;
			y[11] = yc+4;
		
			//Scale
			for(i = 0; i<12; i++){
				x[i] = x[i]*size + (xc - xc*size);
				y[i] = y[i]*size + (yc - yc*size);
			}
			
			//Draw
			drawLine(x[0], y[0], x[1], y[1], r, g, b);
			drawLine(x[1], y[1], x[2], y[2], r, g, b);
			drawLine(x[2], y[2], x[3], y[3], r, g, b);
			drawLine(x[3], y[3], x[4], y[4], r, g, b);
			drawLine(x[4], y[4], x[5], y[5], r, g, b);
			drawLine(x[5], y[5], x[6], y[6], r, g, b);
			drawLine(x[6], y[6], x[7], y[7], r, g, b);
			drawLine(x[7], y[7], x[8], y[8], r, g, b);
			drawLine(x[8], y[8], x[9], y[9], r, g, b);
			drawLine(x[9], y[9], x[10], y[10], r, g, b);
			drawLine(x[10], y[10], x[11], y[11], r, g, b);
			drawLine(x[11], y[11], x[0], y[0], r, g, b);
			
			if(fill == 1){
				fillArea(xc-2*size+1, yc, r, g, b);
			}
			break;
		}
		case 'I':
		{
			//Init
			int x[12];
			int y[12];
			
			x[0] = xc-2;
			y[0] = yc-4;
			x[1] = xc+2;
			y[1] = yc-4;
			x[2] = xc+2;
			y[2] = yc-3;
			x[3] = xc+1;
			y[3] = yc-3;
			x[4] = xc+1;
			y[4] = yc+3;
			x[5] = xc+2;
			y[5] = yc+3;
			x[6] = xc+2;
			y[6] = yc+4;
			x[7] = xc-2;
			y[7] = yc+4;
			x[8] = xc-2;
			y[8] = yc+3;
			x[9] = xc-1;
			y[9] = yc+3;
			x[10] = xc-1;
			y[10] = yc-3;
			x[11] = xc-2;
			y[11] = yc-3;
		
			//Scale
			for(i = 0; i<12; i++){
				x[i] = x[i]*size + (xc - xc*size);
				y[i] = y[i]*size + (yc - yc*size);
			}
			
			//Draw
			drawLine(x[0], y[0], x[1], y[1], r, g, b);
			drawLine(x[1], y[1], x[2], y[2], r, g, b);
			drawLine(x[2], y[2], x[3], y[3], r, g, b);
			drawLine(x[3], y[3], x[4], y[4], r, g, b);
			drawLine(x[4], y[4], x[5], y[5], r, g, b);
			drawLine(x[5], y[5], x[6], y[6], r, g, b);
			drawLine(x[6], y[6], x[7], y[7], r, g, b);
			drawLine(x[7], y[7], x[8], y[8], r, g, b);
			drawLine(x[8], y[8], x[9], y[9], r, g, b);
			drawLine(x[9], y[9], x[10], y[10], r, g, b);
			drawLine(x[10], y[10], x[11], y[11], r, g, b);
			drawLine(x[11], y[11], x[0], y[0], r, g, b);
			
			if(fill == 1){
				fillArea(xc, yc, r, g, b);
			}
			break;
		}
		case 'J':
		{
			//Init
			int x[11];
			int y[11];
			
			x[0] = xc-2;
			y[0] = yc-4;
			x[1] = xc+2;
			y[1] = yc-4;
			x[2] = xc+2;
			y[2] = yc+2;
			x[3] = xc+1;
			y[3] = yc+4;
			x[4] = xc-1;
			y[4] = yc+4;
			x[5] = xc-2;
			y[5] = yc+3;
			x[6] = xc-1;
			y[6] = yc+2;
			x[7] = xc;
			y[7] = yc+3;
			x[8] = xc+1;
			y[8] = yc+3;
			x[9] = xc+1;
			y[9] = yc-3;
			x[10] = xc-2;
			y[10] = yc-3;
		
			//Scale
			for(i = 0; i<11; i++){
				x[i] = x[i]*size + (xc - xc*size);
				y[i] = y[i]*size + (yc - yc*size);
			}
			
			//Draw
			drawLine(x[0], y[0], x[1], y[1], r, g, b);
			drawLine(x[1], y[1], x[2], y[2], r, g, b);
			drawLine(x[2], y[2], x[3], y[3], r, g, b);
			drawLine(x[3], y[3], x[4], y[4], r, g, b);
			drawLine(x[4], y[4], x[5], y[5], r, g, b);
			drawLine(x[5], y[5], x[6], y[6], r, g, b);
			drawLine(x[6], y[6], x[7], y[7], r, g, b);
			drawLine(x[7], y[7], x[8], y[8], r, g, b);
			drawLine(x[8], y[8], x[9], y[9], r, g, b);
			drawLine(x[9], y[9], x[10], y[10], r, g, b);
			drawLine(x[10], y[10], x[0], y[0], r, g, b);
			
			if(fill == 1){
				fillArea(xc+2*size-1, yc, r, g, b);
				fillArea(xc, yc+4*size-1, r, g, b);
			}
			break;
		}
		case 'K':
		{
			//Init
			int x[11];
			int y[11];
			
			x[0] = xc-2;
			y[0] = yc-4;
			x[1] = xc-1;
			y[1] = yc-4;
			x[2] = xc-1;
			y[2] = yc-1;
			x[3] = xc+1;
			y[3] = yc-4;
			x[4] = xc+2;
			y[4] = yc-4;
			x[5] = xc;
			y[5] = yc;
			x[6] = xc+2;
			y[6] = yc+4;
			x[7] = xc+1;
			y[7] = yc+4;
			x[8] = xc-1;
			y[8] = yc+1;
			x[9] = xc-1;
			y[9] = yc+4;
			x[10] = xc-2;
			y[10] = yc+4;
		
			//Scale
			for(i = 0; i<11; i++){
				x[i] = x[i]*size + (xc - xc*size);
				y[i] = y[i]*size + (yc - yc*size);
			}
			
			//Draw
			drawLine(x[0], y[0], x[1], y[1], r, g, b);
			drawLine(x[1], y[1], x[2], y[2], r, g, b);
			drawLine(x[2], y[2], x[3], y[3], r, g, b);
			drawLine(x[3], y[3], x[4], y[4], r, g, b);
			drawLine(x[4], y[4], x[5], y[5], r, g, b);
			drawLine(x[5], y[5], x[6], y[6], r, g, b);
			drawLine(x[6], y[6], x[7], y[7], r, g, b);
			drawLine(x[7], y[7], x[8], y[8], r, g, b);
			drawLine(x[8], y[8], x[9], y[9], r, g, b);
			drawLine(x[9], y[9], x[10], y[10], r, g, b);
			drawLine(x[10], y[10], x[0], y[0], r, g, b);
			
			if(fill == 1){
				fillArea(xc-2*size+1, yc, r, g, b);
			}
			break;
		}
		case 'L':
		{
			//Init
			int x[6];
			int y[6];
			
			x[0] = xc-2;
			y[0] = yc-4;
			x[1] = xc-1;
			y[1] = yc-4;
			x[2] = xc-1;
			y[2] = yc+3;
			x[3] = xc+2;
			y[3] = yc+3;
			x[4] = xc+2;
			y[4] = yc+4;
			x[5] = xc-2;
			y[5] = yc+4;
		
			//Scale
			for(i = 0; i<6; i++){
				x[i] = x[i]*size + (xc - xc*size);
				y[i] = y[i]*size + (yc - yc*size);
			}
			
			//Draw
			drawLine(x[0], y[0], x[1], y[1], r, g, b);
			drawLine(x[1], y[1], x[2], y[2], r, g, b);
			drawLine(x[2], y[2], x[3], y[3], r, g, b);
			drawLine(x[3], y[3], x[4], y[4], r, g, b);
			drawLine(x[4], y[4], x[5], y[5], r, g, b);
			drawLine(x[5], y[5], x[0], y[0], r, g, b);
			
			if(fill == 1){
				fillArea(xc-2*size+1, yc, r, g, b);
			}
			break;
		}
		case 'M':
		{
			//Init
			int x[10];
			int y[10];
			
			x[0] = xc-2;
			y[0] = yc+4;
			x[1] = xc-2;
			y[1] = yc-4;
			x[2] = xc;
			y[2] = yc-1;
			x[3] = xc+2;
			y[3] = yc-4;
			x[4] = xc+2;
			y[4] = yc+4;
			x[5] = xc+1;
			y[5] = yc+4;
			x[6] = xc+1;
			y[6] = yc-1;
			x[7] = xc;
			y[7] = yc+1;
			x[8] = xc-1;
			y[8] = yc-1;
			x[9] = xc-1;
			y[9] = yc+4;
		
			//Scale
			for(i = 0; i<10; i++){
				x[i] = x[i]*size + (xc - xc*size);
				y[i] = y[i]*size + (yc - yc*size);
			}
			
			//Draw
			drawLine(x[0], y[0], x[1], y[1], r, g, b);
			drawLine(x[1], y[1], x[2], y[2], r, g, b);
			drawLine(x[2], y[2], x[3], y[3], r, g, b);
			drawLine(x[3], y[3], x[4], y[4], r, g, b);
			drawLine(x[4], y[4], x[5], y[5], r, g, b);
			drawLine(x[5], y[5], x[6], y[6], r, g, b);
			drawLine(x[6], y[6], x[7], y[7], r, g, b);
			drawLine(x[7], y[7], x[8], y[8], r, g, b);
			drawLine(x[8], y[8], x[9], y[9], r, g, b);
			drawLine(x[9], y[9], x[0], y[0], r, g, b);
			
			if(fill == 1){
				fillArea(xc-2*size+1, yc, r, g, b);
				fillArea(xc+2*size-1, yc, r, g, b);
				fillArea(xc, yc-size, r, g, b);
			}
			break;
		}
		case 'N':
		{
			//Init
			int x[10];
			int y[10];
			
			x[0] = xc-2;
			y[0] = yc+4;
			x[1] = xc-2;
			y[1] = yc-4;
			x[2] = xc-1;
			y[2] = yc-4;
			x[3] = xc+1;
			y[3] = yc+1;
			x[4] = xc+1;
			y[4] = yc-4;
			x[5] = xc+2;
			y[5] = yc-4;
			x[6] = xc+2;
			y[6] = yc+4;
			x[7] = xc+1;
			y[7] = yc+4;
			x[8] = xc-1;
			y[8] = yc-1;
			x[9] = xc-1;
			y[9] = yc+4;
			
			//Scale
			for(i = 0; i<10; i++){
				x[i] = x[i]*size + (xc - xc*size);
				y[i] = y[i]*size + (yc - yc*size);
			}
			
			//Draw
			drawLine(x[0], y[0], x[1], y[1], r, g, b);
			drawLine(x[1], y[1], x[2], y[2], r, g, b);
			drawLine(x[2], y[2], x[3], y[3], r, g, b);
			drawLine(x[3], y[3], x[4], y[4], r, g, b);
			drawLine(x[4], y[4], x[5], y[5], r, g, b);
			drawLine(x[5], y[5], x[6], y[6], r, g, b);
			drawLine(x[6], y[6], x[7], y[7], r, g, b);
			drawLine(x[7], y[7], x[8], y[8], r, g, b);
			drawLine(x[8], y[8], x[9], y[9], r, g, b);
			drawLine(x[9], y[9], x[0], y[0], r, g, b);
			
			if(fill == 1){
				fillArea(xc-2*size+1, yc, r, g, b);
			}
			break;
		}
		case 'O':
		{
			//Init
			int x[14];
			int y[14];
			
			x[0] = xc-2;
			y[0] = yc-3;
			x[1] = xc-1;
			y[1] = yc-4;
			x[2] = xc+1;
			y[2] = yc-4;
			x[3] = xc+2;
			y[3] = yc-3;
			x[4] = xc+2;
			y[4] = yc+3;
			x[5] = xc+1;
			y[5] = yc+4;
			x[6] = xc-1;
			y[6] = yc+4;
			x[7] = xc-2;
			y[7] = yc+3;
			x[8] = xc-1;
			y[8] = yc-2;
			x[9] = xc;
			y[9] = yc-3;
			x[10] = xc+1;
			y[10] = yc-2;
			x[11] = xc+1;
			y[11] = yc+2;
			x[12] = xc;
			y[12] = yc+3;
			x[13] = xc-1;
			y[13] = yc+2;
			
			//Scale
			for(i = 0; i<14; i++){
				x[i] = x[i]*size + (xc - xc*size);
				y[i] = y[i]*size + (yc - yc*size);
			}
			
			//Draw
			drawLine(x[0], y[0], x[1], y[1], r, g, b);
			drawLine(x[1], y[1], x[2], y[2], r, g, b);
			drawLine(x[2], y[2], x[3], y[3], r, g, b);
			drawLine(x[3], y[3], x[4], y[4], r, g, b);
			drawLine(x[4], y[4], x[5], y[5], r, g, b);
			drawLine(x[5], y[5], x[6], y[6], r, g, b);
			drawLine(x[6], y[6], x[7], y[7], r, g, b);
			drawLine(x[7], y[7], x[0], y[0], r, g, b);
			
			drawLine(x[8], y[8], x[9], y[9], r, g, b);
			drawLine(x[9], y[9], x[10], y[10], r, g, b);
			drawLine(x[10], y[10], x[11], y[11], r, g, b);
			drawLine(x[11], y[11], x[12], y[12], r, g, b);
			drawLine(x[12], y[12], x[13], y[13], r, g, b);
			drawLine(x[13], y[13], x[8], y[8], r, g, b);
			
			if(fill == 1){
				fillArea(xc-2*size+1, yc, r, g, b);
			}
			break;
		}
		case 'P':
		{
			//Init
			int x[14];
			int y[14];
			
			x[0] = xc-2;
			y[0] = yc-4;			
			x[1] = xc+1;
			y[1] = yc-4;			
			x[2] = xc+2;
			y[2] = yc-2;			
			x[3] = xc+1;
			y[3] = yc;
			x[4] = xc-1;
			y[4] = yc;
			x[5] = xc-1;
			y[5] = yc+4;
			x[6] = xc-2;
			y[6] = yc+4;
			x[7] = xc-1;
			y[7] = yc-3;
			x[8] = xc;
			y[8] = yc-3;
			x[9] = xc+1;
			y[9] = yc-2;
			x[10] = xc;
			y[10] = yc-1;
			x[11] = xc-1;
			y[11] = yc-1;
			
			//Scale
			for(i = 0; i<12; i++){
				x[i] = x[i]*size + (xc - xc*size);
				y[i] = y[i]*size + (yc - yc*size);
			}
			
			//Draw
			drawLine(x[0], y[0], x[1], y[1], r, g, b);
			drawLine(x[1], y[1], x[2], y[2], r, g, b);
			drawLine(x[2], y[2], x[3], y[3], r, g, b);
			drawLine(x[3], y[3], x[4], y[4], r, g, b);
			drawLine(x[4], y[4], x[5], y[5], r, g, b);
			drawLine(x[5], y[5], x[6], y[6], r, g, b);
			drawLine(x[6], y[6], x[0], y[0], r, g, b);
			
			drawLine(x[7], y[7], x[8], y[8], r, g, b);
			drawLine(x[8], y[8], x[9], y[9], r, g, b);
			drawLine(x[9], y[9], x[10], y[10], r, g, b);
			drawLine(x[10], y[10], x[11], y[11], r, g, b);
			drawLine(x[11], y[11], x[7], y[7], r, g, b);
			
			if(fill == 1){
				fillArea(xc-2*size+1, yc, r, g, b);
			}
			break;
		}
		case 'Q':
		{
			//Init
			int x[18];
			int y[18];
			
			x[0] = xc-2;
			y[0] = yc-3;
			x[1] = xc-1;
			y[1] = yc-4;
			x[2] = xc+1;
			y[2] = yc-4;
			x[3] = xc+2;
			y[3] = yc-3;
			x[4] = xc+2;
			y[4] = yc+1;
			x[5] = xc+1;
			y[5] = yc+2;
			x[6] = xc+2;
			y[6] = yc+3;
			x[7] = xc+1;
			y[7] = yc+4;
			x[8] = xc;
			y[8] = yc+3;
			x[9] = xc;
			y[9] = yc+2;
			x[10] = xc-1;
			y[10] = yc+2;
			x[11] = xc-2;
			y[11] = yc+1;
			x[12] = xc-1;
			y[12] = yc-2;
			x[13] = xc;
			y[13] = yc-3;
			x[14] = xc+1;
			y[14] = yc-2;
			x[15] = xc+1;
			y[15] = yc;
			x[16] = xc;
			y[16] = yc+1;
			x[17] = xc-1;
			y[17] = yc;
			
			//Scale
			for(i = 0; i<18; i++){
				x[i] = x[i]*size + (xc - xc*size);
				y[i] = y[i]*size + (yc - yc*size);
			}
			
			//Draw
			drawLine(x[0], y[0], x[1], y[1], r, g, b);
			drawLine(x[1], y[1], x[2], y[2], r, g, b);
			drawLine(x[2], y[2], x[3], y[3], r, g, b);
			drawLine(x[3], y[3], x[4], y[4], r, g, b);
			drawLine(x[4], y[4], x[5], y[5], r, g, b);
			drawLine(x[5], y[5], x[6], y[6], r, g, b);
			drawLine(x[6], y[6], x[7], y[7], r, g, b);
			drawLine(x[7], y[7], x[8], y[8], r, g, b);
			drawLine(x[8], y[8], x[9], y[9], r, g, b);
			drawLine(x[9], y[9], x[10], y[10], r, g, b);
			drawLine(x[10], y[10], x[11], y[11], r, g, b);
			drawLine(x[11], y[11], x[0], y[0], r, g, b);
			
			drawLine(x[12], y[12], x[13], y[13], r, g, b);
			drawLine(x[13], y[13], x[14], y[14], r, g, b);
			drawLine(x[14], y[14], x[15], y[15], r, g, b);
			drawLine(x[15], y[15], x[16], y[16], r, g, b);
			drawLine(x[16], y[16], x[17], y[17], r, g, b);
			drawLine(x[17], y[17], x[12], y[12], r, g, b);
			
			if(fill == 1){
				fillArea(xc-2*size+1, yc, r, g, b);
			}
			break;
		}
		case 'R':
		{
			//Init
			int x[18];
			int y[18];
			
			x[0] = xc-2;
			y[0] = yc-4;
			x[1] = xc+1;
			y[1] = yc-4;
			x[2] = xc+2;
			y[2] = yc-2;
			x[3] = xc+1;
			y[3] = yc;
			x[4] = xc;
			y[4] = yc;
			x[5] = xc+2;
			y[5] = yc+4;
			x[6] = xc+1;
			y[6] = yc+4;
			x[7] = xc-1;
			y[7] = yc+1;
			x[8] = xc-1;
			y[8] = yc+4;
			x[9] = xc-2;
			y[9] = yc+4;
			x[10] = xc-1;
			y[10] = yc-3;
			x[11] = xc;
			y[11] = yc-3;
			x[12] = xc+1;
			y[12] = yc-2;
			x[13] = xc;
			y[13] = yc-1;
			x[14] = xc-1;
			y[14] = yc-1;
			
			//Scale
			for(i = 0; i<15; i++){
				x[i] = x[i]*size + (xc - xc*size);
				y[i] = y[i]*size + (yc - yc*size);
			}
			
			//Draw
			drawLine(x[0], y[0], x[1], y[1], r, g, b);
			drawLine(x[1], y[1], x[2], y[2], r, g, b);
			drawLine(x[2], y[2], x[3], y[3], r, g, b);
			drawLine(x[3], y[3], x[4], y[4], r, g, b);
			drawLine(x[4], y[4], x[5], y[5], r, g, b);
			drawLine(x[5], y[5], x[6], y[6], r, g, b);
			drawLine(x[6], y[6], x[7], y[7], r, g, b);
			drawLine(x[7], y[7], x[8], y[8], r, g, b);
			drawLine(x[8], y[8], x[9], y[9], r, g, b);
			drawLine(x[9], y[9], x[0], y[0], r, g, b);
			
			drawLine(x[10], y[10], x[11], y[11], r, g, b);
			drawLine(x[11], y[11], x[12], y[12], r, g, b);
			drawLine(x[12], y[12], x[13], y[13], r, g, b);
			drawLine(x[13], y[13], x[14], y[14], r, g, b);
			drawLine(x[14], y[14], x[10], y[10], r, g, b);
			
			if(fill == 1){
				fillArea(xc-2*size+1, yc, r, g, b);
			}
			break;
		}
		case 'S':
		{
			//Init
			int x[12];
			int y[12];
			
			x[0] = xc+2;
			y[0] = yc-4;
			x[1] = xc-2;
			y[1] = yc-4;
			x[2] = xc-2;
			y[2] = yc+1; // +0 ?
			x[3] = xc+1;
			y[3] = yc+1; // +0 ?
			x[4] = xc+1;
			y[4] = yc+3;
			x[5] = xc-2;
			y[5] = yc+3;
			x[6] = xc-2;
			y[6] = yc+4;
			x[7] = xc+2;
			y[7] = yc+4;
			x[8] = xc+2;
			y[8] = yc-1;
			x[9] = xc-1;
			y[9] = yc-1;
			x[10] = xc-1;
			y[10] = yc-3;
			x[11] = xc+2;
			y[11] = yc-3;
			
			//Scale
			for(i = 0; i<12; i++){
				x[i] = x[i]*size + (xc - xc*size);
				y[i] = y[i]*size + (yc - yc*size);
			}
			
			//Draw
			drawLine(x[0], y[0], x[1], y[1], r, g, b);
			drawLine(x[1], y[1], x[2], y[2], r, g, b);
			drawLine(x[2], y[2], x[3], y[3], r, g, b);
			drawLine(x[3], y[3], x[4], y[4], r, g, b);
			drawLine(x[4], y[4], x[5], y[5], r, g, b);
			drawLine(x[5], y[5], x[6], y[6], r, g, b);
			drawLine(x[6], y[6], x[7], y[7], r, g, b);
			drawLine(x[7], y[7], x[8], y[8], r, g, b);
			drawLine(x[8], y[8], x[9], y[9], r, g, b);
			drawLine(x[9], y[9], x[10], y[10], r, g, b);
			drawLine(x[10], y[10], x[11], y[11], r, g, b);
			drawLine(x[11], y[11], x[0], y[0], r, g, b);
			
			if(fill == 1){
				fillArea(xc, yc, r, g, b);
			}
			break;
		}
		case 'T':
		{
			//Init
			int x[8];
			int y[8];
			
			x[0] = xc-2;
			y[0] = yc-4;
			x[1] = xc+2;
			y[1] = yc-4;
			x[2] = xc+2;
			y[2] = yc-2;
			x[3] = xc+1; //+0
			y[3] = yc-2;
			x[4] = xc+1; //+0
			y[4] = yc+4;
			x[5] = xc-1;
			y[5] = yc+4;
			x[6] = xc-1;
			y[6] = yc-2;
			x[7] = xc-2;
			y[7] = yc-2;
			
			//Scale
			for(i = 0; i<8; i++){
				x[i] = x[i]*size + (xc - xc*size);
				y[i] = y[i]*size + (yc - yc*size);
			}
			
			//Draw
			drawLine(x[0], y[0], x[1], y[1], r, g, b);
			drawLine(x[1], y[1], x[2], y[2], r, g, b);
			drawLine(x[2], y[2], x[3], y[3], r, g, b);
			drawLine(x[3], y[3], x[4], y[4], r, g, b);
			drawLine(x[4], y[4], x[5], y[5], r, g, b);
			drawLine(x[5], y[5], x[6], y[6], r, g, b);
			drawLine(x[6], y[6], x[7], y[7], r, g, b);
			drawLine(x[7], y[7], x[0], y[0], r, g, b);
			
			if(fill == 1){
				fillArea(xc, yc, r, g, b);
			}
			break;
		}
		case 'U':
		{
			//Init
			int x[8];
			int y[8];
			
			x[0] = xc-2;
			y[0] = yc-4;
			x[1] = xc-2;
			y[1] = yc+4;
			x[2] = xc+2;
			y[2] = yc+4;
			x[3] = xc+2;
			y[3] = yc-4;
			x[4] = xc+1;
			y[4] = yc-4;
			x[5] = xc+1;
			y[5] = yc+3;
			x[6] = xc-1;
			y[6] = yc+3;
			x[7] = xc-1;
			y[7] = yc-4;
			
			//Scale
			for(i = 0; i<8; i++){
				x[i] = x[i]*size + (xc - xc*size);
				y[i] = y[i]*size + (yc - yc*size);
			}
			
			//Draw
			drawLine(x[0], y[0], x[1], y[1], r, g, b);
			drawLine(x[1], y[1], x[2], y[2], r, g, b);
			drawLine(x[2], y[2], x[3], y[3], r, g, b);
			drawLine(x[3], y[3], x[4], y[4], r, g, b);
			drawLine(x[4], y[4], x[5], y[5], r, g, b);
			drawLine(x[5], y[5], x[6], y[6], r, g, b);
			drawLine(x[6], y[6], x[7], y[7], r, g, b);
			drawLine(x[7], y[7], x[0], y[0], r, g, b);
			
			if(fill == 1){
				fillArea(xc-2*size+1, yc, r, g, b);
			}
			break;
		}
		case 'V':
		{
			//Init
			int x[7];
			int y[7];
			
			x[0] = xc-2;
			y[0] = yc-4;
			x[1] = xc-1;
			y[1] = yc+4;
			x[2] = xc+1;
			y[2] = yc+4;
			x[3] = xc+2;
			y[3] = yc-4;
			x[4] = xc+1;
			y[4] = yc-4;
			x[5] = xc;
			y[5] = yc+3;
			x[6] = xc-1;
			y[6] = yc-4;
			
			//Scale
			for(i = 0; i<7; i++){
				x[i] = x[i]*size + (xc - xc*size);
				y[i] = y[i]*size + (yc - yc*size);
			}
			
			//Draw
			drawLine(x[0], y[0], x[1], y[1], r, g, b);
			drawLine(x[1], y[1], x[2], y[2], r, g, b);
			drawLine(x[2], y[2], x[3], y[3], r, g, b);
			drawLine(x[3], y[3], x[4], y[4], r, g, b);
			drawLine(x[4], y[4], x[5], y[5], r, g, b);
			drawLine(x[5], y[5], x[6], y[6], r, g, b);
			drawLine(x[6], y[6], x[0], y[0], r, g, b);
			
			if(fill == 1){
				fillArea(xc, yc+4*size-1, r, g, b);
			}
			break;
		}
		case 'W':
		{
			//Init
			int x[10];
			int y[10];
			
			x[0] = xc+2;
			y[0] = yc-4;
			x[1] = xc+2;
			y[1] = yc+4;
			x[2] = xc;
			y[2] = yc+1;
			x[3] = xc-2;
			y[3] = yc+4;
			x[4] = xc-2;
			y[4] = yc-4;
			x[5] = xc-1;
			y[5] = yc-4;
			x[6] = xc-1;
			y[6] = yc+1;
			x[7] = xc;
			y[7] = yc-1;
			x[8] = xc+1;
			y[8] = yc+1;
			x[9] = xc+1;
			y[9] = yc-4;
		
			//Scale
			for(i = 0; i<10; i++){
				x[i] = x[i]*size + (xc - xc*size);
				y[i] = y[i]*size + (yc - yc*size);
			}
			
			//Draw
			drawLine(x[0], y[0], x[1], y[1], r, g, b);
			drawLine(x[1], y[1], x[2], y[2], r, g, b);
			drawLine(x[2], y[2], x[3], y[3], r, g, b);
			drawLine(x[3], y[3], x[4], y[4], r, g, b);
			drawLine(x[4], y[4], x[5], y[5], r, g, b);
			drawLine(x[5], y[5], x[6], y[6], r, g, b);
			drawLine(x[6], y[6], x[7], y[7], r, g, b);
			drawLine(x[7], y[7], x[8], y[8], r, g, b);
			drawLine(x[8], y[8], x[9], y[9], r, g, b);
			drawLine(x[9], y[9], x[0], y[0], r, g, b);
			
			if(fill == 1){
				fillArea(xc, yc+1, r, g, b);
				fillArea(xc+2*size-1, yc, r, g, b);
				fillArea(xc-2*size+1, yc, r, g, b);
			}
			break;
		}
		case 'X':
		{
			//Init
			int x[12];
			int y[12];
			
			x[0] = xc-1;
			y[0] = yc-4;
			x[1] = xc;
			y[1] = yc-1;
			x[2] = xc+1;
			y[2] = yc-4;
			x[3] = xc+2;
			y[3] = yc-4;
			x[4] = xc+1;
			y[4] = yc;
			x[5] = xc+2;
			y[5] = yc+4;
			x[6] = xc+1;
			y[6] = yc+4;
			x[7] = xc;
			y[7] = yc+1;
			x[8] = xc-1;
			y[8] = yc+4;
			x[9] = xc-2;
			y[9] = yc+4;
			x[10] = xc-1;
			y[10] = yc;
			x[11] = xc-2;
			y[11] = yc-4;
		
			//Scale
			for(i = 0; i<12; i++){
				x[i] = x[i]*size + (xc - xc*size);
				y[i] = y[i]*size + (yc - yc*size);
			}
			
			//Draw
			drawLine(x[0], y[0], x[1], y[1], r, g, b);
			drawLine(x[1], y[1], x[2], y[2], r, g, b);
			drawLine(x[2], y[2], x[3], y[3], r, g, b);
			drawLine(x[3], y[3], x[4], y[4], r, g, b);
			drawLine(x[4], y[4], x[5], y[5], r, g, b);
			drawLine(x[5], y[5], x[6], y[6], r, g, b);
			drawLine(x[6], y[6], x[7], y[7], r, g, b);
			drawLine(x[7], y[7], x[8], y[8], r, g, b);
			drawLine(x[8], y[8], x[9], y[9], r, g, b);
			drawLine(x[9], y[9], x[10], y[10], r, g, b);
			drawLine(x[10], y[10], x[11], y[11], r, g, b);
			drawLine(x[11], y[11], x[0], y[0], r, g, b);
			
			if(fill == 1){
				fillArea(xc, yc, r, g, b);
			}
			break;
		}
		case 'Y':
		{
			//Init
			int x[12];
			int y[12];
			
			x[0] = xc-2;
			y[0] = yc-4;
			x[1] = xc-1;
			y[1] = yc-4;
			x[2] = xc-1;
			y[2] = yc-1;
			x[3] = xc+1;
			y[3] = yc-1;
			x[4] = xc+1;
			y[4] = yc-4;
			x[5] = xc+2;
			y[5] = yc-4;
			x[6] = xc+2;
			y[6] = yc;
			x[7] = xc+1;
			y[7] = yc;
			x[8] = xc+1;
			y[8] = yc+4;
			x[9] = xc-1;
			y[9] = yc+4;
			x[10] = xc-1;
			y[10] = yc;
			x[11] = xc-2;
			y[11] = yc;
		
			//Scale
			for(i = 0; i<12; i++){
				x[i] = x[i]*size + (xc - xc*size);
				y[i] = y[i]*size + (yc - yc*size);
			}
			
			//Draw
			drawLine(x[0], y[0], x[1], y[1], r, g, b);
			drawLine(x[1], y[1], x[2], y[2], r, g, b);
			drawLine(x[2], y[2], x[3], y[3], r, g, b);
			drawLine(x[3], y[3], x[4], y[4], r, g, b);
			drawLine(x[4], y[4], x[5], y[5], r, g, b);
			drawLine(x[5], y[5], x[6], y[6], r, g, b);
			drawLine(x[6], y[6], x[7], y[7], r, g, b);
			drawLine(x[7], y[7], x[8], y[8], r, g, b);
			drawLine(x[8], y[8], x[9], y[9], r, g, b);
			drawLine(x[9], y[9], x[10], y[10], r, g, b);
			drawLine(x[10], y[10], x[11], y[11], r, g, b);
			drawLine(x[11], y[11], x[0], y[0], r, g, b);
			
			if(fill == 1){
				fillArea(xc, yc, r, g, b);
			}
			break;
		}
		case 'Z':
		{
			//Init
			int x[10];
			int y[10];
			
			x[0] = xc-2;
			y[0] = yc-4;
			x[1] = xc+2;
			y[1] = yc-4;
			x[2] = xc+2;
			y[2] = yc-3;
			x[3] = xc-1;
			y[3] = yc+3;
			x[4] = xc+2;
			y[4] = yc+3;
			x[5] = xc+2;
			y[5] = yc+4;
			x[6] = xc-2;
			y[6] = yc+4;
			x[7] = xc-2;
			y[7] = yc+2;
			x[8] = xc+1;
			y[8] = yc-3;
			x[9] = xc-2;
			y[9] = yc-3;
		
			//Scale
			for(i = 0; i<10; i++){
				x[i] = x[i]*size + (xc - xc*size);
				y[i] = y[i]*size + (yc - yc*size);
			}
			
			//Draw
			drawLine(x[0], y[0], x[1], y[1], r, g, b);
			drawLine(x[1], y[1], x[2], y[2], r, g, b);
			drawLine(x[2], y[2], x[3], y[3], r, g, b);
			drawLine(x[3], y[3], x[4], y[4], r, g, b);
			drawLine(x[4], y[4], x[5], y[5], r, g, b);
			drawLine(x[5], y[5], x[6], y[6], r, g, b);
			drawLine(x[6], y[6], x[7], y[7], r, g, b);
			drawLine(x[7], y[7], x[8], y[8], r, g, b);
			drawLine(x[8], y[8], x[9], y[9], r, g, b);
			drawLine(x[9], y[9], x[0], y[0], r, g, b);
			
			if(fill == 1){
				fillArea(xc, yc-4*size+1, r, g, b);
				fillArea(xc, yc+4*size-1, r, g, b);
			}
			break;
		}
	}
}

/*
* TODO
*/
void DrawService::drawRectangle(int xc, int yc, int width, int heigth, unsigned char r, unsigned char g, unsigned char b, int degree, bool fill){
	drawRectangleCenter(xc+width/2, yc+heigth/2, width, heigth, r, g, b, degree, fill);
}

/*
* Draws a rectangle on the screen with cetern = (xc, yc), color rgb, and rotates CW degree, and optional filling
*/
void DrawService::drawRectangleCenter(int xc, int yc, int width, int heigth, unsigned char r, unsigned char g, unsigned char b, int degree, bool fill){
	//Init
	int x1, y1, x2, y2, x3, y3, x4, y4;
	int dx1, dy1, dx2, dy2, dx3, dy3, dx4, dy4;
	float radians;
	float sin_val, cos_val;
	
	//Calculate initial corners
	x1 = xc - width/2;
	y1 = yc - heigth/2;
	
	x2 = xc + width/2;
	y2 = yc - heigth/2;
	
	x3 = xc + width/2;
	y3 = yc + heigth/2;
	
	x4 = xc - width/2;
	y4 = yc + heigth/2;
	
	//Rotation
	radians = degree*PI/180.0f;
	cos_val = cosf(radians);
	sin_val = sinf(radians);
	dx1 = x1*cos_val - y1*sin_val + (-xc*cos_val + yc*sin_val + xc);
	dy1 = x1*sin_val + y1*cos_val + (-xc*sin_val - yc*cos_val + yc);
	
	dx2 = x2*cos_val - y2*sin_val + (-xc*cos_val + yc*sin_val + xc);
	dy2 = x2*sin_val + y2*cos_val + (-xc*sin_val - yc*cos_val + yc);
	
	dx3 = x3*cos_val - y3*sin_val + (-xc*cos_val + yc*sin_val + xc);
	dy3 = x3*sin_val + y3*cos_val + (-xc*sin_val - yc*cos_val + yc);
	
	dx4 = x4*cos_val - y4*sin_val + (-xc*cos_val + yc*sin_val + xc);
	dy4 = x4*sin_val + y4*cos_val + (-xc*sin_val - yc*cos_val + yc);
	
	//Draw lines
	drawLine(dx1, dy1, dx2, dy2, r, g, b);
	drawLine(dx2, dy2, dx3, dy3, r, g, b);
	drawLine(dx3, dy3, dx4, dy4, r, g, b);
	drawLine(dx4, dy4, dx1, dy1, r, g, b);
	
	//Fill
	if(fill == 1){
		fillArea(xc, yc, r, g, b);
	}
}

/*
* TODO
*/
void DrawService::drawCircle(int xc, int yc, int radius, unsigned char r, unsigned char g, unsigned char b, bool fill){
	drawCircleCenter(xc+radius/2, yc+radius/2, radius, r, g, b, fill);
}

/*
*	Draws a circle with center = (xc, yc), Color RGB, and an optional fill
*/
void DrawService::drawCircleCenter(int xc, int yc, int radius, unsigned char r, unsigned char g, unsigned char b, bool fill){
	//Init
	int x, y, e;
	x = 0;
	y = radius;
	e = -radius;
	
	//Draw
	while(x <= y){
		setPixel(xc + x, yc + y, r, g, b);
		setPixel(xc + y, yc + x, r, g, b);
		setPixel(xc + y, yc - x, r, g, b);
		setPixel(xc + x, yc - y, r, g, b);
		setPixel(xc - x, yc - y, r, g, b);
		setPixel(xc - y, yc - x, r, g, b);
		setPixel(xc - y, yc + x, r, g, b);
		setPixel(xc - x, yc + y, r, g, b);
		
		e = e + 2*x + 2;
		x = x + 1;
		if(e >= 0){
			e = e - 2*y + 2;
			y = y - 1;
		}
	}
	
	//Fill
	if(fill == 1){
		fillArea(xc, yc, r, g, b);
	}
}

/*
*	Draws a line from (xs, ys) -> (xe, ye) with a RGB color
*/
void DrawService::drawLine(int xs, int ys, int xe, int ye, unsigned char r, unsigned char g, unsigned char b){
	//Init
	int x, y, e, dx, dy, inc_x, inc_y;
	dx = xe - xs;
	dy = ye - ys;
	
	//Direction check
	if(xs >= xe && ys >= ye){
		//Up left
		dx = -dx;
		dy = -dy;
		inc_x = 1;
		inc_y = 1;
		int temp;
		temp = xs;
		xs = xe;
		xe = temp;
		temp = ys;
		ys = ye;
		ye = temp;
	}else if(xs <= xe && ys >= ye){
		//Up right
		dy = -dy;
		inc_x = 1;
		inc_y = -1;
	}else if(xs > xe && ys <= ye){
		//Down left
		dx = -dx;
		int temp;
		temp = xs;
		xs = xe;
		xe = temp;
		temp = ys;
		ys = ye;
		ye = temp;
		inc_x = 1;
		inc_y = -1;
	}else{
		//Down right
		inc_x = 1;
		inc_y = 1;
	}
	
	x = xs;
	y = ys;
	e = -(dx >> 1);
	
	//More than 45 degree slope
	if(dy != 0 && dx/dy < 1){
		if(dx != 0){		
			//Degree != 90
			while(x <= xe){		
				setPixel(x, y, r, g, b);
				y = y + inc_y;
				e = e + dx;
		
				if(e >= 0){
					x = x + inc_x;
					e = e - dy;
				}
			}
		}else{
			//Vertical line
			while(y <= ye){
				setPixel(x, y, r, g, b);
				y = y + inc_y;
			}
		}
	}else{
		while(x <= xe){		
			setPixel(x, y, r, g, b);
			x = x + inc_x;
			e = e + dy;
		
			if(e >= 0){
				y = y + inc_y;
				e = e - dx;
			}
		}
	}
}

/*
*	Sets a RGB color for a single pixel (x,y)
*/
void DrawService::setPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b){
	//Verify coordinates in screen
	assert(x < width && x >= 0);
	assert(y < height && y >= 0);
	
	//Set pixel
	pixels[y*width*3 + x*3 + 2] = r;
	pixels[y*width*3 + x*3 + 1] = g;
	pixels[y*width*3 + x*3 + 0] = b;
}

/*
*	Returns the RED part of the color in (x, y)
*/
inline unsigned char DrawService::getRed(int x, int y){
	return pixels[y*width*3 + x*3 + 2];
}


/*
*	Returns the GREEN part of the color in (x, y)
*/
inline unsigned char DrawService::getGreen(int x, int y){
	return pixels[y*width*3 + x*3 + 1];
}


/*
*	Returns the BLUE part of the color in (x, y)
*/
inline unsigned char DrawService::getBlue(int x, int y){
	return pixels[y*width*3 + x*3];
}
