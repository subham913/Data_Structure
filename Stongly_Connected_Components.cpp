#include<bits/stdc++.h>
using namespace std;
int cnt=0;
vector<int> scc;
vector<bool> visited;
vector< vector < int > > adjacency;
vector< vector < int > > tr_adj;
stack<int> Stack;




void DFS(int v)
{
	
	visited[v] = true;
	scc.push_back(v);
// 	cout << v << " ";

	for (int i = 0; i < tr_adj[v].size(); i++){
		int u=tr_adj[v][i];
		if (!visited[u])
			DFS(u);
	}
}





void stackfill(int v)
{
	visited[v] = true;


	for(int i = 0; i < adjacency[v].size()-1; ++i){
		int u=adjacency[v][i];
		if(!visited[u])
			stackfill(u);
	}

	 
	Stack.push(v);
}



void getSCCs(int n)
{
	


	for(int i = 0; i < n; i++){
		if(visited[i] == false)
			stackfill(i);
	}

	tr_adj.resize(n);
	for(int i=0;i<n;i++){
		for(int j=0;j<adjacency[i].size()-1;j++){
			int u=adjacency[i][j];
			tr_adj[u].push_back(i);
		}
	}

	for(int i = 0; i < n; i++)
		visited[i] = false;

	while (Stack.empty() == false)
	{
		int v = Stack.top();
		Stack.pop();

		if (visited[v] == false)
		{
			DFS(v);
			scc.push_back(-1);
			cnt++;

		}
	}
}


int main()
{   
	int n;
	cin>>n;
	vector<int> component(n);
	vector<int> minimum;
	for(int j=0;j<n;j++){
		visited.push_back(false);
	}
	int i=0;
	adjacency.resize(n);
	int marked[n];
	for(int j=0;j<n;j++){
	    marked[j]=0;
	}
	while(1){
		int a;
		cin>>a;
		if(i==n)break;
		if(a!=-1){
			adjacency[i].push_back(a);
		}
		else{
			adjacency[i].push_back(-1);
			i++;
		}
	}
	getSCCs(n);
	cout<<cnt<<endl;
	int k=0;
	int mini=1001;
	while(1){
	    if(k==scc.size())break;
	    if(scc[k]!=-1){
	        if(mini>scc[k])mini=scc[k];
	    }
	    else{
	        minimum.push_back(mini);
	        mini=1001;
	    }
	   k++; 
	}
	
	int l=0;
	int j=0;
	while(1){
	    if(l==scc.size())break;
	    if(scc[l]!=-1){
	        int u=scc[l];
	        component[u]=minimum[j];
	    }
	    else{
	        j++;
	        if(j==component.size())break;
	    }
	   l++; 
	}
	int arr[cnt][cnt];
	for(int i=0;i<cnt;i++){
	    for(int j=0;j<cnt;j++){
	        arr[i][j]=0;
	    }
	}
	int counter=0;
	while(1){
    	for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(marked[j]==0){
                    if(mini>component[j]){
                        mini=component[j];
                    }
                }
            }
            
            if(component[i]==mini){
                component[i]=counter;
                marked[i]=1;
            }
        }
        mini=1001;
        counter++;
        if(counter==cnt)break;
	}
	
	for(int i=0;i<n;i++){
	    for(int j=0;j<adjacency[i].size()-1;j++){
	        int u=adjacency[i][j];
	        if(component[i]!=component[u]){
	            arr[component[i]][component[u]]=1;
	        }
	    }
	}
	
	
	
	for(int i=0;i<cnt;i++){
        for(int j=0;j<cnt;j++)
	        if(arr[i][j]==1){
	            cout<<j<<" ";
	        }
	   cout<<-1<<endl;
	        
	}
    
    
	
// 	for(int j=0;j<n;j++){
// 	    cout<<component[j]<<endl;
// 	}    
	
	

	return 0;
}
