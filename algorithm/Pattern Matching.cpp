#include <iostream>
#include <vector>
using namespace std;


vector<int> fail(string pat){
	vector<int> output(pat.size());
	output[0] = -1;
	for(int i=1;i<pat.size();i++){
		if(pat[i] == pat[output[i-1]+1])	output[i] = output[i-1]+1;
		else output[i] = -1;
	}
	return output;
}

int matching(string s,string pat){
	vector<int> failure = fail(pat);
	int i=0,j=0;
	while(i<s.size()){
		while(s[i]!=pat[j])	i++;
		while(j<pat.size() && s[i]==pat[j]){
			i++;
			j++;
		}
		if(j==pat.size())	return 1;	//matching successful
		j = failure[j-1];
	}
	return 0;	//no matched
}

int main() {
	int result = matching("bbabcabcaa(abcabcacab)","abcabcacab");
	cout<< result;
}
