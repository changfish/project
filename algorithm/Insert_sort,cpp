#include <iostream>
using namespace std;

void sort(int*,int);


int main() {
	int A[5]={9,8,7,6,5};
	sort(A,5);
	for(int i=0;i<5;i++)
		cout<<A[i]<<"\t";
}

void sort(int *A,int K){
	for(int i=1;i<K;i++){
		int t=A[i];
		int j=i-1;
		while(j>=0&&t<A[j]){
			A[j+1]=A[j];
			j--;
		}
		A[j+1]=t;	
	}
}
