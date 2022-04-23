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
	for(int i=0;i<K;i++){
		int s[2]={A[i],i};
		for(int j=i;j<K;j++){
			if(A[j]<s[0]){
				s[0]=A[j];
				s[1]=j;
			}	
		}
		int t=A[s[1]];
		A[s[1]]=A[i];
		A[i]=t;
	}
}
	 

