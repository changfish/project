#include <iostream>
using namespace std;

class tree{
	public:
		int data;
		class tree *left,*right;
};
typedef class tree node;
typedef node *btree;

btree rootnode; //在全域定義根節點 

void add_node(int);

int main()
{	
	int A[8]={6,3,5,9,7,8,4,2};
	rootnode=NULL;
	for(int i=0;i<8;i++){
		add_node(A[i]);
	}
	btree newnode = rootnode;
	while(newnode!=NULL){
		cout<<newnode->data;
		newnode=newnode->left;
		cout<<endl;
	}
	
}

void add_node(int value){
	int flag=0;		//紀錄是否要插入新的節點 
	btree newnode,currentnode;
	newnode =new node;
	newnode->data=value;
	newnode->left=NULL;
	newnode->right=NULL;
	if(rootnode==NULL){
		rootnode=newnode;
	}
	else{
		currentnode=rootnode;
		while(!flag){
			if(value<currentnode->data){//往左子樹 
				if(currentnode->left==NULL){
					currentnode->left=newnode;
					flag=1;
				}else{
					currentnode=currentnode->left;
				}
			}else{//往右子樹 
				if(currentnode->right==NULL){
					currentnode->right=newnode;
					flag=1;
				}else{
					currentnode=currentnode->right;
				}
			}
		}	
	}
}

