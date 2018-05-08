#include <iostream>
using namespace std;

struct node{
    int val;//stores the val in the node
    int degree;//stores the degree or k of Bk binomial heap
    node *child;//stores the leftmost child of the node
    node *sibling;//stores the node next to the given node
    node *parent;//stores the parent of the node
};

struct heap{//points to the first node in heap
    node *head;
}*h;//Stores the head pointer to the heap linked list
heap *union_heap(heap *);

heap *create_heap(){//Creates an empty heap with head as NULL
    heap * h=new heap;
    h->head=NULL;
    return h;
}
void printTree(node *g){//prints the heap
    while (g!=NULL){
        cout << g->val << " ";//prints the root
        printTree(g->child);//goes to lefmost child
        g=g->sibling; //then goes to child's sibling
    }
}
void sabfree(node *g){//prints the heap
    while (g!=NULL){
        sabfree(g->child);//goes to lefmost child
        node *temp=g;
        g=g->sibling; //then goes to child's sibling
        delete temp;
    }
}

 
void insert(node *z){
    heap *h1= create_heap(); //Empty heap is created
    z->parent=NULL;
    z->child=NULL;
    z->sibling=NULL;
    z->degree=0;//A node 'z' with initial parametres NULL is created and inserted to heap h1
    h1->head=z;
    h=union_heap(h1);//h i.e our main heap is joined with this single node heap h1.
}

heap *binomial_heap_merge(heap *h2){//Merges two binomial heaps
    node *x=h->head;//pointer to first element of main heap
    node *y=h2->head;
    heap *hi=create_heap();//Heap which will contain the merged data 
    node *ptr;//points to current node poisition in merged heap
    if(x==NULL || y==NULL){//If either of the nodes is null then ptr is pointing to non null node
        if(x==NULL) {
            hi->head=y;
            ptr=y;
            y=y->sibling;
        }
        else  if(y==NULL){
            hi->head=x;
            ptr=x;
            x=x->sibling;
        }
    } //now the node whose degree is less is included first
    else {
        if(x->degree<=y->degree){
            hi->head=x;
            ptr=x;
            x=x->sibling;
        }
        else{
             hi->head=y;
             ptr=y;
             y=y->sibling;
        }
    }
    while(x!=NULL && y!=NULL){
        if(x->degree<=y->degree){
            ptr->sibling=x;
            ptr=x;
            x=x->sibling;
        }
        else if(x->degree>y->degree){
            ptr->sibling=y;
            ptr=y;
            y=y->sibling;
        }
   }
    while(x!=NULL){
        ptr->sibling=x;
        ptr=x;
        x=x->sibling;
    }
    while(y!=NULL){
        ptr->sibling=y;
        ptr=y;
        y=y->sibling;
    }
    return hi;//merged heap is returned
}

void binomial_link(node *y,node *z){//Makes the parent of y to be z
    y->parent=z;
    y->sibling=z->child;
    z->child=y;
    z->degree++;//degree of z increases
}

 heap *union_heap(heap *h2){//Merges two binomial trees whose degree is same and increases the degree
    heap *hi = binomial_heap_merge(h2);//merges to heaps irrespective of two trees having same degree
    delete h;//deletes h
    delete h2;//deletes h2
    if(hi->head==NULL) return h;
    node *prev=NULL;//prev of curr node
    node *x=hi->head;
    node *next=x->sibling;//next node
    while(next!=NULL){
        //if either degrees of next and x are diff or degree of x is equal to next equal to sibling of next
        if((x->degree!=next->degree) || (next->sibling!=NULL && x->degree == next->sibling->degree) ){
            prev=x;
            x=next;
        } 
        //degrees of x and next are equal so we make the parent whose val is minimum
        else if(x->val < next->val) { 
            x->sibling=next->sibling;
            binomial_link(next,x);
        }
        else{//else case of next 
            if(prev==NULL) hi->head=next;
            else prev->sibling=next;
            binomial_link(x,next);
            x=next;
        }
        next=x->sibling;
    }
    return hi;
 
 }

 int search_min(){ //Searches the minimum value along the roots
    node *x=h->head;
    int min=x->val;
    node *temp=x;
    while(x!=NULL){
        if(min>x->val){
            min=x->val;
            temp=x;
        }
        x=x->sibling;
    }
    return min;
 }
 
void extract_min(){ //Deletes the minimum value
    node *x=h->head;
    node *prev=NULL;
    int min=x->val;
    node *temp=x;
    while(x->sibling!=NULL){
        if(min>x->sibling->val){
            min=x->val;
            temp=x->sibling;
            prev=x;//stores the node whose sibling is minimum
        }
        x=x->sibling;
    }
    node *curr=temp;
    if(curr->sibling ==NULL && curr->child==NULL){//if only node present in heap
        delete curr;
        h->head=NULL;
        return ;
    }
    temp=temp->child;
    int cnt=0;
    node *temp2=temp;
    while(temp2!=NULL) {
        cnt++;
        temp2=temp2->sibling;
    }
    node* arr[cnt];
    for(int i=0;i<cnt;i++){
        arr[i]=temp;
        temp=temp->sibling;
    }
    heap* h1= create_heap();//new heap h1 which will containt all the children of min node in reverse order
    node *ptr;
    if(cnt>0){//if children are non zero
        ptr=arr[cnt-1];
        h1->head=ptr;
        for(int i=cnt-2;i>=0;i--){//reverses the linked list
            ptr->sibling=arr[i];
            ptr=arr[i];
        }
        ptr->sibling=NULL;
        node *p=h1->head;
    }
    if(prev==NULL)h->head=curr->sibling;
    else prev->sibling=curr->sibling;
    delete curr;
    node *t=h1->head;
    h=union_heap(h1);//Unites the two heaps
}

 int main(){
    cout<<"Welcome to Binomial Heap\n";
    h=create_heap();
    while(1){
        cout<<"1.Insert\n2.Search_Min\n3.Extract_Min\n4.Exit\n";
        int y;
        cin>>y;
        if(y==1){
            int val;
            cin>>val;
            node *z=new node;
            z->val=val;
            insert(z);
        }
        else if(y==2) {
            if(h->head!=NULL) cout<<search_min()<<"\n";
        }
        else if(y==3){
             if(h->head!=NULL) extract_min();
        }
        else if(y<1 || y>3) break;
        /*for(node *i=h->head;i!=NULL;i=i->sibling) cout<<i->degree<<" ";
        cout<<"\n";*/
        if(h->head==NULL) cout<<"Empty tree";

        else printTree(h->head);
        cout<<"\n";
    }
    sabfree(h->head);
}

