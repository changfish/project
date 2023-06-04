#include <iostream>
using namespace std;
#include <map>



int main(){
	int a,N=0;
	string b;
	float sum=0;
	map<string,float> g;
	g["D"] = 1;
	g["C-"] = 1.7;
	g["C"] = 2;
	g["C+"] = 2.3;
	g["B-"] = 2.7;
	g["B"] = 3;
	g["B+"] = 3.3;
	g["A-"] = 3.7;
	g["A"] = 4;
	g["A+"] = 4.3;
	while(cin>>a>>b){
		N+=a;
		sum+=a*g[b];
	}
	cout<<sum/N<<endl;
}
