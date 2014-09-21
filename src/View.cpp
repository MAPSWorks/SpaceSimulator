#include "../include/View.hpp"
#include <iostream>

View::View(int x, int y, int width, int height){
	// Debug
	//std::cout << "View.cpp\t\t\tInitializing" << std::endl;
	
	// Init
	this->red = 255;
	this->green = 255;
	this->blue = 255;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->clickActions = new std::vector<ViewClickedAction*>();
}

View::~View(){
	// Debug
	//std::cout << "View.cpp\t\t\tFinalizing" << std::endl;
	
	// Free
	delete clickActions;
}

void View::addViewClickedAction(ViewClickedAction *action){
	clickActions->push_back(action);
}

void View::draw(DrawService *service){
	service->drawLine(x, y, x+width, y, red, green, blue);
	service->drawLine(x, y, x, y+height, red, green, blue);
	service->drawLine(x, y+height, x+width, y+height, red, green, blue);
	service->drawLine(x+width, y, x+width, y+height, red, green, blue);
}

bool View::isInside(int x, int y){

}

void View::clicked(int button, int action){
	// Fire off listeners
	std::cout << "Clicked " << this << std::endl;
}
