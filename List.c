#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "xmalloc.h"
#include "List.h"

List *__newList(const char *typeName, size_t typeSize)
{
    List *list = 0;
    list = (List *)xmalloc(sizeof(List));
    if (list != 0)
    {
        list->_priv.typeName = typeName;
        list->_priv.typeSize = typeSize;
        list->_priv.next = 0;

        list->value = xmalloc(typeSize);
        if (list->value == 0)
            perror("__newList() : Unable to allocate the value field.");

        list->delete = &List_delete;
        list->push = &List_push;
        list->pop = &List_pop;
    }
    else
        perror("__newList() : Unable to allocate a new List.");

    return list;
}

static void List_free(List *list)
{
    xfree(list->value);
    xfree(list);
}

void List_delete(List **list)
{
    List *this = *list;
    if (this->_priv.next != 0)
        this->delete (&this->_priv.next);

    List_free(this);
    *list = 0;
}

int List_push(List *this, void *value)
{
    List *list = this;
    while (list->_priv.next != 0)
    {
        list = list->_priv.next;
    };

    list->_priv.next = __newList(list->_priv.typeName, list->_priv.typeSize);
    if (list->_priv.next != 0)
        memcpy(list->_priv.next->value, value, list->_priv.typeSize);
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

    while (this->_priv.next != 0)
    {
        prev = this;
        this = this->_priv.next;
    };

    if (this != list)
    {
        memcpy(value, this->value, list->_priv.typeSize);
        List_free(this);
        prev->_priv.next = 0;
    }
    else
    {
        fprintf(stderr, "List_pop() : The List is empty\n");
        return -1;
    }

    return 0;
}
