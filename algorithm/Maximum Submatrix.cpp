#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int sub_max(vector<int> &v){
	int sz=v.size(),ans=0;
	for(int i=1;i<sz;i++){
		v[i]=max(v[i-1]+v[i],v[i]);
	}
	for(int i=0;i<sz;i++){
		ans=max(ans,v[i]);
	}
	return ans;
}


int main(){
	int m,n,ans=0;
	cin>>m>>n;
	vector< vector<int> > mat;
	for(int i=0;i<m;i++){
		vector<int> v(n,0);
		for(int j=0;j<n;j++)	cin>>v[j];
		mat.push_back(v);
	}
	for(int i=1;i<=m*(m-1)/2;i++){
		for(int j=0;j+i<=m;j++){
			vector<int> line(n,0);
			for(int k=0;k<i;k++){
				for(int a=0;a<n;a++)	line[a]+=mat[j+k][a];
			}
			ans = max(ans,sub_max(line));
		}
	}
	cout<<ans;
}

