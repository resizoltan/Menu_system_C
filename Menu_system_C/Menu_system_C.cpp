// Menu_system_C.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <stdio.h>
//#include <stdarg.h>


/*==============================================================================================================*/
/*                                                Mouse Menu                                                    */
/*==============================================================================================================*/
typedef struct item item_t;
typedef item_t* itemPtr_t;
typedef itemPtr_t* itemIterator_t;
typedef itemPtr_t* itemPtrArr_t;
typedef struct menu menu_t;
typedef void(*onSelectCallback_t)(menu_t*);


typedef struct item {
	onSelectCallback_t onSelectCallback_;// = NULL;
	itemPtrArr_t *items_;// = NULL;
	itemIterator_t item_iterator_;// = NULL;
	itemIterator_t last_item_;// = NULL;
}item_t;

typedef struct menu {
	itemPtrArr_t *allItems_;// = NULL;
	itemPtr_t curr_item_;// = NULL;
}menu_t;

/*----Macro for creating menu items----*/
/*		name: name of item
		onSelectCallback: callback function to execute when this item is selected
		item_count: number of items contained in this item (min: 1 (parent item))
		...: items to be contained by this item (min: 1 (parent item))
*/
#define m_defineItem(name, onSelectCallback, item_count, ...)	\
item_t *name_##subitems[] = {__VA_ARGS__};			\
item_t name{									\
	.onSelectCallback_ = onSelectCallback,			\
	.items_ = name_##subitems,						\
	.item_iterator_ = name_##subitems[0],						\
	.last_item_ = name_##subitems[item_count - 1]			\
};

#define m_declareMenu(name, init_item, ...)			\
item_t *name_##all_items[] = {__VA_ARGS__};			\
typedef struct{										\
	all_items_ = name_##all_items;					\
	curr_item_ = init_item;							\
}name##Menu;

void select(menu_t* menu) {
	itemIterator_t it = menu->curr_item_->item_iterator_;
	(*it)->onSelectCallback_(menu);
	return;
}

void next(menu_t *menu) {
	itemPtr_t curr_item = menu->curr_item_;
	itemIterator_t it = curr_item->item_iterator_;
	if (it != curr_item->last_item_) {
		it++;
	}
	else {
		it = &(curr_item->items_[0]);
	}
	return;
}

void enterTopic(menu_t *menu) {
	menu->curr_item_ = *(menu->curr_item_->item_iterator_);
	return;
}

/*---------------------------------------------- My Menu ---------------------------------------------*/
item_t root = { .onSelectCallback_ = enterTopic,.items_ = NULL,.item_iterator_ = NULL,.last_item_ = NULL };
item_t submenu1 = { .onSelectCallback_ = enterTopic,.items_ = NULL,.item_iterator_ = NULL,.last_item_ = NULL };
item_t submenu2 = { .onSelectCallback_ = enterTopic,.items_ = NULL,.item_iterator_ = NULL,.last_item_ = NULL };

//#define itemCount 3
itemPtrArr_t root_subitems[] = {&root, &submenu1, &submenu2};

//item_t topic1_subitems[] = { &root };
//
//item_t root = { enterTopic, &root_subitems, &root_subitems[0], &root_subitems[count - 1] };
//
//item_t topic1;
//item_t topic2;


//root->onSelectCallback_ = enterTopic;
// {
//	.onSelectCallback_ = enterTopic,
//	.items_ = root_subitems,
//	.item_iterator_ = &(root_subitems[0]),
//
//};



//m_defineItem(root, enterTopic, 3, &topic1, &topic2, &root);

int var1Ptr[1];// = { 5 };
int var2Ptr[1];
int var3Ptr[1];

int itemek[] = { 5 };
int *items[] = { var1Ptr, var2Ptr, var3Ptr };

int main()
{
	*var1Ptr = 1;
	*var2Ptr = 2;
	*var3Ptr = 3;

	for (int i = 0; i < 3; i++) {
		printf("%i\n", *(items[i]));
	}


	printf("item_t size %i\n", sizeof(item_t));
	printf("item_t* size %i\n", sizeof(item_t*));

	printf("Main menu\n");

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
