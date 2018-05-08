#include <iostream>
using namespace std;
struct node{// node actually stores the edge data , i.e source destination and weight
  int x;
  int y;
  int distance;
};

/* Implementation of merge sort*/
void merge(node* arr, int l, int m, int r){
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    node L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2){
        if (L[i].distance <= R[j].distance){
            arr[k] = L[i];
            i++;
        }
        else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort(node* arr, int l, int r){
    if (l < r){
        int m = l+(r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}
/*Implementation of union-find*/     
int find(int x,int *par){
  if(x!=par[x]) par[x]=find(par[x],par);
  return par[x];
}
void unione(int x,int y,int *par,int *rank){
  int fpar1=find(x,par);
  int fpar2=find(y,par);
  par[x]=fpar1;
  par[y]=fpar2;
  if(rank[fpar1]>rank[fpar2]) par[fpar2]=fpar1;
  else if(rank[fpar1]<rank[fpar2]) par[fpar1]=fpar2;
  else {
    par[fpar2]=fpar1;
    rank[fpar1]++;
  }
}

/*Kruskals sorts the edges in distance fashion and checks for cycles*/
void Kruskals(node *sorted,int n,int m){
  mergeSort(sorted,0,m-1); //edges are ow sorted
  int par[n+1];
  int rank[n+1];
  for(int i=1;i<=n;i++){
    par[i]=i;
    rank[i]=0;
  }
  cout<<"Min Span Tree :\nV1 | V2 | Weight\n";
  int count=1;
  for(int i=0;count<n;i++){
    int x=sorted[i].x;
    int y=sorted[i].y;
    if(find(sorted[i].x,par)==find(sorted[i].y,par))continue; //This implies that cycle if found since root is same
    unione(sorted[i].x,sorted[i].y,par,rank);
    cout<<x<<" "<<y<<" "<<sorted[i].distance<<"\n";
    count++;
  }
}

int main(){
  int n,m;
  label : cout<<"Welcome to Min-Spanning Tree!\nMake sure you enter a connected graph..\nEnter nodes\n";
  cin>>n;
  //Checking whether input is integer or not
  if(cin.fail()){
    cout<<"Integers please\n";
    cin.clear();
    std::cin.ignore(256,'\n');
    goto label;
  }
  cout<<"Enter edges\n";
  cin>>m; //edges
  if(cin.fail()){
     cout<<"Integers please\n";
     cin.clear();
     std::cin.ignore(256,'\n');
     goto label;
  }
  if(m<n-1){
    cout<<"Too few edges\n"; //tree has to have atleast n-1 edges
    goto label;
  }
  node toSort[m];
  cout<<"Node1 , Node2 , Length : \n";
  for(int i=1;i<=m;i++){
    int x,y,weight;
    cin>>x>>y>>weight;

    if(x>n || y>n) {
        cout<<"Vertices out of range !\n"; //Vertices have to be in range 1-n
        goto label;
    }
    if(x==y) {
        cout<<"Sorry , no self loops assignable\n";
        goto label;
    }
    if(cin.fail()){
      cout<<"Integers please\n"; //again checking on whether input is integer or not
      i--;
      cin.clear();
      std::cin.ignore(256,'\n');
      goto label;
    }
    toSort[i-1].x=x;
    toSort[i-1].y=y;
    toSort[i-1].distance=weight; //updating the struct toSort
  }
  Kruskals(toSort,n,m);//Calls Kruskal
}

  
