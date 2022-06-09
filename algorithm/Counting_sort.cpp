#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

int size=100;  //計數排列要知道數值範圍,size 

void sort(int *A,int *s,int n){		//counting sort
	for(int i=0;i<n;i++){
		s[A[i]]++;
	}
	int a=0;
	for(int i=0;i<size;i++){
		for(int j=0;j<s[i];j++){
			A[a]=i;
			a++;
		}
	}	 	
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n,s[size];
	while(cin>>n && n){
		int A[n];
		memset(A,0,sizeof(A));
		memset(s,0,sizeof(s));
		for(int i=0;i<n;i++){
			cin>>A[i];
		}
		sort(A,s,n);
		for(int i=0;i<n;i++){
			cout<<A[i];
			if(i!=n-1)
				cout<<" ";
		}
		cout<<endl;
	}
}
