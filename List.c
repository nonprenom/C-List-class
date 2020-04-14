#include <stdlib.h>
#include <string.h>

#include "List.h"

List* __newList(const char *typeName, size_t typeSize)
{
    List* list;
    list = (List*)malloc(sizeof(List));

    list->__typeName = (char*)malloc(sizeof(char)*strlen(typeName));
    strcpy(list->__typeName, typeName);
    list->__typeSize = typeSize;

    list->__next = 0;
    list->value = 0;
    list->delete = &List_delete;
    list->push = &List_push;
    list->pop = &List_pop;
}

void List_delete(List **list)
{
    List *this = *list;
    if(this->__next != 0)
    {
        this->delete(&this->__next);
        this->__next = 0;
    }
    
    free(this->__typeName);
    free(this);
    *list = 0;
}

void List_push(List *this, void *value)
{
    List *list = this;
    while(list->__next != 0)
    {
        list = list->__next;
    };
    
    list->__next = __newList(list->__typeName, list->__typeSize);
    list->__next->value = malloc(list->__typeSize);
    memcpy(list->__next->value, value, list->__typeSize);
}

void List_pop(List *list, void *value)
{
    List *this = list;
    List *prev = list;
    void *ret;

    while(this->__next != 0)
    {
        prev = this;
        this = this->__next;
    };

    memcpy(value, this->value, list->__typeSize);
    free(this->value);
    free(this);
    prev->__next = 0;
}
