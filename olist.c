#include <stdio.h>
#include "olist.h"
#include <stdlib.h>

struct list * createList(){
   struct list *llist = malloc(sizeof(struct list));
   llist->head = NULL;
   llist->tail = NULL;
   return llist;
}

int numNodes = 0;

void insertNode(struct list *l, int val){
   struct listNode *cur;
   struct listNode *newNode = malloc(sizeof(struct listNode));

   if(newNode == NULL){
	   perror("Why enter a null node?");
	   exit(-1);
   }

   newNode->val = val;

   if(l->head == NULL){
      l->head = newNode;
      l->tail = newNode;
      newNode->previous = NULL;
      newNode->next = NULL;
   }
   else if(l->head->val >= val){
      l->head->previous = newNode;
      newNode->next = l->head;
      newNode->previous = NULL;
      l->head = newNode;
      if(l->head == l->tail){
         l->tail = newNode;
      }
   }
   else{
      for(cur = l->head; cur->next != NULL && cur->next->val < val; cur = cur->next);

      if(cur->next == NULL){
         l->tail = newNode;
      }
      else{
         cur->next->previous = newNode;
      }
      newNode->next = cur->next;
      newNode->previous = cur;
      cur->next = newNode;
   }
   numNodes++;
}

void deleteNode(struct list *l, int val){
   struct listNode *cur;

   for(cur = l->head; cur->val != val && cur->next != NULL; cur = cur->next);

   if(cur->val == val){
      if(cur->next == NULL){
         l->tail = cur->previous;
      }
      else{
         cur->next->previous = cur->previous;
      }
      if(cur->previous == NULL){
         l->head = cur->next;
      }
      else{
         cur->previous->next = cur->next;
      }
      numNodes--;
   }
   else{
      printf("The number specified is not in the list\n");
   }

   if(numNodes == 0){
      l->head = NULL;
      l->tail = NULL;
   }
}

void printListFW(struct list *l){
   struct listNode *cur;

   if(numNodes != 0){
   for(cur = l->head; cur->next != NULL; cur = cur->next){
      printf("%d ", cur->val);
   }
      printf("%d ", cur->val);
   }
   printf("\n");
}

void printListBW(struct list *l){
   struct listNode *cur;

   if(numNodes != 0){
   for(cur = l->tail; cur->previous != NULL; cur = cur->previous){
      printf("%d ", cur->val);
   }
      printf("%d ", cur->val);
   }
   printf("\n");
}
