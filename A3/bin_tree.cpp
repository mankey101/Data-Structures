#include <iostream>
using namespace std;
struct node{
	int num;
	char gender;
        string college;	
	node* lptr;
	node* rptr;
}*root=NULL;//Stores the information of the student
void insert(node* n,node* curr){ //inserts into the tree
	if(root==NULL){ root=n;	return ;} //NULL root case
	else if(n->num>curr->num){
		if(curr->rptr==NULL) {
			curr->rptr=n;
			return ;
		}
		else insert(n,curr->rptr);//recursion upon going to the correct root depending upon values
	}
	else if(n->num < curr->num){//if val of input node is less it goes to left side of the tree
		if(curr->lptr==NULL){
			curr->lptr=n;
			return ;
		}
		else insert(n,curr->lptr);
	}
}
bool search(int val,node* curr){//Recursively checks if value is there
	if(curr==NULL) return false;
	if(val==curr->num) return true;
	else if(val>curr->num) return search(val,curr->rptr);
	else return search(val,curr->lptr);
}
node* foundF(int val,node* curr){//reccursively returns the pointer to node whose value is being searhed
	if( (curr->lptr!=NULL && val==curr->lptr->num ) ||(curr->rptr!=NULL &&  val==curr->rptr->num ) ) return curr;
	else if(val>curr->num) return foundF(val,curr->rptr);
	else return foundF(val,curr->lptr);
}
node* delet(node* curr){ 
	if(curr->rptr==NULL) return curr;
	else return delet(curr->rptr);
}
void prnt_tree(node * curr)//prints the tree in inorder traversal
{
	if(curr!=NULL){
		 	    cout<<curr -> num<<" "<<curr->gender<<"\t"<<curr->college<<endl; //prints curent root

  	  if(curr -> lptr != NULL) prnt_tree(curr -> lptr); //first goes to left subtree
 	   if(curr -> rptr != NULL) prnt_tree(curr -> rptr);//goes to right subtree
	}
}
void sabfree(node * curr)//deallocates memory given to the nodes
{
	if(curr!=NULL){
		if(curr -> lptr != NULL) sabfree(curr -> lptr);
   	        if(curr -> rptr != NULL) sabfree(curr -> rptr);
   		 delete(curr);
	}
}

node* extract(node *curr,int x){
    if(x==curr->num) return curr;
    else if(x>curr->num) return extract(curr->rptr,x);
    else return extract(curr->lptr,x);
}

int main(){
	int a;
	cout<<"Choice : \n1.Insert\n2.Search\n3.Delete\n4.Print\n5.Delete all"<<endl;
	while(cin>>a){
		int x;
		if(a<1 || a>5) break;
		if(a<=3) {
			cout<<"Enter name (Integer): ";
			cin>>x;
		}
		if(a==1){
			node* n=new node();
			if(n==NULL) {
                cout<<"Memory allocation failed\n";
                break;
			}
			n->num=x;	
			char gen;
			cout<<"Enter gender  (M/F) : ";
			cin>>gen;
			cout<<"Enter college : ";
			string s;
			cin.ignore();
			getline(cin,s);
			n->gender=gen;
			n->college=s;
			insert(n,root);
		}
		else if(a==2){
		       if(search(x,root)) {
                    cout<<"Found\n"<<endl;
                    node* temp;
                    temp=extract(root,x);
                    cout<<temp->num<<"\n"<<temp->gender<<"\n"<<temp->college<<"\n";
                }
			else cout<<"Nope"<<endl;
		}
		else if(a==3){
			if(search(x,root)){
				if(root->num==x) {
					if(root->lptr==NULL){
						node *p=root->rptr;
						delete root;
						root=p;
					}
					else{
						node* swap=delet(root->lptr);
						node *fat=foundF(swap->num,root);
						root->num=swap->num;
							if(fat->lptr==swap) fat->lptr=swap->lptr;
							else fat->rptr=swap->lptr;
							delete swap;
					}
				}
				else {
					node* curr;
					bool flag=0;	
					node* father=foundF(x,root);
					if(father->lptr!=NULL && father->lptr->num==x) curr=father->lptr;
					else { curr=father->rptr; flag=1; }
					if(curr->lptr==NULL){
						if(flag) father->rptr=curr->rptr;
						else father->lptr=curr->rptr;
						delete curr;
					}
					else{
						node* swap=delet(curr->lptr);
						node* fat=foundF(swap->num,root);
						curr->num=swap->num;
						if(fat->lptr!=NULL && fat->lptr==swap) fat->lptr=swap->lptr;
						else fat->rptr=swap->lptr;
						delete swap;
					}
				}
			}
			else cout<<"Not Found"<<endl;
		}
		else if(a==4){
			if(root==NULL) cout<<"Empty list!";
			else prnt_tree(root);
		}
		else if(a==5) {
			if(root!=NULL) {
				sabfree(root);
				root=NULL;
			}
			else cout<<"Already empty\n";
		}
		else break;
		cout<<"\nChoice : \n1.Insert\n2.Search\n3.Delete\n4.Print\n5.Delete all"<<endl;
	}
	sabfree(root);	
}

