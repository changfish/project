#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

int main(int argc, char** argv) {
	list<int> v;
	int n,a;	//要輸入n個數(
	cin>>n;
	while(n){
		v.push_back(n);
		n--;
	}
	reverse(v.begin(),v.end()); //反轉 
	for(list<int>::iterator it=v.begin();it!=v.end();it++){
		cout<<*it<<"\t";
	}	
}
