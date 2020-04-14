#ifndef LIST_H
#define LIST_H

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

List* newList();
void List_delete(List **this);
void List_push(List *this, void *value);
void* List_pop(List *this);
void List_pushInt(List *this, int value);
int List_popInt(List *this);

#endif // LIST_H
