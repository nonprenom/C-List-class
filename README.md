# List class in C !

Hi! It's a small project for fun to try to implement a class in C. 
I took the a one way linked list class as challenge.
The list store copies of the items (not references).

## How to use it
After you included List.h, you can:

 - create a new list of any type,
 - add new items into the front of the list with list->push(...)
 - get the last item with list->pop(...)
 - delete the list with delete()
## Example

    #include "List.h"
    
    // define a new "complex" structure
    typedef struct myStruct
    {
        int int_field;
        double double_field;
        char *pChar_field;
        char string_field[128];
    } myStruct_t;

    // Create the list
    List *list = newList(myStruct_t);

	// push a new item in the list
    myStruct_t value;
    value.int_field = 1111;
    value.double_field = 35.98;
    value.pChar_field = "pChar_field 1";
    strcpy(value.string_field, "string_field 1");
    list->push(list, &value);

	// Get the last item
	myStruct_t value2 = {0};
    list->pop(list, &value2);
    printf("value : int_field = %d, double_field = %f, pChar_field = %s, string_field = %s\n",
        value2.int_field, value2.double_field, value2.pChar_field, value2.string_field);
    
    // Delete the list
    list->delete(&list);

## How to build
Build the project with "make"
