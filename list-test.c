#include <stdio.h>

#include "List.h"

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
