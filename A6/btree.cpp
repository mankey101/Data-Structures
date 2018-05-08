#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
#define MAX     20
struct node{
    int keys[MAX];//Stores the values in the node
    node *c[MAX];//Stores the pointers to childrn
    bool isLeaf;//checks if node is leaf or not
    int number_nodes;//number of keys in the node
}*root=NULL;//rot node
int t;//order of the tree
int height=0;
void remove(node *curr,int val); //removes the node with value 'val'
bool isFull(node *r){ //returns if node is full or not
    if(r->number_nodes==2*t-1) return true;
    else return false;
}

void print_list(node *curr) //Prints the list 
{
    int i;
    for (i = 0; i < curr->number_nodes; i++){
                cout<<" "<< curr->keys[i];

        if (!(curr->isLeaf)) print_list(curr->c[i]);
    }
 
    if (curr->isLeaf == false) print_list(curr->c[i]);
}
void sabfree(node *curr){//frees all the nodes
    int i;
    if(curr!=NULL){
        for (i = 0; i < curr->number_nodes; i++){
            if (!(curr->isLeaf)) sabfree(curr->c[i]);
        }
        if (curr->isLeaf == false) sabfree(curr->c[i]);
        delete curr;
    }
}
void split_child(node *x,int i,node *y){//if node is full then middle element is promoted and node is split in half
    node *z=new node;// z is the sister of the node y
    z->isLeaf=y->isLeaf;
    z->number_nodes=t-1;
    /* Copies second half of data of y into z*/
    for(int j=0;j<t-1;j++) z->keys[j]=y->keys[j+t];
    if(!(y->isLeaf)){
        for(int j=0;j<t;j++) z->c[j]=y->c[j+t];    
    }
    y->number_nodes=t-1;
    for(int j=x->number_nodes;j>i;j--){
        x->c[j+1]=x->c[j];
    }
    x->c[i+1]=z;
    //shifts the keys of x one poisition right
    for(int j=x->number_nodes-1;j>=i;j--){
        x->keys[j+1]=x->keys[j];
    }
    //inserts the new ket into x
    x->keys[i]=y->keys[t-1];
    x->number_nodes=x->number_nodes+1;
}
            
void insert_non_full(node *x,int k){
    int i=x->number_nodes-1; 
    if(x->isLeaf){//if x is leaf then we simply insert into this leaf
        while(i>=0 && k<x->keys[i]){
            x->keys[i+1]=x->keys[i];//it is assured it will be non full
            i=i-1;
        }
        x->keys[i+1]=k;
        x->number_nodes=x->number_nodes+1;
    }
    else {
        while(i>=0 && k<x->keys[i]){
            i=i-1;
        }
        i=i+1;//we go to current indexed child
        if(x->c[i]->number_nodes==2*t-1) {//if child is full, the node is split
            split_child(x,i,x->c[i]);
            if(k>x->keys[i]) i=i+1;
        }
        insert_non_full(x->c[i],k);// else we go to the child without splitting , it ensures that child is non full
    }
}

/*inserts node into the tree*/
void insert(int val){
    //checks if root is NULL and inserts into it
    if(root==NULL){
        root=new node;
        root->keys[0] = val;
        root->isLeaf=true;
        root->number_nodes = 1;
    }
    else{
        node *r=root;
        //If root is full then we split the root and insert into the new root
        if(r->number_nodes==(2*t-1)){
            node *s=new node;
            s->isLeaf=false;
            s->c[0]=root;
            split_child(s,0,r);
            insert_non_full(s,val);
            root=s;
        }
        else insert_non_full(r,val);
    }
}
/*Returns whether the key is in tree or not */
bool isThere(node *curr,int key){
    int i;
    if(!(curr->isLeaf)){
        for(i=0;i<curr->number_nodes;i++){
            if(curr->keys[i]==key) return true;
            else if(curr->keys[i]>key) return isThere(curr->c[i],key);        
        } 
        return isThere(curr->c[curr->number_nodes],key);
    }
    else{
        for(i=0;i<curr->number_nodes;i++){
            if(curr->keys[i]==key) return true;
            else if(curr->keys[i]>key) return false;
        }
        return false;
    }
}

/* returns the node containing the key 'val'*/
node *return_node(node *curr,int val){

    int i;
    if(!(curr->isLeaf)){
        for(i=0;i<curr->number_nodes;i++){
            if(curr->keys[i]==val) return curr;
            else if(curr->keys[i]>val) return return_node(curr->c[i],val);        
        } 
        return return_node(curr->c[curr->number_nodes],val);
    }
    else{
        for(i=0;i<curr->number_nodes;i++){
            if(curr->keys[i]==val) return curr;
        }
    }
    return NULL;
}

void remove_leaf(node *j,int val){
    int i;
    
    for(i=j->number_nodes;i>=0;i--) if(j->keys[i]==val) break;
    for (int i1=i+1; i1<j->number_nodes; i1++) j->keys[i1-1] = j->keys[i1];
    j->number_nodes--;
}

/* returns the index at which key is just greater than val in node*/
int inNode(node *curr,int val){
    int i;
    for(i=0;i<curr->number_nodes;i++) if(curr->keys[i]>=val) break;
    return i;
}
/*checks if key is in the current node or not*/
bool present(node *curr,int val){
    for(int i=0;i<curr->number_nodes;i++) if(curr->keys[i]==val) return true;
    return false;
}
/* borrows from left silbing if its value-rich*/
void reduce_sib_left(node *curr,int ch_index){
    node *pred=curr->c[ch_index]; //child
    node *left=curr->c[ch_index-1];//left sibling
    for (int i=pred->number_nodes-1; i>=0; i--) pred->keys[i+1] = pred->keys[i]; //keys of child are shifted to left
 
    if (!(pred->isLeaf)){//if not a child then children of the child are lso chifted to right
        for(int i=pred->number_nodes; i>=0; i--)
            pred->c[i+1] = pred->c[i];
    }
    /*first key of child becomes the child-indexed key of curr*/
     pred->keys[0]=curr->keys[ch_index-1];
 
    if (!(pred->isLeaf)) pred->c[0]=left->c[left->number_nodes]; //child's first child becomes last child of left sibling
    curr->keys[ch_index-1] = left->keys[left->number_nodes-1]; //update the child-indexed key of curr
    pred->number_nodes++;//left sibling nodes are reduced
    left->number_nodes--;//right sibling increased
}
/*borrows from right if its value-rich*/
void reduce_sib_right(node *curr,int ch_index){
    node *pred=curr->c[ch_index];
    node *right=curr->c[ch_index+1];
 
    pred->keys[pred->number_nodes]=curr->keys[ch_index];
 
    if (!(pred->isLeaf)) pred->c[pred->number_nodes+1] = right->c[0];
     
     curr->keys[ch_index]=right->keys[0];
 
    for(int i=1;i<right->number_nodes;i++) right->keys[i-1] = right->keys[i];
    if(!(right->isLeaf)){
        for(int i=1;i<=right->number_nodes;i++) right->c[i-1]=right->c[i];
    }

    pred->number_nodes++;
    right->number_nodes--;
}

/* If neither of left or right sibling is key rich , we merge the  current node and next if curr is not last
and prev and curr if curr node is last*/
void merge(int ch_index,node *curr){
    node *pred=curr->c[ch_index];
    node *next=curr->c[ch_index+1];
    pred->keys[t-1]=curr->keys[ch_index];
    //copies from next to current child
     for (int i=0; i<next->number_nodes; i++) pred->keys[i+t] = next->keys[i];
    //copies children of next too
     if (!(pred->isLeaf)){
        for(int i=0; i<=next->number_nodes; i++)
            pred->c[i+t] = next->c[i];
    }
 
    for (int i=ch_index+1; i<curr->number_nodes; i++)
        curr->keys[i-1] = curr->keys[i];
 
    for (int i=ch_index+2; i<=curr->number_nodes; i++)
        curr->c[i-1] = curr->c[i];
 
    pred->number_nodes += next->number_nodes+1;
    curr->number_nodes--;
    //delete the next node
    delete next;
    return;
}
/*If child is resourceless then we do the borrowing*/
void complete_child(node *curr,int ch_index){
    if(ch_index>0 && curr->c[ch_index-1]->number_nodes>=t) reduce_sib_left(curr,ch_index);
    else if(ch_index<curr->number_nodes && curr->c[ch_index+1]->number_nodes>=t) reduce_sib_right(curr,ch_index);
    else{
        if(ch_index!=curr->number_nodes) merge(ch_index,curr);//if not the last child then we merge with next
        else merge(ch_index-1,curr);//else with prev
    }
}

void remove_non_leaf(node *curr,int val){
    int i; 
    for(i=curr->number_nodes-1;i>=0;i--) if(curr->keys[i]==val) break;
    // i returns the index of curr node
    int temp=curr->keys[i];
    if(curr->c[i]->number_nodes >=t){
        node *pred=curr->c[i];
        while (!(pred->isLeaf)) pred = pred->c[pred->number_nodes];
        //keep moving downward unitl you reach a leaf and replace it
        int fore=pred->keys[pred->number_nodes-1];
        curr->keys[i]=fore;
        remove(curr->c[i],fore);
    }
    //if that node is not resourcesful then we ask for a key from next child key
    else if (curr->c[i+1]->number_nodes >= t){//it is sure that i+1 wouldn't exceed number_nodes 
    cout<<"I'm here\n";
        node *pred=curr->c[i+1];// as i is beginning from number_nodes -1
        while (!(pred->isLeaf)) pred = pred->c[0];
        int apr = pred->keys[0];
        curr->keys[i] = apr;
        remove(curr->c[i+1],apr);
    }
    else {
        //none resourcesful so we merge the two nodes.
        merge(i,curr);
        remove(curr->c[i],temp);
    }
}

void remove(node *curr,int val){
    int j=inNode(curr,val);
    //j returns the index of key just greater than val
    if(present(curr,val)){
        if(curr->isLeaf) remove_leaf(curr,val); //if present in node and curr node is leaf
        else remove_non_leaf(curr,val);//if not a leaf
    }
    else{
        bool atEnd;
        if(j==curr->number_nodes) atEnd=true; //if last node
        else atEnd =false;
        if(curr->c[j]->number_nodes<t) complete_child(curr,j); //completes the child
        if(atEnd && j>curr->number_nodes) remove(curr->c[j-1],val); //completion reduces the number of nodes by 1 so we update the corrected child
        else remove(curr->c[j],val);
    }
}



int main(){
    cout<<"Welcome to B-tree for odd keys\nEnter order :\n";
    label:cin>>t;
    if(t%2==0) {cout<<"Only odd keys!(>1)\n"; goto label;}

    else if(t==1){cout<<"B-tree used for accessing large data from drives , so enter >1\n"; goto label;}

    while(1){
        cout<<"1.Insert\n2.Search\n3.Delete\n4.Exit\n";
        int y;
        cin>>y;
        if(y==1){
            int val;
            cin>>val;
            insert(val);
        }
        else if(y==2) {
                cout<<"Enter value :\n";
                int val;
                cin>>val;
                if(root!=NULL){
                    if(isThere(root,val)) cout<<"Found\n";
                    else cout<<"Not found\n";
                }
        }
        else if(y==3){
            int val;
            cin>>val;
            if(root==NULL) {}
            else if(isThere(root,val)){
                remove(root,val);
                /*If root if reduced to 0 keys then we have to update one of child as root*/
                if(root->number_nodes==0){
                    node *toDel=root;
                    if(root->isLeaf) root=NULL;
                    else root=root->c[0];
                    delete toDel;
                }
            }
            else cout<<"Not found!\n";
        }
        else if(y<1 || y>3) break;
        if(root!=NULL) {
            cout<<"List : ";
             print_list(root);
        }
        else cout<<"Empty tree\n";
        cout<<"\n";
    }
    sabfree(root);

}
            

