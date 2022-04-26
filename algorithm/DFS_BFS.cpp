#include <iostream>
using namespace std;


class list{
	public:
		int val;
		class list *next;
};
typedef class list node;
typedef node *link;

void add_node(link,int); 
void dfs(link*,int,int *);

int main()
{	
	int n;
	cin>>n;	//成員總數，所以需要有n-1行來儲存成員個數
	int A[n][2],run[n];;
	link h[n],ptr;
	for(int i=0;i<n-1;i++){
		cin>>A[i][0]>>A[i][1];
		h[i]=new node;
		h[i]->next=NULL;
		h[i]->val=i;
		run[i]=0;		
	}
	h[n-1]=new node;		//輸入時沒建立第n個串列首 所以在這邊建立 
	h[n-1]->next=NULL;
	h[n-1]->val=n-1;
	run[n-1]=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<n-1;j++){
			if(A[j][0]==h[i]->val){
				add_node(h[i],A[j][1]);
				add_node(h[A[j][1]],A[j][0]);
			}
		}
	}
	for(int i=0;i<n;i++){
		ptr=h[i];
		while(ptr!=NULL){
			cout<<ptr->val<<" ";
			ptr=ptr->next;	
		}
		cout<<endl;
	}
	cout<<"dfs：\n";
	dfs(h,1,run);
}

void dfs(link *h,int current,int *run){
	link ptr;
	ptr=h[current];
	run[current]=1;
	cout<<current<<" ";
	ptr=h[current]->next;
	while(ptr!=NULL){
		if(!run[ptr->val])
			dfs(h,ptr->val,run);
		ptr=ptr->next;
	}
}

void add_node(link h,int val){
	link ptr,newnode;
	ptr=h;
	newnode =new node;
	newnode->next=NULL;
	newnode->val=val;
	if(ptr->next!=NULL){
		int s=0;		//判斷是否有重複的元素 
		while(ptr->next!=NULL){
			ptr=ptr->next;
			if(ptr->val==val){
				s++;
				break;
			}
		}
		if(!s)
			ptr->next=newnode;
	}else{
		if(!(ptr->val==val))
			ptr->next=newnode;
	}
}
