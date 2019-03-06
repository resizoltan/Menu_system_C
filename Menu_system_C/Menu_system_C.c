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
    char* name_;
	onSelectCallback_t onSelectCallback_;// = NULL;
	itemPtrArr_t *items_;// = NULL;
	itemIterator_t item_iterator_;// = NULL;
	itemIterator_t last_item_;// = NULL;
	int itemCount;
}item_t;

typedef struct item_definition {
	char *name;
	onSelectCallback_t onSelectCallback_;
};

typedef struct menu {
	itemPtrArr_t *all_items_;// = NULL;
	itemPtr_t curr_item_;// = NULL;
}menu_t;

char item_names[][20] = { "root", "sub1", "sub2" };

#define newItem(name)				\
{									\
	.name = name;					\
	.onSelectCallback_ = NULL;		\
	.items_ = NULL;					\
	.item_iterator_ = NULL;			\
	.last_item_ = NULL;				\
	.itemCount = 0;					\
}

#define declareItems(menu_name, ...)					\
itemPtr_t menu_name##_all_items = {__VA_ARGS__}

/*----Macro for creating menu items----*/
/*		name: name of item
		onSelectCallback: callback function to execute when this item is selected
		item_count: number of items contained in this item (min: 1 (parent item))
		...: items to be contained by this item (min: 1 (parent item))
*/
#define m_defineSubmenu(name, onSelectCallback, item_count, ...)	\
itemPtr_t name_##subitems[] = { __VA_ARGS__ };						\
onSelectCallback_t name_##onSelectCallback = onSelectCallback;		\
int name_##item_count = item_count;									\
			


#define m_declareMenu(name, init_item)				\
menu_t name_##menu = {									\
	.all_items_ = &name_##all_items;					\
	.curr_item_ = init_item;							\
};

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
		it = &(*(curr_item->items_)[0]);
	}
	curr_item->item_iterator_ = it;
	printf("Looking at: ");
	printf((*it)->name_);
	printf("\n");
	return;
}

void enterTopic(menu_t *menu) {
	menu->curr_item_ = *(menu->curr_item_->item_iterator_);
	printf("Entered ");
	printf(menu->curr_item_->name_);
	printf("\nLooking at: ");
	printf((*menu->curr_item_->item_iterator_)->name_);
	printf("\n");

	return;
}



/*---------------------------------------------- My Menu ---------------------------------------------*/


















char rootname[] = "root"; 
#define rootItemCount 3
char sub1name[] = "sub1";
#define sub1ItemCount 1
char sub2name[] = "sub2";
#define sub2ItemCount 1

item_t root = { .name_ = rootname,.onSelectCallback_ = enterTopic,.items_ = NULL,.item_iterator_ = NULL,.last_item_ = NULL , .itemCount = rootItemCount};
item_t submenu1 = { .name_ = sub1name,.onSelectCallback_ = enterTopic,.items_ = NULL,.item_iterator_ = NULL,.last_item_ = NULL ,.itemCount = sub1ItemCount };
item_t submenu2 = { .name_ = sub2name,.onSelectCallback_ = enterTopic,.items_ = NULL,.item_iterator_ = NULL,.last_item_ = NULL ,.itemCount = sub2ItemCount };

itemPtr_t root_subitems[] = {&root, &submenu1, &submenu2};
itemPtrArr_t root_subitems_ptr = root_subitems;
itemPtr_t sub1_subitems[] = {&root};
itemPtrArr_t sub1_subitems_ptr = sub1_subitems;
itemPtr_t sub2_subitems[] = {&root};
itemPtrArr_t sub2_subitems_ptr = sub2_subitems;

int itemCount = 3;
itemPtr_t main_menu_allitems[] = {&root, &submenu1, &submenu2};
itemPtrArr_t main_menu_allitems_ptr = main_menu_allitems;
itemPtrArr_t *subitems[] = {&root_subitems_ptr, &sub1_subitems_ptr, &sub2_subitems_ptr };

menu_t main_menu = {.all_items_= &main_menu_allitems_ptr, .curr_item_ = &root};

void linkMenu(menu_t* menu){
    for(int itemIndex = 0; itemIndex < itemCount; itemIndex++){
		item_t *item = (*menu->all_items_)[itemIndex];
        item->items_=subitems[itemIndex];
		item->item_iterator_ = &(*subitems[itemIndex])[0];
		item->last_item_ = &(*subitems[itemIndex])[item->itemCount - 1];
    }
}

int main()
{
    linkMenu(&main_menu);


	printf("Main menu\n");
	do {
		char c = getchar();
		if (c == 's') {
			select(&main_menu);
		}
		else if (c == 'n') {
			next(&main_menu);
		}
		else if (c == 'q') {
			break;
		}
	} while (1);

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
