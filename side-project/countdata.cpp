#include<iostream>
using namespace std;

int main(){
    int A[13]={0,31,28,31,30,31,30,31,31,30,31,30};
    int m[2],d[2],sum=0;
    for(int i=0;i<2;i++){
        cin>>m[i]>>d[i];
    }
    if(m[0]!=m[1]){
        for(int i=d[0];i<=A[m[0]];i++){
                cout<<m[0]<<"/"<<i<<"\t";
                sum++;
        }
        cout<<endl;
        for(int i=m[0]+1;i<m[1];i++){
            for(int j=1;j<=A[i];j++){
                cout<<i<<"/"<<j<<"\t";
                sum++;
            }
            cout<<endl;
        }
        for(int i=1;i<=d[1];i++){
            cout<<m[1]<<"/"<<i<<"\t";
            sum++;
        }
    }
    else{
        for(int i=d[0];i<=d[1];i++){
                cout<<m[0]<<"/"<<i<<"\t";
                sum++;
        }
    }
    cout<<"\n總天數"<<sum;
}  
