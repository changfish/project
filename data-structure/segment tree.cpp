#include <iostream>
using namespace std;


#define maxsize 1000
int tree[maxsize];

//segment tree
void build_tree(int *arr,int node,int start,int end){
	if(start == end)
		tree[node] = arr[start];
	else{
		int mid = (start + end)/2;
		int right_node = node*2+2;
		int left_node = node*2+1;
		build_tree(arr,left_node,start,mid);
		build_tree(arr,right_node,mid+1,end);
		tree[node] = tree[left_node] + tree[right_node];
	}
}

void updata_tree(int *arr,int node,int start,int end,int idx,int val){
		if(start == end){
			tree[node] = val;
			arr[idx] = val;
		}
		else{
			int mid = (start + end)/2;
			int right_node = node*2+2;
			int left_node = node*2+1;
			if(idx<=mid && idx>=start)
				updata_tree(arr,left_node,start,mid,idx,val);
			else
				updata_tree(arr,right_node,mid+1,end,idx,val);
			tree[node] = tree[right_node] + tree[left_node];
		}
}


int query_tree(int *arr,int node,int start,int end,int L,int R){
	if(L>end ||R<start)
		return 0;
	else{
		if(start>=L && end<=R)
			return tree[node];
		else{
			if(start == end)
				return tree[node];
		}
	}
	int mid = (start + end)/2;
	int right_node = node*2+2;
	int left_node = node*2+1;
	int left_sum = query_tree(arr,left_node,start,mid,L,R);
	int right_sum = query_tree(arr,right_node,mid+1,end,L,R);
	return left_sum + right_sum;
}



int main() {
	int size;
	cin>>size;	//the arr's size	(EX input 6 1 3 5 7 9 11) count of data is 6 
	int arr[size];
	for(int i=0;i<size;i++)	cin>>arr[i];	
	build_tree(arr,0,0,size-1);
	cout<<"before: ";
	for(int i=0;i<16;i++){
		cout<<tree[i]<<" ";
	}
	updata_tree(arr,0,0,size-1,5,12);
	cout<<"\n\nafter: ";
	for(int i=0;i<16;i++){
		cout<<tree[i]<<" ";
	}
	cout<<"\n\narr is: ";
	for(int i=0;i<size;i++){
		cout<<arr[i]<<" ";
	}

	cout<<"\n\nsum[4:5]: "<<query_tree(arr,0,0,size-1,4,5);
	
}
