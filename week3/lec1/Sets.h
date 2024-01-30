typedef struct set *Set;
typedef int Item;

Set SetNew(void);

void SetInsert(Set s, Item value);

void SetDelete(Set s);

void SetShow(Set s);

void SetFree(Set s);