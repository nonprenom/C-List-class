#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#include "xmalloc.h"
#include "List.h"

List *__newList(const char *typeName, size_t typeSize)
{
    List *list = 0;
    list = (List *)xmalloc(sizeof(List));
    if (list != 0)
    {
        list->__typeName = typeName;
        list->__typeSize = typeSize;
        list->__next = 0;
        list->__free = &List_free;

        list->value = xmalloc(typeSize);
        if (list->value != 0)
        {
            list->delete = &List_delete;
            list->push = &List_push;
            list->pop = &List_pop;
        }
        else
            perror("__newList() : Unable to allocate the value field.");
    }
    else
        perror("__newList() : Unable to allocate a new List.");

    return list;
}

void List_free(List *list)
{
    xfree(list->value);
    xfree(list);
}

void List_delete(List **list)
{
    List *this = *list;
    if (this->__next != 0)
        this->delete (&this->__next);

    List_free(this);
    *list = 0;
}

int List_push(List *this, void *value)
{
    List *list = this;
    while (list->__next != 0)
    {
        list = list->__next;
    };

    list->__next = __newList(list->__typeName, list->__typeSize);
    if (list->__next != 0)
        memcpy(list->__next->value, value, list->__typeSize);
    else
    {
        fprintf(stderr, "List_push() : Unable to create the next List.\n");
        return -1;
    }

    return 0;
}

int List_pop(List *list, void *value)
{
    List *this = list;
    List *prev = list;
    void *ret;

    while (this->__next != 0)
    {
        prev = this;
        this = this->__next;
    };

    if (this != list)
    {
        memcpy(value, this->value, list->__typeSize);
        List_free(this);
        prev->__next = 0;
    }
    else
    {
        fprintf(stderr, "List_pop() : The List is empty\n");
        return -1;
    }

    return 0;
}
