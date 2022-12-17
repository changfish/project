#include <iostream>
#include <algorithm>
using namespace std;

const int size=7;
int A[size];
void sort(int l,int r){
	int t;
	if(l<r){
		int i=l+1,j=r;
		while(1){
			while(A[i]<A[l] && i<r)
				i++;
			while(A[j]>A[l] && j>l)
				j--;
			if(i>=j)	break;
			t=A[j];
			A[j]=A[i];
			A[i]=t;
		}
		t=A[j];
		A[j]=A[l];
		A[l]=t;
		sort(l,j-1);
		sort(j+1,r);
	}
	
}

int main(){
	for(int i=0;i<size;i++){
		cin>>A[i];
	}
	sort(0,size-1);
	for(int i=0;i<size;i++){
		cout<<A[i]<<" ";
	}
}
