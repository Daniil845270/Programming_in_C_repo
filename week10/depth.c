#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#define STRSIZE 5000

struct node{
	char c;
	struct node *left;
	struct node *right;
};
typedef struct node Node;

Node *MakeNode(char c);
void InsertRandom(Node *t, Node *n, int* nd_max, int* nd_itr);
char *PrintTree(Node *t);

int main(void)
{
   char c;
   Node *head = MakeNode('A');
   int nd_max = 1;
   int nd_itr = 1;
   Node *n;

   srand(time(NULL));
   for(c = 'B'; c < 'G'; c++){
      n = MakeNode(c);
      InsertRandom(head, n, &nd_max, &nd_itr);
   }
   printf("max depth is %d\n", nd_max);
   printf("%s\n", PrintTree(head));
   return 0;
}

Node *MakeNode(char c)
{

   Node *n = (Node *)calloc(1, sizeof(Node));
   assert(n != NULL);
   n->c = c;
   return n;

}

void InsertRandom(Node *t, Node *n, int* nd_max, int* nd_itr)
{

   if((rand()%2) == 0){ /* Left */
      if(t->left == NULL){
         t->left = n;
         if ((*nd_max) < (*nd_itr)){
            (*nd_max) = (*nd_itr);
         }
         (*nd_itr) = 0;
      }
      else{
         (*nd_itr)++;
         InsertRandom(t->left, n, nd_max, nd_itr);
      }
   }
   else{ /* Right */
      if(t->right == NULL){
         t->right = n;
         if ((*nd_max) < (*nd_itr)){
            (*nd_max) = (*nd_itr);
         }
         (*nd_itr) = 0;
      }
      else{
         (*nd_itr)++;
         InsertRandom(t->right, n, nd_max, nd_itr);
      }
   }

}

char *PrintTree(Node *t)
{

   char *str;

   assert((str = calloc(STRSIZE, sizeof(char))) != NULL);
   if(t == NULL){
      strcpy(str, "*");
      return str;
   }
   sprintf(str, "%c (%s) (%s)", t->c, PrintTree(t->left), PrintTree(t->right));
   return str;

}