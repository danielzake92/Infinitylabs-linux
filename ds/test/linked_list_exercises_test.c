#include <stdio.h>/*Required for standard input output*/
#include <stdlib.h> /*Required for malloc*/
#include <linked_list_exercises.h>

static node_t *Create(int A[], int n);
static void Display(struct Node *p);
static void AddLoop(node_t *head, int index);

int main()
{
    int a_arr[] = {1,2,3,4,5};
    int b_arr[] = {1,2};
    int c_arr[] = {1};
	int A[] = {1,2,3,4,5,6,7,8};
    int B[] = {11,22,33,44};

    node_t *a = NULL; 
    node_t *b = NULL; 
    node_t *c = NULL; 
    
	node_t *mylist = Create(A,5);
    node_t *secondlist = Create(B,4);
    node_t *check = NULL;
    node_t *bnode = secondlist;
    node_t *anode = mylist;	
    
    /* test Flip */
    
    a = Create(a_arr, 5);
    b = Create(b_arr, 2);
    c = Create(c_arr, 1);
  	
    
    printf("a:\n");
    Display(a);
    puts("");
    a = Flip(a);
    printf("a (flipped):\n");
    Display(a);
    puts("");
    
    printf("The return val is : %d\n",NthFromLast(a, 3)->data);
    
    printf("b:\n");
    Display(b);
    puts("");
    b = Flip(b);
    printf("b (flipped):\n");
    Display(b);
    puts("");
    
    printf("c:\n");
    Display(c);
    puts("");
    c = Flip(c);
    printf("c (flipped):\n");
    Display(c);
    puts("");
    
    /* test HasLoop */
        
    printf("a shouldn't be with loop: %d\n",HasLoop(a));
    AddLoop(a, 3);
    printf("a should be with loop: %d\n",HasLoop(a));
    puts("");
    
    printf("b shouldn't be with loop: %d\n",HasLoop(b));
    AddLoop(b, 0);
    printf("b should be with loop: %d\n",HasLoop(b));
    puts("");
    
    /* test intersection */
    anode = anode->next->next;
    
    bnode = bnode->next->next->next;
    bnode->next = anode;
    
    puts("Intersection\n************");
    check = Intersection( secondlist, mylist);
    
    puts("anode");
    Display(anode);
    puts("");
    
    puts("bnode");
    Display(bnode);
    puts("");
    
    printf("intersection is from : %d\n",check->data); 
    puts("");
    
    puts("Intersection seperation\n***********************");
    IntersectionSeperation(secondlist, mylist, check);
    
    puts("anode");
    Display(anode);
    puts("");
    
    puts("bnode");
    Display(bnode);
    puts("");
    
    
    return 0;
}


static node_t *Create(int A[], int n)
{
    int i;
    struct Node *current;
    struct Node *back;
    struct Node *t;
    struct Node *last;
    current = (struct Node *)malloc(sizeof(struct Node));
    current->data = A[0];
    current->next = NULL;
    last = current;
    back = current; 
    for(i = 1; i <n; ++i)
    {
        t = (struct Node *)malloc(sizeof(struct Node));
        t->data = A[i];
        t->next = NULL;
        last->next = t;
        last = t;
    }
    return back;
}


static void Display(struct Node *p)
{
	while(p != NULL)
	{
		printf("%d-> ",p->data);
		p = p->next;
	}
	puts("NULL");
}

static void AddLoop(node_t *head, int index)
{
    node_t *circular_begin = NULL;
    node_t *circular_end = NULL;
    int i = 0;
    
    circular_begin = head;
    
    for(; i < index; ++i, circular_begin=circular_begin->next);
    circular_end = circular_begin;
    
    for(; circular_end->next; circular_end=circular_end->next);
    circular_end->next = circular_begin;
}

