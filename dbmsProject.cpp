#include<bits/stdc++.h>
using namespace std;
struct transac{
char first;
int  second;
char third;
};

class Graph
{
    int V;
    list<int> *adj;
    bool isCyclicUtil(int v, bool visited[], bool *rs);
public:
    Graph(int V);
    void addEdge(int v, int w);
    bool isCyclic();
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
}

bool Graph::isCyclicUtil(int v, bool visited[], bool *recStack)
{
    if(visited[v] == false)
    {
        visited[v] = true;
        recStack[v] = true;

        list<int>::iterator i;
        for(i = adj[v].begin(); i != adj[v].end(); ++i)
        {
            if ( !visited[*i] && isCyclicUtil(*i, visited, recStack) )
                return true;
            else if (recStack[*i])
                return true;
        }

    }
    recStack[v] = false;
    return false;
}

bool Graph::isCyclic()
{
    bool *visited = new bool[V];
    bool *recStack = new bool[V];
    for(int i = 0; i < V; i++)
    {
        visited[i] = false;
        recStack[i] = false;
    }
    for(int i = 0; i < V; i++)
        if ( !visited[i] && isCyclicUtil(i, visited, recStack))
            return true;

    return false;
}

bool conflict(int y, vector<transac> s, int n){
	Graph g(y);
for(int i=0; i<n-1; i++){
	for(int j=i+1; j<n; j++){

	if(s[i].third==s[j].third){
		if(s[i].second!=s[j].second){
			if(s[i].first=='w'||s[i].first=='W'||s[j].first=='W'||s[j].first=='w'){
				g.addEdge(s[i].second-1, s[j].second-1);
			}
		}
	}

}
}
if(g.isCyclic()){
	return false;
}
else{
	return true;
}
}

bool view(int y, vector<transac> s, int n, set<char> var){
  vector<bool> flag;
  bool blindWrite=false;
   for(int i=0; i<y; i++){
  	 flag.push_back(false);
   }
   for(auto x:var){
     if(blindWrite==true){
       break;
     }
     for(int i=0; i<y; i++){
    	 flag[i]=false;
     }
     for(int i=0; i<n; i++){

    	 if(s[i].first=='r'||s[i].first=='R'){
    		 if(s[i].third==x){
           flag[s[i].second-1]=true;
         }
    	 }
    	 if(s[i].first=='w'||s[i].first=='W'){
    		 if(flag[s[i].second-1]==false){
    			 blindWrite=true;
           break;
    		 }
    	 }
     }
   }
   if(!blindWrite){
  	 // cout<<"Schedule is not view serializable because it doesnt contain blind write"<<endl;
     return false;
   }
   if(conflict(y, s, n)){
  	 // cout<<"Schedule is view serializable because it is conflict serializable"<<endl;
     return true;
   }
   Graph g(y);
   for(auto x:var){
     bool wr=false;
     for(int i=0; i<n-1; i++){
       if(s[i].first=='w'||s[i].first=='W'){
         if(s[i].third==x){
          wr=true;
         }
       }
       if(wr==true){
         break;
       }
       if(s[i].first=='r'||s[i].first=='R'){
         if(wr==false){
           if(s[i].third==x){
             for (int j = i+1; j<n ; j++) {
               if(s[j].third==x && s[i].second!=s[j].second){
                 if(s[j].first=='w'||s[j].first=='W'){
                   g.addEdge(s[i].second-1, s[j].second-1);
                   wr=true;
                   break;
                 }
               }
             }
           }
         }
       }
     }
   }
   vector<transac> rev;
   for(int i=0; i<n; i++){
     rev.push_back(s[i]);
   }
   reverse(rev.begin(), rev.end());
   for(auto x:var){
     bool re=false;
     for(int i=0; i<n; i++){
       if(rev[i].first=='r'||rev[i].first=='R'){
         if(rev[i].third==x){
           re=true;
         }
       }
       if(rev[i].first=='w'||rev[i].first=='W'){
         if(rev[i].third==x && re==false){
           for(int j=0; j<y; j++){
             if(rev[i].second-1!=j){
               g.addEdge(j, rev[i].second-1);
             }
           }
           break;
         }
       }
     }
   }
   for(int i=0; i<n-1; i++){
     if( (s[i].first=='w'||s[i].first=='w') && (s[i+1].first=='r'||s[i+1].first=='R') ){
       if( (s[i].third==s[i+1].third) && (s[i].second!=s[i+1].second) ){
         g.addEdge(s[i].second-1, s[i+1].second-1);
       }
     }
   }
   if(g.isCyclic()){
     // cout<<"Schedule is not view serializable"<<endl;
     return false;
   }
   else{
     // cout<<"Schedule is view serializable"<<endl;
     return true;
   }
}

int main(){

vector<transac> s;
int n,z,y;
cout<<"Enter number of operations in Schedule : "<<endl;
cin>>n;
cout<<"Enter number of variables in Schedule : "<<endl;
cin>>z;
cout<<"Enter number of transactions in Schedule : "<<endl;
cin>>y;
for(int i=0; i<n; i++){
	transac op;
	cout<<"Enter details for operation "<<i+1<<endl;
	cout<<"Read/Write (R/W) :"<<endl;
	cin>>op.first;
	cout<<"Transaction Number :"<<endl;
	cin>>op.second;
	cout<<"variable :"<<endl;
	cin>>op.third;
	s.push_back(op);
}
set<char> var;
cout<<"Given Schedule is :"<<endl;
for(int i=0; i<n; i++){

  var.insert(s[i].third);
  cout<<s[i].first<<s[i].second<<s[i].third<<" ";

}
cout<<endl;
char cv;
cout<<"The given schedule should be checked for Conflict serializability(C) or View serializability(V)"<<endl;
cin>>cv;
if(cv=='c' || cv=='C'){
  if(conflict(y, s, n)){
    cout<<"Schedule is Conflict serializable"<<endl;
  }
  else{
    cout<<"Schedule is not Conflict serializable"<<endl;
  }
}
else if(cv=='v'||cv=='V'){
  if(view(y, s, n, var)){
    cout<<"Schedule is View serializable"<<endl;
  }
  else{
    cout<<"Schedule is not View serializable"<<endl;
  }
}
else{
  cout<<"WRONG INPUT"<<endl;
}

return 0;
}
