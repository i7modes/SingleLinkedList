#include <stdio.h>
#include <stdlib.h>

struct node {

       int Data;
       struct node* Next;
};
struct node* MakeEmpty(struct node*);
int IsEmpty(struct node*);
int IsLast(struct node*, struct node*);
struct node* Find(int, struct node*);
struct node* FindPrevious(int, struct node*);
void Delete(int, struct node*);
void Insert(int, struct node*, struct node*);
void InsetLast(int, struct node*);
void PrintList(struct node*);
void DeleteList(struct node*);
int size( struct node*);

int main(){
    struct node* myList = MakeEmpty(NULL);

    printf("%d\n", IsEmpty(myList));

    Insert(10, myList, myList);
    Insert(20, myList, myList->Next);
    Insert(30, myList, myList->Next->Next);
    InsertLast(40, myList);
    PrintList(myList);

    printf("%d\n", size(myList));

    printf("%d\n", IsEmpty(myList));

    printf("%d\n", IsLast(myList->Next->Next->Next->Next, myList));

    printf("%d\n", Find(30, myList)->Data);

    printf("%d\n", FindPrevious(30, myList)->Data);

    Delete(20, myList);
    PrintList(myList);

    printf("%d\n", size(myList));

    struct node* List = MakeEmpty(myList);
    PrintList(List);

    printf("\nDone!\n");
    return 0;
}

struct node* MakeEmpty(struct node* L){
    if(L != NULL)
        DeleteList(L);

    L = (struct node*)malloc(sizeof(struct node));

   if(L == NULL)
    printf("Out of memory!\n");

   L->Next = NULL;
   return L;
}

int IsEmpty(struct node* L) {
    return L->Next == NULL;
}

int IsLast(struct node* P, struct node* L) {
    return P->Next == NULL;
}

struct node* Find(int X, struct node* L){
    struct node* P;
    P = L->Next;

    while(P != NULL && P->Data != X)
         P = P->Next;

    return P;
}

struct node* FindPrevious(int X, struct node* L){
     struct node* P;
     P = L;

     while(P->Next != NULL && P->Next->Data != X)
          P = P->Next;

     return P;
}

void Delete(int X, struct node* L){
     struct node* P;
     struct node*temp;

     P = FindPrevious(X, L);

     if(!IsLast(P, L) ){
         temp = P->Next;
         P->Next = temp->Next;
         free(temp);
     }
}

void Insert(int X, struct node* L, struct node* P) {
    struct node* temp;
    temp = (struct node*)malloc(sizeof(struct node));

    if (temp == NULL) {
        printf("Out of memory!\n");
        exit(1);
    }

    temp->Data = X;
    temp->Next = P->Next;
    P->Next = temp;
}

void InsertLast(int X, struct node* L) {
    struct node* temp;
    struct node* P = L;
    temp = (struct node*)malloc(sizeof(struct node));

    if (temp == NULL) {
        printf("Out of memory!\n");
        exit(1);
    }

    temp->Data = X;
    temp->Next = NULL;

    while(P->Next != NULL){
        P = P->Next;
    }

    P->Next = temp;
}

void PrintList(struct node* L){
    struct node* P = L;

    if( IsEmpty(L)){
      printf("Empty list\n");

    } else {

       do{
           P=P->Next;
           printf("%d\t", P->Data);

       }while( !IsLast(P, L) );

    printf("\n");

    }
}

void DeleteList(struct node* L){
     struct node* P;
     struct node* temp;

     P = L->Next;
     L->Next = NULL;

     while(P != NULL){
         temp = P->Next;
         free(P);
         P=temp;
     }
}

int size( struct node* L){
     struct node* P = L->Next;
     int count = 0;

     while(P != NULL ){
          count += 1;
          P = P->Next;
     }

     return count;
}
