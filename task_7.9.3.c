#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node;
struct list;

struct list*create();

void gotohead(struct list*);
void gotonext(struct list*);
void gotoprev(struct list*);

int isempty(struct list*);
int ishead(struct list*);
int getcur(struct list*);

void addafter(struct list*,int);
void addbefore(struct list*,int);
void delcur(struct list*);
void clean(struct list*);
void deleq(struct list*);
void delalleq(struct list*);

void print(struct list*);
void command(void);
int inparse(int*);


int main()
{
 command();
 return 0;
}


struct node
{
 int val;
 struct node *prev,*next;
};

struct list
{
 struct node *head,*cur;
};


struct list *create()
{
 struct list *a=(struct list*)malloc(sizeof(struct list));
 a->cur=a->head=NULL;
 return a;
}

int getcur(struct list *x)
{
 if(isempty(x)==0)
  return x->cur->val;
}

int isempty(struct list *x)
{
 return x->head==NULL;
}

int ishead(struct list *x)
{
 return x->cur==x->head;
}

void gotohead(struct list *x)
{
 x->cur=x->head;
}

void gotonext(struct list *x)
{
 if(isempty(x)==0)
  x->cur=x->cur->next;
}

void gotoprev(struct list *x)
{
 if(isempty(x)==0)
  x->cur=x->cur->prev;
}

void addafter(struct list *x, int newval)
{
 struct node *newnode=(struct node*)malloc(sizeof(struct node));
 newnode->val=newval;
 newnode->prev=newnode->next=NULL;

 if(isempty(x))
 {
  x->cur=x->head=newnode;
  x->cur->next=x->cur->prev=x->cur;
 }
 newnode->prev=x->cur;
 newnode->next=x->cur->next;
 x->cur->next->prev=newnode;
 x->cur->next=newnode;
}

void addbefore(struct list *x, int newval)
{
 struct node *newnode=(struct node*)malloc(sizeof(struct node));
 newnode->val=newval;
 newnode->prev=newnode->next=NULL;

 if(isempty(x))
 {
  x->cur=x->head=newnode;
  x->cur->next=x->cur->prev=x->cur;
 }
 newnode->prev=x->cur->prev;
 newnode->next=x->cur;
 x->cur->prev->next=newnode;
 x->cur->prev=newnode;
}

void delcur(struct list *x) //and gotonext
{
 if(isempty(x)) return;
 if(x->cur->next==x->cur) //only head
 {
  free(x->head);
  x->cur=x->head=NULL;
 }
 else
 {
  struct node *temp=x->cur->prev;
  temp->next=x->cur->next;
  x->cur->next->prev=temp;
  if(ishead(x)) x->head=temp->next;
  free(x->cur);
  x->cur=temp->next;
 }
}

void deleq(struct list *x) //delete equal values except one
{
 if(isempty(x)||x->cur->next==x->cur) return;
 struct node *temp=x->cur;
 int value=x->cur->val;
 gotonext(x);
 for(;x->cur!=temp;)
 {
  int valtmp = x->cur->val;
  if(valtmp==value)
  {
   delcur(x);
   continue;
  }
  gotonext(x);
 }
 x->cur=temp;
}

void delalleq(struct list *x)
{
 if(isempty(x)||x->cur->next==x->cur) return;
 struct node *temp=x->cur;
 gotonext(x);
 for(;x->cur!=temp;)
 {
  deleq(x);
  gotonext(x);
 }
 x->cur=temp;
}

void clean(struct list *x)
{
 for(;x->head!=NULL;) delcur(x);
}

void print(struct list *x)
{
 struct node *temp=x->cur;
 printf("\nList:\n\n");
 if(isempty(x)==0)
 {
/*
  for(temp=x->cur;;temp=temp->next)
  {
   printf("%i ",temp->val);
   if(temp==x->cur) break;
  }
*/
  do
  {
   printf("%i ",temp->val);
   temp=temp->next;
  }
  while(temp!=x->cur);
  printf("\n\nhead: %i\n",x->head->val);
  printf("\ncurrent: %i\n",x->cur->val);
 }
 printf("\n");
}

int inparse(int *y)
{char *str=NULL; size_t length=0; int i,result,flag,sgn;
 getline(&str,&length,stdin);

 for(result=flag=sgn=i=0;i<strlen(str);i++)
 {
  if(str[i]==45 && str[i+1]>=48 && str[i+1]<=57 && flag==0)
  {flag=1; sgn=1;}
  else if(str[i]>=48 && str[i]<=57)
  {
   if(flag==0) flag=1;
   result*=10; result+=str[i]-48;
  }
  else break;
 }
 free(str);
 if(sgn) result*=-1;
 if(flag) {*y=result; return 0;}
 else
 {
  printf("\nValue Error: non-integer input\n");
  return -1;
 }
}

void command(void)
{
 int cmd,num;
 struct list *l=create();

 printf("\nEmpty circular doubly linked list was created.\n");
 printf("\nСommands:\n");
 printf("\n0 - Clean list.\n");
 printf("\n1 - Print list.\n");
 printf("\n2 - Add new integer after current.\n");
 printf("\n3 - Add new integer before current.\n");
 printf("\n4 - Delete current (next is set as new current).\n");
 printf("\n5 - Delete all equal (to current) except one current.\n");
 printf("\n6 - Delete all equal (in the whole list) except one of each value.\n");
 printf("\n7 - Go to the head (set the current to the head).\n");
 printf("\n8 - Go to the next.\n");
 printf("\n9 - Go to the previous.\n");
 printf("\n10 - Get current value.\n");
 printf("\n11 - Is list empty?\n");
 printf("\n12 - Is head the current?\n");
 printf("\n13 - Help (you'll see this list of commands again).\n");
 printf("\n14 - Quit program.\n");

 for(;;)
 {
  printf("\nInput command: ");
  if(inparse(&cmd)==0)
  {
   switch(cmd)
   {
    case 0: clean(l); print(l); break;
    case 1: print(l); break;
    case 2:
      printf("\nInput number to add after: ");
      if(inparse(&num)==0) {addafter(l,num);}
      print(l); break;
    case 3:
      printf("\nInput number to add before: ");
      if(inparse(&num)==0) {addbefore(l,num);}
      print(l); break;
    case 4: delcur(l); print(l); break;
    case 5: deleq(l); print(l); break;
    case 6: delalleq(l); print(l); break;
    case 7: gotohead(l); print(l); break;
    case 8: gotonext(l); print(l); break;
    case 9: gotoprev(l); print(l); break;
    case 10:
      if(isempty(l)==0)
       printf("\ncurrent value from getcur: %i\n",getcur(l));
      else printf("\nEmpty list has no values\n");
      break;
    case 11: printf("\nis empty: %i\n",isempty(l)); break;
    case 12:
      if(isempty(l)==0)
       printf("\nis head: %i\n",ishead(l));
      else printf("\nEmpty list has no head\n");
      break;
    case 13:
 printf("\nСommands:\n");
 printf("\n0 - Clean list.\n");
 printf("\n1 - Print list.\n");
 printf("\n2 - Add new integer after current.\n");
 printf("\n3 - Add new integer before current.\n");
 printf("\n4 - Delete current (next is set as new current).\n");
 printf("\n5 - Delete all equal (to current) except one current.\n");
 printf("\n6 - Delete all equal (in the whole list) except one of each value.\n");
 printf("\n7 - Go to the head (set the current to the head).\n");
 printf("\n8 - Go to the next.\n");
 printf("\n9 - Go to the previous.\n");
 printf("\n10 - Get current value.\n");
 printf("\n11 - Is list empty?\n");
 printf("\n12 - Is head the current?\n");
 printf("\n13 - Help (you'll see this list of commands again).\n");
 printf("\n14 - Quit program.\n");      break;
    case 14: printf("\nBye.\n"); clean(l); free(l); return; break;
    default: printf("\nWrong command.\n"); break;
   }
  }
 }
}

