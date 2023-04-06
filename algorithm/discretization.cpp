#include <iostream>
#include <vector>
using namespace std;


int main(){
	int idx;
	vector<int> v(10),b(10);	//create a vector of size 10;
	for(int i=0;i<10;i++){
		v[i] = 2*i+1;	//1 3 5 7 9 11 13 15 17 19
	}
	b = v;	//b was used for discretization.
	cout<<*b.begin()<<" ";			//1
	cout<<*(b.end()-1)<<" ";		//19
	cout<<b.end()-b.begin()<<" ";	//10
	for(int i=0;i<10;i++){
		b[i] = lower_bound(b.begin(),b.end(),v[i]) - b.begin()+1;	//discretization
	}
	cout<<endl;
	for(int i=0;i<10;i++){
		cout<<b[i]<<" ";	//1 2 3 4 5 6 7 8 9 10
	}
}
