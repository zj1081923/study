#include <iostream>
#include <algorithm>
#include <queue>
#include <map>
using namespace std;
#define INF 2000000000

struct compare{
	bool operator()(pair<int, int> t, pair<int, int> u){
		return t.second > u.second;
	}
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);


	int V, E, K;
	cin >> V >> E >> K;
	K--;
	int i, j;
	int src, dst, w;
	//map<int, int> adj_node[V];
	vector<pair<int, int>> adj_node[V];
	for(i=0; i<E; i++){
		cin >> src >> dst >> w;
		adj_node[src-1].push_back(make_pair(dst-1, w));
	}


	int dist[V]; fill_n(dist, V, INF);
	dist[K] = 0;

	priority_queue<pair<int, int>, vector<pair<int, int>>, compare> h;
	h.push(make_pair(K, dist[K]));

	while(!h.empty()){
		pair<int,int> t = h.top();
		h.pop();
		//if(t.second <= dist[t.first]){
		for(i=0; i<adj_node[t.first].size(); i++){
			int adj = adj_node[t.first][i].first;
			int cal = t.second + adj_node[t.first][i].second;
			if(dist[adj] > cal){
				dist[adj] = cal;
				h.push(make_pair(adj, cal));
			}
		}
	}


	for(i=0; i<V; i++){
		if(dist[i] == INF) cout << "INF" << "\n";
		else cout << dist[i] << "\n";
	}
}
