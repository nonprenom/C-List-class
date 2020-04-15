#ifndef LIST_H
#define LIST_H

/**
 * @brief C Class List :
 *  create with newList()
 *  push a new item with push()
 *  pop with pop()
 *  don't forget to delete with delete()
 */
typedef struct List_s
{
    const char *__typeName;
    size_t __typeSize;
    struct List_s *__next;
    void (*__free)(struct List_s *);

    void *value;

    void (*delete)(struct List_s **);
    int (*push)(struct List_s *, void *);
    int (*pop)(struct List_s *, void *);
} List;

List *__newList(const char *typeName, size_t typeSize);

/**
 * @brief Create a new List object of item of type TYPE
 *  TYPE : the type of the item (int, double, myStruct, etc..)
 * 
 */
#define newList(TYPE) __newList(#TYPE, sizeof(TYPE))

/**
 * @brief Free the memory for one item of the list
 * 
 * @param list : pointer to one item of the list
 */
void List_free(List *list);

/**
 * @brief Free the memory and delete the List
 * 
 * @param this : a pointer to the pointer of the list
 */
void List_delete(List **this);

/**
 * @brief add a new item to the front of the list
 *
 * @param this : a pointer to the List
 * @param value : a pointer to the item
 * @return int : 0 if OK, -1 if error
 */
int List_push(List *this, void *value);

/**
 * @brief return the last item added to the list
 * 
 * @param this : a pointer ot the List
 * @param value : a pointer to the item - needs to be allocated with the correct size.
 * @return int : 0 if OK, -1 if error
 */

int List_pop(List *this, void *value);

#endif // LIST_H
