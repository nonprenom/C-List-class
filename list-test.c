#include <stdio.h>
#include <string.h>

#include "xmalloc.h"
#include "List.h"

static void test_int_list()
{
    printf("---- start %s ----\n", __func__);
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
    printf("---- end %s ----\n", __func__);
}

static void test_myStruct_list()
{
    typedef struct myStruct
    {
        int int_field;
        double double_field;
        char *pChar_field;
        char string_field[128];
    } myStruct_t;

    List *list = newList(myStruct_t);

    myStruct_t value;
    value.int_field = 1111;
    value.double_field = 35.98;
    value.pChar_field = "pChar_field 1";
    strcpy(value.string_field, "string_field 1");

    list->push(list, &value);

    value.int_field = 2222;
    value.double_field = 275.12;
    value.pChar_field = "pChar_field 2";
    strcpy(value.string_field, "string_field 2");

    list->push(list, &value);

    value.int_field = 33333;
    value.double_field = 44.0125;
    value.pChar_field = "pChar_field 3";
    strcpy(value.string_field, "string_field 3");

    list->push(list, &value);

    value.int_field = 444444;
    value.double_field = 34321.9674;
    value.pChar_field = "pChar_field 4";
    strcpy(value.string_field, "string_field 4");

    list->push(list, &value);

    xmalloc_status();

    memset(&value, 0, sizeof(value));

    list->pop(list, &value);
    printf("value : int_field = %d, double_field = %f, pChar_field = %s, string_field = %s\n",
        value.int_field, value.double_field, value.pChar_field, value.string_field);

    list->pop(list, &value);
    printf("value : int_field = %d, double_field = %f, pChar_field = %s, string_field = %s\n",
        value.int_field, value.double_field, value.pChar_field, value.string_field);

    list->pop(list, &value);
    printf("value : int_field = %d, double_field = %f, pChar_field = %s, string_field = %s\n",
        value.int_field, value.double_field, value.pChar_field, value.string_field);

    list->delete(&list);

    xmalloc_status();

    printf("---- end %s ----\n", __func__);
}

int main(int argc, char **argv)
{
    test_int_list();
    test_myStruct_list();

    return 0;
}
