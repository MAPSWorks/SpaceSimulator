#ifndef LIST_LAYOUT_H
#define LIST_LAYOUT_H

#include "../include/DrawService.hpp"
#include "../include/View.hpp"
#include <vector>

class ListLayout: public View{
	private:
		View *parent;
		std::vector<View*> *children;
		
	public:
		/**
		* Creates an empty list layout object
		**/
		ListLayout(int x, int y, int width, int height);
		
		/**
		* Finalizes this ListLayout object
		**/
		~ListLayout();
		
		/**
		* Adds a child view to this layout
		**/
		void addChild(View *view);
		
		/**
		* Executed when the view should be drawn
		**/
		void draw(DrawService *draw);
};

#endif
