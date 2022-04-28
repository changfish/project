#include <iostream>
#include <vector>

using namespace std;


int main() {
	int n,x,y;		//n為spot數 
	cin>>n;
	vector<int> tree[n];	//tree一定要從0~n 
	for(int i=0;i<n-1;i++){//要執行n-1次 因為只有n-1個邊 
		cin>>x>>y;
		tree[y].push_back(x);	//y為x的孩子 
	}
	for(int i=0;i<n;i++){
		if(tree[i].size()==0){
			cout<<"樹根為："<<i;
		}
	}	
}

