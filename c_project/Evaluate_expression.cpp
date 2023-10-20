#include <iostream>
#include <vector>
#include <map>
using namespace std;

map<char,int> precedence;


int main() {
	precedence['+'] = precedence['-'] = 1;
	precedence['*'] = precedence['/'] = 2;
	vector<char> v;
	string s;
	cin>>s;
	int i=0;
	while(i<s.size()){
		while(s[i]==' ')
			i++; 
		if(s[i]>='0' && s[i]<='9')	cout<<s[i]<<" ";
		else if(!v.size())	v.push_back(s[i]);
		else if(precedence[s[i]]>precedence[*(v.end()-1)])	v.push_back(s[i]);
		else{
			cout<< *(v.end()-1) <<' ';
			v[v.size()-1] = s[i];
		}
		i++;
	}
	while(v.size()){
		cout<< *(v.end()-1) <<" ";
		v.pop_back();
	}
}
