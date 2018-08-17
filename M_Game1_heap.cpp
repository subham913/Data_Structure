
#include<bits/stdc++.h>
using namespace std;
//vector<string> words;
void swap(vector<string> &words,int i,int j){
	string temp=words[j];
	words[j]=words[i];
	words[i]=temp;

}
void make_heap(vector<string> &words){
		int l = words.size();
		for(int k=l-1;k>1;k/=2){
		    int flag=0;
			if(k/2>=1){
				if(words[k]<words[k/2]){
					swap(words,k,k/2);
				}
				else{
					flag=1;
				}
			}
			else{
				break;
			}
			if(flag==1){
			    break;
			}
		}
}
void heapify(vector<string> &words){
	int i=1;
	int left=2;
	int right=3;
	int length=words.size();
		while(left<length){
			if(right<length){
				if(words[i]<=words[left] && words[i]<=words[right]){
				return;
				}
				else if(words[right]>=words[left]){
					swap(words,i,left);
					i=left;
				}
				else if(words[left]>=words[right]){
					swap(words,i,right);
					i=right;
				}
			}
			else{
				if(words[i]>=words[left]){
					swap(words,i,left);
					i=left;
				}
				return;
			}
			left=2*i;
			right=left+1;
		}
}
int main(){
	int q;
	cin>>q;
	vector<string> words;
	words.push_back("-1");
	for(int i=0;i<q;i++){
		string command;
		cin>>command;
		if(command=="learn"){
		    string value;
		    cin>>value;
		    words.push_back(value);
		    make_heap(words);
		  //  for(int i=0;i<words.size();i++){
		  //      cout<<"Words are"<<words[i]<<endl;
		  //  }
			// words.push_back(value);
			// heapify(words);
		}
		else if(command=="reportsmallest"){
			cout<<words[1]<<endl;
		}
		else if(command=="forgetsmallest"){
			cout<<words[1]<<endl;
			int length=words.size();
			words[1]=words[length-1];
			words.pop_back();
			heapify(words);
		}
	}
	return 0;
}