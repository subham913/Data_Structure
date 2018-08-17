#include<bits/stdc++.h>
#include<string>
using namespace std;

typedef struct node{
    string info;
	int ht;
	int left_tree_size;
	int right_tree_size;
	struct node *left;
	struct node *right;
}Node;

Node* NewNode(string word){
	Node *temp=(Node *)malloc(sizeof(Node));
	(temp->info) = word;
	temp->ht=0;
	(temp->left)=NULL;
	(temp->right)=NULL;
	(temp->left_tree_size)=0;
	(temp->right_tree_size)=0;
	return temp;
}

int height(Node* T){
	int lh,rh;
	if(T==NULL)
		return 0;
	if(T->left==NULL)
		lh=0;
	else
		lh=1+T->left->ht;
	if(T->right==NULL)
		rh=0;
	else
		rh=1+T->right->ht;
	if(lh>rh)
		return lh;
	return rh;
}

int bf(Node* T){
	int lh,rh;
	if(T==NULL)
		return 0;
	if(T->left==NULL)
		lh=0;
	else
		lh=1+T->left->ht;
	if(T->right==NULL)
		rh=0;
	else
		rh=1+T->right->ht;
	return (lh-rh);
}

Node* rotateLeft(Node* x){
	Node *y;
	y=x->right;
	x->right=y->left;
	y->left=x;
	x->right_tree_size=y->left_tree_size;
	y->left_tree_size=1+x->left_tree_size+x->right_tree_size;
	x->ht=height(x);
	y->ht=height(y);
	return(y);
}

Node* LL_rotation(Node* T){
	T=rotateLeft(T);
	return T;
}
Node* rotateRight(Node* x){
	Node *y;
	y=x->left;
	x->left=y->right;
	y->right=x;
// 	if(y->right==NULL);{
// 	    y->right_tree_size=0;
// 	}
	x->left_tree_size=y->right_tree_size;
// 	if(x->right==NULL){
// 	    x->right_tree_size=0;
// 	}
	y->right_tree_size=1+x->left_tree_size+x->right_tree_size;
	x->ht=height(x);
	y->ht=height(y);
// 	cout<<y->ht<<endl;
	return(y);
}

Node* RR_rotation(Node* T){
	T=rotateRight(T);
	return T;
}

Node* LR_rotation(Node* T){
	Node *temp;
	temp=rotateLeft(T->left);
	T->left=temp;
	T=rotateRight(T);
	return T;
}

Node* RL_rotation(Node* T){
	T->right=rotateRight(T->right);
	T=rotateLeft(T);
	return T;
}
Node* insert(Node* T,string x){
	if(T==NULL){
	    //cout<<"Hi insertNULL"<<endl;
	    T=NewNode(x);
		return T;
	}
	else if(x > T->info){
		(T->right_tree_size)+=1;
		T->right=insert(T->right,x);
		 //cout<<"Hi insertRight"<<endl;
		if(bf(T)==-2){
			if(x>T->right->info)
				T=LL_rotation(T);
			else
				T=RL_rotation(T);
		}
	}
	else if(x < T->info){
	    //cout<<"Hi insertLeft"<<endl;
		(T->left_tree_size)+=1;
		T->left=insert(T->left,x);
		//cout<<bf(T)<<endl;
		if(bf(T)==2){
			if(x<T->left->info)
				T=RR_rotation(T);
			else
				T=LR_rotation(T);
		}
	}
	T->ht=height(T);
	//cout<<T->ht<<endl;
	return T;
}

int position(Node* T,string x){
	int cnt=1;
    if(T==NULL){
        //cout<<"Hi1"<<endl;
        return 0;
    }
	while(T!=NULL){
		if(x>T->info){
			cnt+=1+T->left_tree_size;
		//	 cout<<"Hi2"<<endl;
			T=T->right;
		}
		else if(x<T->info){
		//     cout<<"Hi3"<<endl;
			T=T->left;			
		}
        else{
         //   cout<<"Hi Dude"<<endl;
		    return (cnt+T->left_tree_size);
        }
    }	
}

Node* forget(Node *T,string word){
    if(T==NULL) return T;
    
	if(word < T->info){
	    T->left_tree_size-=1;
		T->left=forget(T->left,word);
	}
	else if(word>T->info){
		T->right_tree_size-=1;
		T->right=forget(T->right,word);
	}
	else{
// 		if (T->left==NULL && T->right==NULL)
// 		    {
// 		        T=NULL;
// 		       return NULL; 
// 		    }
		if(T->left==NULL){
			Node *temp;
			temp=T->right;
			T=NULL;
			return temp;
		}
		else if(T->right==NULL){
			Node *temp;
			temp=T->left;
			T=NULL;
			return temp;
		}
		else{
			Node *succ=T->right;
			while(succ->left!=NULL){
				succ=succ->left;
			}
			T->info=succ->info;
			
			T->right=forget(T->right,succ->info);
		}
	}
	T->ht=height(T);
	if(bf(T)>1 && bf(T->left)>=0){
		return RR_rotation(T);
	}
	else if(bf(T)>1 && bf(T->left)<0){
		return LR_rotation(T);
	}
	else if(bf(T)<-1 && bf(T->right)<=0){
		return LL_rotation(T);
	}
	else if(bf(T) && bf(T->right)>0){
		return RL_rotation(T);
	}
	
	return T;
}


int main(){
	int q;
	cin>>q;
	Node *node=NULL;
	for (int i = 0; i < q; ++i)
	{
		string command;
		string word;
		cin>>command;
		cin>>word;
		if(command=="learn"){
		    if(!node)node=NewNode(word);
		    else
		    node=insert(node,word);
		    //cout<<"Hi"<<endl;
		}
		else if(command=="forget"){
			int word_rank=position(node,word);
			cout<<word_rank<<endl;
			node=forget(node,word);
        }
		else {
		    //cout<<"hi"<<endl;
			int word_rank=position(node,word);
			cout<<word_rank<<endl;
		}
	}
	// while(!(node->left)){
	// 	cout<<node->left->info<<endl;
	// 	node=node->left;
	// }
	return 0;
}
#include<bits/stdc++.h>
#include<string>
using namespace std;

typedef struct node{
    string info;
	int ht;
	int left_tree_size;
	int right_tree_size;
	struct node *left;
	struct node *right;
}Node;

Node* NewNode(string word){
	Node *temp=(Node *)malloc(sizeof(Node));
	(temp->info) = word;
	temp->ht=0;
	(temp->left)=NULL;
	(temp->right)=NULL;
	(temp->left_tree_size)=0;
	(temp->right_tree_size)=0;
	return temp;
}

int height(Node* T){
	int lh,rh;
	if(T==NULL)
		return 0;
	if(T->left==NULL)
		lh=0;
	else
		lh=1+T->left->ht;
	if(T->right==NULL)
		rh=0;
	else
		rh=1+T->right->ht;
	if(lh>rh)
		return lh;
	return rh;
}

int bf(Node* T){
	int lh,rh;
	if(T==NULL)
		return 0;
	if(T->left==NULL)
		lh=0;
	else
		lh=1+T->left->ht;
	if(T->right==NULL)
		rh=0;
	else
		rh=1+T->right->ht;
	return (lh-rh);
}

Node* rotateLeft(Node* x){
	Node *y;
	y=x->right;
	x->right=y->left;
	y->left=x;

	x->right_tree_size=(x->right==NULL)?0:x->right->right_tree_size+x->right->left_tree_size+1;
	x->left_tree_size=(x->left==NULL)?0:x->left->right_tree_size+x->left->left_tree_size+1;
	y->right_tree_size=(y->right==NULL)?0:y->right->right_tree_size+y->right->left_tree_size+1;
	y->left_tree_size=(y->left==NULL)?0:y->left->right_tree_size+y->left->left_tree_size+1;
	x->ht=height(x);
	y->ht=height(y);
	return(y);
}

Node* LL_rotation(Node* T){
	T=rotateLeft(T);
	return T;
}
Node* rotateRight(Node* x){
	Node *y;
	y=x->left;
	x->left=y->right;
	y->right=x;
	
	x->right_tree_size=(x->right==NULL)?0:x->right->right_tree_size+x->right->left_tree_size+1;
	x->left_tree_size=(x->left==NULL)?0:x->left->right_tree_size+x->left->left_tree_size+1;
	y->right_tree_size=(y->right==NULL)?0:y->right->right_tree_size+y->right->left_tree_size+1;
	y->left_tree_size=(y->left==NULL)?0:y->left->right_tree_size+y->left->left_tree_size+1;
	x->ht=height(x);
	y->ht=height(y);
// 	cout<<y->ht<<endl;
	return(y);
}

Node* RR_rotation(Node* T){
	T=rotateRight(T);
	return T;
}

Node* LR_rotation(Node* T){
	Node *temp;
	temp=rotateLeft(T->left);
	T->left=temp;
	T=rotateRight(T);
	return T;
}

Node* RL_rotation(Node* T){
	T->right=rotateRight(T->right);
	T=rotateLeft(T);
	return T;
}
Node* insert(Node* T,string x){
	if(T==NULL){
	    //cout<<"Hi insertNULL"<<endl;
	    T=NewNode(x);
		return T;
	}
	else if(x > T->info){
		T->right=insert(T->right,x);
		 //cout<<"Hi insertRight"<<endl;
		if(bf(T)==-2){
			if(x>T->right->info)
				T=LL_rotation(T);
			else
				T=RL_rotation(T);
		}
	}
	else if(x < T->info){
	    //cout<<"Hi insertLeft"<<endl;
		T->left=insert(T->left,x);
		//cout<<bf(T)<<endl;
		if(bf(T)==2){
			if(x<T->left->info)
				T=RR_rotation(T);
			else
				T=LR_rotation(T);
		}
	}
	T->right_tree_size=(T->right==NULL)?0:T->right->right_tree_size+T->right->left_tree_size+1;
	T->left_tree_size=(T->left==NULL)?0:T->left->right_tree_size+T->left->left_tree_size+1;
	T->ht=height(T);
	//cout<<T->ht<<endl;
	return T;
}

int position(Node* T,string x){
	int cnt=1;
    if(T==NULL){
        //cout<<"Hi1"<<endl;
        return 0;
    }
	while(T!=NULL){
		if(x>T->info){
			cnt+=1+T->left_tree_size;
		//	 cout<<"Hi2"<<endl;
			T=T->right;
		}
		else if(x<T->info){
		//     cout<<"Hi3"<<endl;
			T=T->left;			
		}
        else{
         //   cout<<"Hi Dude"<<endl;
		    return (cnt+T->left_tree_size);
        }
    }	
}

Node* forget(Node *T,string word){
    if(T==NULL) return T;
    
	if(word < T->info){
		T->left=forget(T->left,word);
	}
	else if(word>T->info){
		T->right=forget(T->right,word);
	}
	else{
// 		if (T->left==NULL && T->right==NULL)
// 		    {
// 		        T=NULL;
// 		       return NULL; 
// 		    }
		if(T->left==NULL){
			Node *temp;
			temp=T->right;
			T=NULL;
			return temp;
		}
		else if(T->right==NULL){
			Node *temp;
			temp=T->left;
			T=NULL;
			return temp;
		}
		else{
			Node *succ=T->right;
			while(succ->left!=NULL){
				succ=succ->left;
			}
			T->info=succ->info;
			
			T->right=forget(T->right,succ->info);
		}
	}

	if(bf(T)>1 && bf(T->left)>=0){
		return RR_rotation(T);
	}
	else if(bf(T)>1 && bf(T->left)<0){
		return LR_rotation(T);
	}
	else if(bf(T)<-1 && bf(T->right)<=0){
		return LL_rotation(T);
	}
	else if(bf(T)<-1 && bf(T->right)>0){
		return RL_rotation(T);
	}
	T->right_tree_size=(T->right==NULL)?0:T->right->right_tree_size+T->right->left_tree_size+1;
	T->left_tree_size=(T->left==NULL)?0:T->left->right_tree_size+T->left->left_tree_size+1;
	T->ht=height(T);	
	return T;
}


int main(){
	int q;
	cin>>q;
	Node *node=NULL;
	for (int i = 0; i < q; ++i)
	{
		string command;
		string word;
		cin>>command;
		cin>>word;
		if(command=="learn"){
		    if(!node)node=NewNode(word);
		    else
		    node=insert(node,word);
		    //cout<<"Hi"<<endl;
		}
		else if(command=="forget"){
			int word_rank=position(node,word);
			cout<<word_rank<<endl;
			node=forget(node,word);
        }
		else {
		    //cout<<"hi"<<endl;
			int word_rank=position(node,word);
			cout<<word_rank<<endl;
		}
	}
	// while(!(node->left)){
	// 	cout<<node->left->info<<endl;
	// 	node=node->left;
	// }
	return 0;
}

