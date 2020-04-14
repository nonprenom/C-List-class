#include <stdlib.h>
#include <string.h>

#include "List.h"

List* newList()
{
    List* list;
    list = (List*)malloc(sizeof(List));

    list->_next = 0;
    list->value = 0;
    list->delete = &List_delete;
    list->_push = &List_push;
    list->_pop = &List_pop;
    list->pushInt = &List_pushInt;
    list->popInt = &List_popInt;
}

void List_delete(List **list)
{
    List *this = *list;
    if(this->_next != 0)
    {
        this->delete(&this->_next);
        this->_next = 0;
    }
    
    free(this);
    *list = 0;
}

void List_push(List *this, void *value)
{
    List *list = this;
    while(list->_next != 0)
    {
        list = list->_next;
    };
    
    list->_next = newList();
    list->_next->value = value;
}

void* List_pop(List *list)
{
    List *this = list;
    List *prev = list;
    void *ret;

    while(this->_next != 0)
    {
        prev = this;
        this = this->_next;
    };

    ret = this->value;
    free(this);
    prev->_next = 0;
    
    return ret;
}

void List_pushInt(List *this, int value)
{
    int *intValue = (int*)malloc(sizeof(int));
    memcpy(intValue, &value, sizeof(int));
    this->_push(this, intValue);
}

int List_popInt(List *this)
{
    int *value;
    value = this->_pop(this);

    int intValue = 0;
    memcpy(&intValue, value, sizeof(int));

    free(value);
    return intValue;
}



