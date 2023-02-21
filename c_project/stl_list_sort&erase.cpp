#include <iostream>
#include <list>
using namespace std;

int main(int argc, char** argv) {
	list<int> v;
	int n,a;	//要輸入n個數(
	cin>>n;
	while(n--){
		cin>>a;
	v.push_back(a);
	}
	v.sort();		//升序排列 
	for(list<int>::iterator it=v.begin();it!=v.end();it++){
		if(!(*it%3))
			it=v.erase(it);
		cout<<*it<<"\t";
	}	
}
