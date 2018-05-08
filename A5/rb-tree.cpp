#include <iostream>
#include <cmath>
using namespace std;
struct node{
    char color;//color whether 'R' or 'B'
    int key; //val of node
    node *left;//ptr to left node
    node *right;//ptr to right node
    node *p;//parent pointer
}*root,*nul;//nul is sentinel node
int max_count=0,curr_count=0;
void create_sentinel(){ //A sentinel node is a black node to which all null pointers in tree point to.
    node *p=new node;
    if(p==NULL){
        cout<<"Memory allocation failed\n";
        return ;
    }
    p->color='B';
    p->left=NULL;
    p->right=NULL;
    nul=p;
    root=nul;
    root->p=nul;
}
void print_list(node *curr){//inorder traversal of the r-b tree
    if(curr!=nul){
                cout<<curr->key<<" "<<curr->color<<endl;

        if(curr->left!=nul) print_list(curr->left);
        if(curr->right!=nul) print_list(curr->right);
    }
}
int log(int n){
    int c=0;
    while(n>=2){
        c++;
        n/=2;
    }
    return c;
}

/*Left rotation*/
void left_rotate(node *x){
    node *y=x->right;
    x->right=y->left;
    if(y->left!=nul) y->left->p=x;
    y->p=x->p;
    if(x->p==nul) root=y;
    else if(x==x->p->left) x->p->left=y;
    else x->p->right=y;
    y->left=x;
    x->p=y;
}
/*Right rotation*/
void right_rotate(node *y){
    node *x=y->left;
    y->left=x->right;
    if(x->right!=nul) x->right->p=y;
    x->p=y->p;
    if(y->p==nul) root=x;
    else if(y==y->p->left) y->p->left=x;
    else y->p->right=x;
    x->right=y;
    y->p=x;
}

/*corrects the color of the nodes by traversing up the tree*/
void insert_fixup(node *z){
    node *y;
    while(z->p->color=='R'){ //Upto parent color is red , as black color node can have its children of any color
        if(z->p==z->p->p->left) { //If parent of z is left sibling
            y=z->p->p->right;//y is right sibling of parent
            if(y->color=='R'){//checks if color of y is R
                z->p->color='B';
                y->color='B';
                z->p->p->color='R';
                z=z->p->p;
            }
            else if(z==z->p->right){//if z is right sibling
                z=z->p;
                left_rotate(z);
            }
            else { //if z is left sibling
                z->p->color='B';
                z->p->p->color='R';
                right_rotate(z->p->p);
            }
        }
        else{
            y=z->p->p->left;
            if(y->color=='R'){
                z->p->color='B';
                y->color='B';
                z->p->p->color='R';
                z=z->p->p;
            }
            else if(z==z->p->left){
                z=z->p;
                right_rotate(z);
            }
            else {
                z->p->color='B';
                z->p->p->color='R';
                left_rotate(z->p->p);
            }
        }
    }
    root->color='B';
}
                


/* Inserts independent of the color of nodes which will be fixed up in the insert-fixup-method*/
void insert(int val){
    node *n=new node;
    if(n==NULL){
        cout<<"Memory allocation failed\n";
        return ;
    }
    n->key=val;
    node *x,*y;
    x=root;
    y=nul;
    while(x!=nul){
        y=x;
        if(n->key<x->key) x=x->left;
        else x=x->right;
    }
    
    n->p=y;
    if(y==nul) root=n;
    else if(n->key<y->key) y->left=n;
    else y->right=n;
    n->left=nul;
    n->right=nul;
    n->color='R';
    insert_fixup(n);
}

/* Searches for the noe*/
node *search(int val,node *curr){
    if(curr==nul) return curr;
    else if(curr->key==val) return curr;
    else if(curr->key>val) return search(val,curr->left);
    else return search(val,curr->right);
}

void dfs(node *curr){//For calculating height of tree
    if(curr==nul) {
        if(curr_count>max_count) max_count=curr_count;
            return ;
    }
    curr_count++;
    dfs(curr->left);
    dfs(curr->right);
    curr_count--;
}
void sabfree(node *curr){
    if(curr!=nul){
        if(curr->left!=nul) sabfree(curr->left);
        if(curr->right!=nul) sabfree(curr->right);
        sabfree(curr);
    }
}

int main(){
    cout<<"Welcome to RB Tree\n";
    create_sentinel();
    int count=0;
    while(1){
        cout<<"1.Insert\n2.Search\n";
        int x;
        cin>>x;
        if(x>2 || x<1) break;
        else if(x==1){
            cout<<"Enter val:\t";
            int y;
            cin>>y;
            insert(y);
            count++;
        }
        else if(x==2){
            cout<<"Enter val:\t";
            int y;
            cin>>y;
            node *z=search(y,root);
            if(z==nul) cout<<"Not found\n";
            else cout<<"Found : "<<z->key<<" : "<<z->color<<endl;
        }
        dfs(root);
        cout<<"Height : "<<max_count<<" "<<"Log : "<<2*log(count+1)<<endl;
        print_list(root);
        curr_count=0;
        max_count=0;
    }
    sabfree(root);
    delete nul;
}
