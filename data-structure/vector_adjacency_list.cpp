#include <iostream>
#include <vector>
using namespace std;

int main() {
   int n;
   cin>>n;
   int A[n][2];
   vector<int> tree[n];
   for(int i=0;i<n-1;i++){
   		cin>>A[i][0]>>A[i][1];
   		tree[i].push_back(i);
   }
   tree[n-1].push_back(n-1);
   for(int i=0;i<n-1;i++){
		tree[A[i][0]].push_back(A[i][1]);
		tree[A[i][1]].push_back(A[i][0]);
   }
	for(int i=0;i<n;i++){
		for(vector<int>::iterator it=tree[i].begin();it<tree[i].end();it++){
	   		cout<<*it<<" ";
	   }
	   cout<<"\n";
	}
}
