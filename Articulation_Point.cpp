#include<bits/stdc++.h>
using namespace std;
vector< vector < int > > adjacency;
int cnt=0;
int children=0;
vector<int> dfn;
vector<int> low;

// vector<int> previous;

void biconnected(int ch,int v,int u,int AP[]){
	cnt++;
	dfn[v]=cnt;
	low[v]=cnt;
	for(int i=0;i<adjacency[v].size();i++){
		int w=adjacency[v][i];
		if(dfn[w]==0){
		    // previous[w]=v;
			biconnected(0,w,v,AP);
			low[v]=min(low[v],low[w]);
			if(dfn[v]<=low[w]){
			    AP[v]=1;
			}
			if(ch==1)children++;
		}
		else if(dfn[w]<dfn[v] && w!=u){
			low[v]=min(low[v],dfn[w]);
		}
	}
}
int main(){
	int m,n;
	cin>>n>>m;
	adjacency.resize(n);
	low.resize(n);
	int AP[n];
	for(int j=0;j<n;j++){
	  AP[j]=0;
	}
	for(int j=0;j<n;j++){
	  dfn.push_back(0);
	}
	for(int i=0;i<m;i++){
		int a,b;
		cin>>a>>b;
		adjacency[a].push_back(b);
		adjacency[b].push_back(a);
	}
	for(int j=0;j<n;j++){
		if(dfn[j]==0){
			biconnected(1,j,0,AP);
			if(children>1)AP[j]=1;
			else AP[j]=0;
		}
		children=0;
	}
	for(int i=0;i<n;i++){
	    if(AP[i]==1)
	    cout<<i<<endl;
	}
	return 0;

}

