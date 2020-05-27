#include <iostream>
#include <stdio.h>
#include <queue>
#include <tuple>
#include <algorithm>

#define INF 2000000000

using namespace std;

// 짧은 소요시간 먼저
struct compare{
	bool operator()(tuple<int, int, int> t, tuple<int, int, int> u){
		return get<2>(t) > get<2>(u);
	}
};

bool isin_tup(vector<tuple<int,int,int>> v, tuple<int,int,int> u){
	return find(v.begin(), v.end(), u) != v.end();
}

// 0번 -> N-1번으로 가는..
void shortest_way(int N, int M, int K){
	//pair<int,int> adj[N][N];
	vector<tuple<int,int,int>> adj[N];
	//pair<int, int> adj[N][N];
	//adj[i][j] -> i에서 j로 가는 경로 (pair는 0으로 초기화되는듯)
	//pair.first = 비용 (비용 넘기면 pass)
	//pair.second = 소요시간 (소요시간 넘기면 pass)
	// 소요시간 가장 짧게
	int i, j, t1, t2, t3, t4;
	for(i=0; i<K; i++){
		cin >> t1 >> t2 >> t3 >> t4;
		adj[t1-1][t2-1] = make_pair(t3, t4);
		//adj[t1-1].push_back(make_tuple(t2-1, t3, t4));
	}

	int time[N]; fill_n(time, N, INF);
	time[0] = 0;
	bool inqueue[N]; fill_n(inqueue, N, false);
	inqueue[0] = true;

	priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, compare> h;
	vector<tuple<int,int,int>> qlist;
	h.push(make_tuple(0, 0, 0));
	qlist.push_back(make_tuple(0, 0, 0));


	while(!h.empty()){
		tuple<int,int,int> t = h.top();

		h.pop();
		int cur = get<0>(t);
		int cur_cost = get<1>(t);
		int cur_time = get<2>(t);
		//cout << "-------------------------------\n";

		//cout << cur+1 << ": cost= " << cur_cost << ", time= " << cur_time << endl;

		for(i=0; i<adj[cur].size(); i++){
			int next = get<0>(adj[cur][i]);
			int next_cost = cur_cost + get<1>(adj[cur][i]);
			if(next_cost > M) continue;
			int next_time = cur_time + get<2>(adj[cur][i]);
			//cout << next+1 << ", " << next_cost <<", " << next_time << endl;
			tuple<int,int,int> tmp = make_tuple(next, next_cost, next_time);
			//if(!isin_tup(qlist, tmp)){
			if(inqueue[next] == false){
				time[next] = next_time;
				h.push(tmp);
				//qlist.push_back(tmp);
				/*cout << "push: (" << next+1 << " " << next_cost << " " << next_time << ")\n";
				for(j=0; j<N; j++){
					if(time[j] == INF) cout << "INF ";
					else cout << time[j]<< " ";
				}cout << endl;*/
			}
		}
	}
	if(time[N-1] == INF) cout << "Poor KCM\n";
	else cout << time[N-1] << "\n";


	
}	





int main()
{
	int T;
	cin >> T;
	int test_case,i, j;
	for(test_case=0; test_case<T; test_case++){
		int N, M, K;
		cin >> N >> M >> K;
		shortest_way(N, M, K);


	}
}
