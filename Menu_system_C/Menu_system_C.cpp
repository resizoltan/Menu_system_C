// Menu_system_C.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <stdio.h>
//#include <stdarg.h>


/*==============================================================================================================*/
/*                                                Mouse Menu                                                    */
/*==============================================================================================================*/
typedef struct item item_t;
typedef struct menu menu_t;
typedef void(*onSelectCallback_t)(menu_t*);


typedef struct item {
	onSelectCallback_t onSelectCallback_ = NULL;
	item_t *items_ = NULL;
	int item_count_ = 0;
	int item_iterator_ = 0;
}item_t;

typedef struct menu {
	item_t *allItems_ = NULL;
	item_t *cur_item_ = NULL;
};

//typedef struct menu menu_t;
#define m_declareItem(name, onSelectCallback, item_count, ...)	\
item_t *name_##subitems[] = {__VA_ARGS__};			\
item_t name##Item{									\
	onSelectCallback_ = onSelectCallback;			\
	items_ = name_##subitems;						\
	item_count_ = item_count;						\
	active_item_ = 0;								\
};

#define m_declareMenu(name, init_item, ...)			\
item_t *name_##all_items[] = {__VA_ARGS__};			\
typedef struct{										\
	all_items_ = name_##all_items;					\
	cur_item_ = init_item;							\
}name##Menu;

void select(menu_t* menu) {
	menu->cur_item_->onSelectCallback_(menu);
}

/*---------------------------------------------- Main Menu ---------------------------------------------*/

//void dummy1(void);
//void dummy2(void);
//void dummy3(void);
//
//void (*dummyFcnPtr[])(void) = { dummy1, dummy2, dummy3};



int main()
{
	printf("Main menu");

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
