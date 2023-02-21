#include <iostream>
#include <vector>

using namespace std;


int main() {
	int n;
	vector<int> t;
	while(cin>>n){
		while(n>0){
			t.insert(t.begin(),n%2);
			n/=2;
		}
		for(vector<int>::iterator it=t.begin();it<t.end();it++){
			cout<<*it;
		}
		cout<<endl;
		t.clear();
	}
}

