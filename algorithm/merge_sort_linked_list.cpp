#include <iostream>
using namespace std;

typedef class list{
	public:
		int val;
		list *next;
} node;

typedef node *link;

link c_list(int *A,int n){
	link head,ptr,newnode;
	head = new node;
	head->val=A[0];
	head->next = NULL;
	ptr=head;
	for(int i=1;i<n;i++){
		newnode = new node;
		newnode->val =A[i];
		newnode->next=NULL;
		ptr->next=newnode;
		ptr=ptr->next;
	}
	return head;
}

link merge_two_list(link l1,link l2){
	if(!l2) return l1;
	else if(!l1) return l2;
	else if(l1->val<l2->val) l1->next = merge_two_list(l1->next,l2);
	else l2->next =  merge_two_list(l2->next,l1);
}

link merge_sort(link head){
	if(!head||!head->next) return head;
	link slow=head,mid,fast=head->next;
	while(fast&&fast->next){
		slow = slow->next;
		fast = fast->next;
	}
	fast = fast->next;
	mid = slow->next;
	slow->next=NULL;
	link left = merge_sort(head);
	link right = merge_sort(mid);
	return merge_two_list(left,right);
}




int main(){
	int A[8]={2,5,4,6,8,1,7,3};
	link head = c_list(A,8);
	head = merge_sort(head);
	while(head){
		cout<<head->val<<" ";
		head=head->next;
	}
}
