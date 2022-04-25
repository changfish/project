#include <iostream>
using namespace std;

class list{
	public:
		int data;
		class list *next;
};
typedef class list node;
typedef node *link;

int main()
{	
	link newnode,ptr,delptr;
	delptr=new node;
	cin>>delptr->data;
	ptr=delptr;
	for(int i=1;i<5;i++){
		newnode = new node;
		cin>>newnode->data;
		ptr->next=newnode;
		newnode->next=NULL;
		ptr=newnode;
	}
	ptr=delptr;
	while(ptr!=NULL){
		cout<<ptr->data<<"\t";
		ptr=ptr->next; 
	}
}
