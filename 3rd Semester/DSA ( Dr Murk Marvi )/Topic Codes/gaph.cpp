#include<iostream>
#include<list>
#include<vector>
#include<stack>
using namespace std;
void DFSHelper(int vertex, vector<list<int> >&AdjList, vector<bool>& visited){
	list<int>::iterator it;
	cout<<vertex<<" ";
	visited[vertex] = 1;
	for(it=AdjList[vertex].begin(); it!=AdjList[vertex].end(); it++)
		if(!visited[*it])
			DFSHelper(*it, AdjList, visited);
}

void DFS(vector<list<int> >&AdjList){
	vector<bool> visited(AdjList.size(), false);
	for(int i=0; i<AdjList.size(); i++){
		if(!visited[i])
			DFSHelper(i, AdjList, visited);
	}
	cout<<endl;
}

bool CycleDHelper(int vertex, vector<list<int> >&AdjList, vector<bool>& visited, vector<bool>& additional){
	list<int>::iterator it;
	visited[vertex] = true;
	additional[vertex] = true;
	for(it=AdjList[vertex].begin(); it!=AdjList[vertex].end(); it++){
		if(!visited[*it] &&	CycleDHelper(*it, AdjList, visited, additional))
			return true;
		else if(additional[*it])
			return true;
			}
	additional[vertex]=false;
	return false;
}

bool CycleD(vector<list<int> >&AdjList){
	vector<bool> visited(AdjList.size(), false);
	vector<bool> additional(AdjList.size(), false);
	for(int i=0; i<AdjList.size(); i++){
		if( !visited[i] && CycleDHelper(i, AdjList, visited, additional)) {
			cout << "Cycle Detected: " << endl ;
			return true ;
		}
	}
	cout<<"No Cycle"<<endl;
	return false;
}


bool CycleHelper(int vertex, int parent, vector<list<int> >&AdjList, vector<bool>& visited){
	list<int>::iterator it;
	visited[vertex] = 1;
	for(it=AdjList[vertex].begin(); it!=AdjList[vertex].end(); it++){
		if(!visited[*it]){
			if( CycleHelper(*it, vertex, AdjList, visited) )
				return true;
				}
		else if(*it != parent)
			return true;
		}
	return 0;
}
void Cycle(vector<list<int> >&AdjList){
	vector<bool> visited(AdjList.size(), false);
	for(int i=0; i<AdjList.size(); i++){
		if(!visited[i]) {
			if(CycleHelper(i, -1, AdjList, visited)){
				cout<<"Cycle Detected!"<<endl;
				return;
			}
			CycleHelper(i, -1, AdjList, visited);
		}
	}
	cout<<"No Cycle"<<endl;
}

void Helper(int vertex, vector<list<int> >& AdjList, vector<bool>& visited, stack<int>& st){
	visited[vertex]= true;
	list<int>::iterator it;
	for(it=AdjList[vertex].begin(); it!=AdjList[vertex].end(); it++){
		if(!visited[*it])
			Helper(*it, AdjList, visited, st);
	}
	st.push(vertex);
}
void TopologicalSort(vector<list<int> > AdjList){
	vector<bool> visited(AdjList.size(), false);
	stack<int> st;
	if(!CycleD(AdjList)){
		for(int i=0;i<AdjList.size();i++){
			if(!visited[i])
				Helper(i, AdjList, visited, st);
		}
//		cout<<st.size();
		while(!st.empty()){
			cout<<st.top()<<" ";
			st.pop();
		}
		cout<<endl;
	}
}


void AddNode(vector<list<int> >&AdjList){
	AdjList.push_back(list<int>());
}
void AddEdge(int u, int v, vector<list<int> >&AdjList, bool directed=1){
	AdjList[u].push_back(v);
	if(!directed)
		AdjList[v].push_back(u);
}
void display(vector<list<int> > AdjList){
	list<int>::iterator it;
	for(int i=0; i<AdjList.size(); i++){
		cout<<i;
		for(it=AdjList[i].begin(); it!=AdjList[i].end(); it++){
				cout<<" ---> "<<*it;
		}
		cout<<endl;
	}
}
int main(){
	vector<list<int> > AdjList;
	for(int i=0; i<5; i++)
		AddNode(AdjList);
	AddEdge(0,1, AdjList);
	AddEdge(0,2, AdjList);
	AddEdge(2,1, AdjList);
	AddEdge(3,4, AdjList);
	AddEdge(2,4, AdjList);
	AddEdge(3,1, AdjList);
	display(AdjList);
	DFS(AdjList);
//	CycleD(AdjList);
	TopologicalSort(AdjList);
}
