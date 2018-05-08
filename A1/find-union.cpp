#include <iostream>
using namespace std;

int find(int x,int *par){ //recursively goes to the root of union tree and returns the root
  if(x==par[x]) return x;
  else return find(par[x],par);
}


void unione(int x,int y,int *par,int *rank){
  int fpar1=find(x,par); //root of x
  int fpar2=find(y,par); //root of y
  par[x]=fpar1;
  par[y]=fpar2;
  if(rank[fpar1]>rank[fpar2]) par[fpar2]=fpar1; //joining tree2 as subtree of tree 1 as rank of tree is more
  else if(rank[fpar1]<rank[fpar2]) par[fpar1]=fpar2;
  else {
    par[fpar2]=fpar1; //if ranks are equal then height of tree is increased.
    rank[fpar1]++;
  }
}



int main(){
  int n,m;
  cin>>n;
  int par[n+1];
  int rank[n+1];
  for(int i=1;i<=n;i++){
    par[i]=i; //par[i]=i is used as the finish of recursion / implies that this node i is parent of itself
    rank[i]=0;//used for evauating the height of the tree
  }
  while(1){
    int y;
    cin>>y;
    if(y==1){
      int x,y;
      cin>>x>>y;
      unione(x,y,par,rank);
    }
    else {
      int x;
      cin>>x;
      cout<<find(x,par)<<endl;
    }
  }
  
  /*for(int i=1;i<=m;i++) {
    int x,y;
    cin>>x>>y;
    if(find(x,par)==find(y,par)){
        cout<<"Cycle Detected\n";
        continue;
    }
    unione(x,y,par,rank);
  }*/
}

