#include<bits/stdc++.h>
using namespace std;
#define infi 0x3f3f3f3f
vector< vector < pair<int,int> > > adjacency;
vector<int> key;
priority_queue< pair< int,int >, vector < pair< int,int > > , greater< pair< int,int > > > pqueue;

void Relax(int u,int v,int weight){
	if(key[v]>key[u]+weight){
		key[v]=key[u]+weight;
		pqueue.push(make_pair(key[v],v));
	}
}


int main(){
	int n,m;
	cin>>n;
	cin>>m;
	adjacency.resize(n);
	for(int i=0;i<m;i++){
		int u,v,w;
		cin>>u;
		cin>>v;
		cin>>w;
		adjacency[u].push_back(make_pair(v,w));
		adjacency[v].push_back(make_pair(u,w));
	}
	for(int i=0;i<n;i++){
		key.push_back(infi);
	}
	pqueue.push(make_pair(0,0));
	key[0]=0;
	while(pqueue.empty()==0){
		int u=pqueue.top().second;
		pqueue.pop();
		for(int i=0;i<adjacency[u].size();i++){
			int v=adjacency[u][i].first;
			int weight=adjacency[u][i].second;
			Relax(u,v,weight);
		}
	}
   // cout<<"Hi";
	if(key[n-1]==infi){
		cout<<"-1";
	}
	else{
		cout<<key[n-1];
	}
    //cout<<"done";
	return 0;

}