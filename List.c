#include <stdlib.h>
#include <string.h>

#include "xmalloc.h"
#include "List.h"

List* __newList(const char *typeName, size_t typeSize)
{
    List* list;
    list = (List*)xmalloc(sizeof(List));

    list->__typeName = typeName;
    list->__typeSize = typeSize;
    list->__next = 0;
    list->__free = &List_free;

    list->value = xmalloc(typeSize);
    list->delete = &List_delete;
    list->push = &List_push;
    list->pop = &List_pop;
}

void List_free(List *list)
{
    xfree(list->value);
    xfree(list);
}

void List_delete(List **list)
{
    List *this = *list;
    if(this->__next != 0)
    {
        this->delete(&this->__next);
        this->__next = 0;
    }
    
    List_free(this);
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
    List_free(this);
    prev->__next = 0;
}
