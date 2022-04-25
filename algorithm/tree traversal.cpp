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

void pre(btree);
void in(btree);
void post(btree);


int main()
{	
	int A[8]={6,3,5,9,7,8,4,2};
	rootnode=NULL;
	cout<<"原陣列: ";
	for(int i=0;i<8;i++){
		add_node(A[i]);
		cout<<A[i]<<"\t";
	}
	cout<<"\n\n前序走訪preorder traversal：\n";
	pre(rootnode);
	cout<<"\n\n中序走訪inorder traversal：\n";
	in(rootnode);
	cout<<"\n\n中後序走訪postorder traversal：\n\n";
	post(rootnode);
	
}

void pre(btree ptr){	//前序走訪preorder traversal 
	if(ptr!=NULL){
		cout<<ptr->data<<"\t";
		pre(ptr->left);
		pre(ptr->right);
	}
}

void in(btree ptr){		//中序走訪inorder traversal 
	if(ptr!=NULL){
		pre(ptr->left);
		cout<<ptr->data<<"\t";
		pre(ptr->right);
	}
}

void post(btree ptr){			//後序走訪postorder traversal 
	if(ptr!=NULL){
		pre(ptr->left);
		pre(ptr->right);
		cout<<ptr->data<<"\t";
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
