#include <iostream>
#include <algorithm>
using namespace std;

string mx(string s1,string s2){
	if(s1.size()>s2.size())	return s1;
	else return s2;
}

int main(){
	string s1,s2;
	cin>>s1>>s2;
	string dp[s1.size()][s2.size()];
	for(int i=0;i<s1.size();i++){
		if(s1[i]==s2[0]) dp[i][0]=s1[i];
		else dp[i][0]="";
	}
	for(int i=0;i<s2.size();i++){
		if(s1[0]==s2[i]) dp[0][i]=s2[i];
		else dp[0][i]="";
	}
	for(int i=1;i<s1.size();i++){
		for(int j=1;j<s2.size();j++){
			if(s1[i]==s2[j])	dp[i][j]=dp[i-1][j-1]+s1[i];
			else dp[i][j] = mx(dp[i-1][j],dp[i][j-1]);
		}
	}
	for(int i=0;i<s1.size();i++){
		for(int j=0;j<s2.size();j++){
			cout<<dp[i][j]<<"\t";
		}
		cout<<endl;
	}
	cout<<dp[s1.size()-1][s2.size()-1];
}

