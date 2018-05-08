#include <iostream>
using namespace std;
#define INF 100000000
#define MAXN 100001//Size of heap initially +2
struct node{
    int index;
    int distance;
    int parent;
};//stores the node information
struct edge{
  int x;
  int y;
  int distance;
  edge * ptr;
};//stores the edge information
node* min_heap[MAXN];
int counte=MAXN-1;//initial size of heap

void insert(edge** head,edge** tail,int x, int y,int weight){//Insertion in linked list
  edge *p=new edge;
  if(!p) {
    cout<<"Memory allocataion failed"; //either stack is full which results in no memory alloc
    return ;
  }
  p->x=x;//updating the edge variables
  p->y=y;
  p->distance=weight;
  if(*head==NULL){ //head is the head of linked list
    *head=p;
    *tail=p;//tail is the tail of linked lists
  }
  else{
    (*tail)->ptr=p;
    *tail=p;
  }
    (*tail)->ptr=NULL;
}

/*operations on min_heap*/
void swap(int a,int b){
	node* t=min_heap[a];
    min_heap[a]=min_heap[b];
	min_heap[b]=t;

}
void delete_head(){
  if(counte>0) counte--;
  else return ;
  min_heap[1]=min_heap[counte+1];
  min_heap[counte+1]->distance=INF;
	int i=1;
  while((2*i+1)<=counte && (min_heap[i]->distance>min_heap[2*i]->distance || min_heap[i]->distance>min_heap[2*i+1]->distance)){
        if(min_heap[2*i]->distance<min_heap[2*i+1]->distance){
			swap(i,2*i);
			i*=2;
		}
    else {
			swap(i,2*i+1);
			i=i*2+1;
		}
	}
}
/*Log and pow functions for determining the height of the tree*/
int log(int n){
    int c=0;
    while(n>=2){
        c++;
        n/=2;
    }
    return c;
}
int pow(int n){
    int c=1;
    while(n>=1){
        c=c*2;
        n--;
    }
    return c;
}

 /* Heapification i.e bubbling the heap upto the root or until parent is smaller than children*/
void heapify_sub(int index,int n){
    int l=2*index;
    int r=2*index+1;
    while(r<=n && (min_heap[index]->distance>min_heap[l]->distance || min_heap[index]->distance>min_heap[r]->distance)) {
        if(min_heap[l]->distance>min_heap[r]->distance){
            swap(r,index);
            index=index*2+1;
        }
        else{
            swap(l,index);
            index=index*2;
        }
        l=index*2;
        r=index*2+1;
    }
}
      /* heapify operation*/      
void heapify(int n){
    int h=log(n);
    h--;
    int index=pow(h);//index to first element in row
    int index_temp=index;
    int finali=index*2-1;//index to last element in row
    while(h>=0){
        while(index_temp<=finali) heapify_sub(index_temp++,n); //heapifies the row
        h--;
        index/=2;
        index_temp=index;
        finali=index*2-1;
    }
}

/* Prim starts*/
void prim(edge **listH,edge **listT,int n,int m){
    bool visited[MAXN];//Checks whether node is pulled out of heap or not
    node nodes[MAXN]; //array to store node info.
    for(int i=1;i<MAXN;i++){
        visited[i]=false;//everything is in heap right now
    }
    for(int i=1;i<MAXN;i++) {
        nodes[i].index=i;//i represents the destination vertex
        nodes[i].distance=INF; //this value is upadted as the graph is traversed
        nodes[i].parent=0; //parent represents the parent of node [i] in the Min. Spanning tree
        min_heap[i]=&nodes[i];//min_heap stores the pointers to the nodes so that change in node is represented in change in min_heap
    }
    int t=1;
    nodes[t].distance=0;//Starting from index 1
    for(int i=1;i<n;i++){
        delete_head();// t is pushed out of heap
        visited[t]=true;//t is vsited
        for(edge *j=listH[t];j!=NULL;j=j->ptr){
            if(visited[j->y]==false){
                    if(nodes[j->y].distance>j->distance){// if key less than distance , then distance is updated
                        nodes[j->y].distance=j->distance;
                        nodes[j->y].parent=t;
                        heapify(counte);//heapification brought in to bubble the heap value to its appropriate position
                    }
            }
        }
            int ij=0;
        cout<<min_heap[1]->parent<<" "<<min_heap[1]->index<<" "<<min_heap[1]->distance<<endl;//the node pushed out is formed a part of the tree
        t=min_heap[1]->index;
    }
}
void sabfree(edge **listH,int n){
    for(int i=1;i<=n;i++){
        for(edge *j=listH[i];j!=NULL;j=j->ptr) delete j;
    }
}
int main(){
  int n,m;
  label : cout<<"Welcome to Shortest Path!\nEnter nodes\n";
  cin>>n;
  if(cin.fail()){
    cout<<"Integers please\n";
    cin.clear();
    std::cin.ignore(256,'\n');
    goto label;
  }
  cout<<"Enter edges\n";
  cin>>m;
  if(cin.fail()){
     cout<<"Integers please\n";
     cin.clear();
     std::cin.ignore(256,'\n');
     goto label;
  }
  edge* listH[n+1];
  edge* listT[n+1];
  for(int i=1;i<=n;i++){
    listH[i]=NULL;
    listT[i]=NULL;
  }
  cout<<"Node1 , Node2 , Length : \n";
  for(int i=1;i<=m;i++){
    int x,y,weight;
    cin>>x>>y>>weight;
    if(x>n || y>n) {
        cout<<"Vertices out of range !\n";
        goto label;
    }
    if(cin.fail()){
      cout<<"Integers please\n";
      i--;
      cin.clear();
      std::cin.ignore(256,'\n');
      goto label;
    }//checks whether input is within range and integer or not
    insert(&listH[x],&listT[x],x,y,weight); //inserts into linked list of x
    insert(&listH[y],&listT[y],y,x,weight);//inserts into linkedl list of y
  }
  cout<<"The tree is :\nV1 | V2 | Distance\n";
    prim(listH,listT,n,m);//prim
  sabfree(listH,n);
}
