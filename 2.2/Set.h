#ifndef SET_H
#define SET_H
#define MAX_NUM 99

typedef struct SetRep* Set;

Set SetCreate();
void SetInsert(Set, int );
void SetDelete(Set, int);
int SetMember(Set, int);
Set SetUnion(Set, Set);
Set SetIntersect(Set, Set);
void SetDestroy(Set);

Set SetCopy(Set);
void SetShow(Set);

int binary_search(Set s, int left, int right, int looking);
void Set_insert_special(Set s, int critical_index, int n);
int index_finding(Set s, int left, int right, int looking);
void SetDeletion(Set s, int n);


int Member_Search(Set s, int n);
#endif 

