#include <iostream>
using namespace std;
#define INF   1000000000//INFINTE
#define MAXN  100001 //Max size of min_heap
int min_heap[MAXN];
int counte;
void swap(int a,int b){ //swaps two values in min_heap
	int t=min_heap[a];
	min_heap[a]=min_heap[b];
	min_heap[b]=t;
}
void print(){
	for(int i=1;i<=counte;i++) cout<<min_heap[i]<<" ";
	if(counte!=0) cout<<"\n";
  else cout<<"Heap Empty!\n";
}
void insert(bool* flag){  //insert in heap
	cout<<"Enter value : ";
	int y;
	cin>>y;
	counte++; //index where element is to be inserted , also number of elements in heap
	int index=counte;
  if(counte==MAXN) {
    counte--;
    *flag=true;
    return ;
  }
	min_heap[index]=y; //Last value of heap is given as y , now we will organise the heap
	int ind_par=index/2; //index of parent
	while(ind_par>=1){//Recursion till either parent becomes less than child or we reach the root
		if(min_heap[ind_par]>min_heap[index]){//swaps parent and child
			swap(ind_par,index);
			index/=2;
			ind_par=index/2;
		}
   else break;
	}
}
int find_top(bool* flag){//returns the element at the top  i.e. the least element
	if(counte==0) {
    *flag=true;
    return 0;
  }
  else return min_heap[1];
}
void delete_head(){
  if(counte>0) counte--;
  else return ;
  min_heap[1]=min_heap[counte+1]; //last element is brought up to root position and recursively brought down
  min_heap[counte+1]=INF;//sigifies deletion of counte+1 element as now control is given to root
	int i=1;
	/*checking whether parent is greater than either of the children and swaps if its the case*/
  while(2*i+1<=counte && (min_heap[i]>min_heap[2*i] || min_heap[i]>min_heap[2*i+1])){ 
		if(min_heap[2*i]<min_heap[2*i+1]){
			swap(i,2*i);
			i*=2;
		}
    else {
			swap(i,2*i+1);
			i=i*2+1;
		}
	}
}

int main(){
  for(int i=0;i<MAXN;i++) min_heap[i]=INF;
	cout<<"Enter :\n1.Insert\n2.Peek\n3.Delete\n4.Exit\n";
	int x;
	cin>>x;
	while(x!=4){
    bool flag=false;
		if(x==1){
      insert(&flag);
      if(flag==true) cout<<"Sorry,heap full\n";
    }
		else if(x==2){
      int t=find_top(&flag);
      if(flag==false) cout<<"Top : "<<t<<"\n";
    }
    else if(x==3){
      delete_head();
		}
		else break;
		label:print();
		cout<<"Enter choice : ";
		cin>>x;
	}
}

				


	
