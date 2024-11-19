#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <stdbool.h>

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
void free_tree(Node *t);
bool are_same(Node *a, Node *b);

int main(void)
{
   Node *head1 = MakeNode('A');
   Node *n;
   int nd_max = 1;
   int nd_itr = 1;

   srand(time(NULL));
   for(char c = 'B'; c < 'G'; c++){
      n = MakeNode(c);
      InsertRandom(head1, n, &nd_max, &nd_itr);
   }

   printf("max depth is %d\n", nd_max);
   char *p_head1 = PrintTree(head1);
   printf("%s\n", p_head1);

   /////////////////////////////////////////////////// this should be a separate function, but I can't be asked to make this pretty as long as it work

   Node *head2 = MakeNode('A');
   Node *m;
   nd_max = 1;
   nd_itr = 1;

   // srand(time(NULL));
   for(char c = 'B'; c < 'G'; c++){
      m = MakeNode(c);
      InsertRandom(head2, m, &nd_max, &nd_itr);
   }

   printf("max depth is %d\n", nd_max);
   char *p_head2 = PrintTree(head2);
   printf("%s\n", p_head2);



   if (are_same(head1, head2) == true){
      printf("The 2 trees are identical\n");
      printf("\n");
   }
   else{
      printf("The 2 trees have differences\n");
      printf("\n");
   }
   
   free(p_head1);
   free_tree(head1);
   free(p_head2);
   free_tree(head2);

   return 0;
}

bool are_same(Node *a, Node *b)
{
   if (((a == NULL) ^ (b == NULL)) == true){ // if both are NULL or pointers, XOR is false -> false == the nodes are the same
      return false;
   }

   if (a != NULL){ //it could alt be b, it doesn't matter
      if (a->c != b->c){
         return false;
      }

      if (are_same(a->left, b->left) == false){
         return false; 
      }
      if (are_same(a->right, b->right) == false){
         return false; 
      }
   }

   return true;
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
         (*nd_itr)++;
         if ((*nd_max) < (*nd_itr)){
            (*nd_max) = (*nd_itr);
         }
         (*nd_itr) = 1;
      }
      else{
         (*nd_itr)++;
         InsertRandom(t->left, n, nd_max, nd_itr);
      }
   }
   else{ /* Right */
      if(t->right == NULL){
         t->right = n;
         (*nd_itr)++;
         if ((*nd_max) < (*nd_itr)){
            (*nd_max) = (*nd_itr);
         }
         (*nd_itr) = 1;
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
   char *p_left = PrintTree(t->left); 
   char *p_right = PrintTree(t->right); 
   sprintf(str, "%c (%s) (%s)", t->c, p_left, p_right);
   free(p_left);
   free(p_right);
   return str;

}

void free_tree(Node *t)
{
   if(t->left != NULL){
      free_tree(t->left);
   }
   if(t->right != NULL){
      free_tree(t->right);
   }
   free(t);
}