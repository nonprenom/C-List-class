#include <stdio.h>

#include "xmalloc.h"
#include "List.h"

int main(int argc, char **argv)
{
    List *list = newList(int);
    int value = 0;

    value = 12;
    list->push(list, &value);
    value = 8;
    list->push(list, &value);
    value = 89898;
    list->push(list, &value);

    //xmalloc_status();

    list->pop(list, &value);
    printf("%d\n", value);
    list->pop(list, &value);
    printf("%d\n", value);
    list->pop(list, &value);
    printf("%d\n", value);

    if(list->pop(list, &value) == 0)
        printf("%d\n", value);
    else
        printf("error with pop()\n");

    //xmalloc_status();

    list->delete (&list);

    xmalloc_status();

    return 0;
}
