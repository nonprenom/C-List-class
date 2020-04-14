#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct List_s
{
    void *value;

    struct List_s *_next;
    void (*delete)(struct List_s **);
    void (*_push)(struct List_s *, void*);
    void* (*_pop)(struct List_s *);

    void (*pushInt)(struct List_s *, int);
    int (*popInt)(struct List_s *);
} List;

void List_delete(List **this);
void List_push(List *this, void *value);
void* List_pop(List *this);
void List_pushInt(List *this, int value);
int List_popInt(List *this);

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

int main(int argc, char **argv)
{
    List* list = newList();

    list->pushInt(list, 12);
    list->pushInt(list, 8);
    list->pushInt(list, 255);

    printf("%d\n", list->popInt(list));
    printf("%d\n", list->popInt(list));
    printf("%d\n", list->popInt(list));

    list->delete(&list);

    return 0;
}

