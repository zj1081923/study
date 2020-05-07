#include <iostream>
#include <queue>
using namespace std;

int N, L, R;
int map[50][50];
int dir_x[] = {-1, 0, 1, 0};
int dir_y[] = {0, 1, 0, -1};

int cur_total_pop=0;
int cur_con_num=1;

queue<pair<int,int>> neighber_loc;

void open_(int cur_x, int cur_y, bool(*map_used)[50])
{
	int i, j, next_x, next_y, next_loc_pop;
	int cur_loc_pop = map[cur_x][cur_y];
	map_used[cur_x][cur_y] = true;

	for(i=0; i<4; i++){
		next_x = cur_x + dir_x[i];
		next_y = cur_y + dir_y[i];

		if(next_x<0 || next_x>=N || next_y<0 || next_y>=N) continue;

		next_loc_pop = map[next_x][next_y];
		int m = abs(next_loc_pop - cur_loc_pop);
		
		if(L<=m && m<=R && map_used[next_x][next_y]==false){
			neighber_loc.push(make_pair(next_x, next_y));
			cur_con_num++;
			cur_total_pop += next_loc_pop;
			open_(next_x, next_y, map_used);
		}
	}
		
}

bool modify_pop(bool(*map_used)[50])
{
	int i, j;

	bool ischanged = false;


	int changed_pop = cur_total_pop/cur_con_num;
	cur_total_pop=0;
	cur_con_num=1;

	while(!neighber_loc.empty()){
		int x, y;
		x = neighber_loc.front().first;
		y = neighber_loc.front().second;
		neighber_loc.pop();
		if(map[x][y] != changed_pop) ischanged = true;
		map[x][y] = changed_pop;
	}

	return ischanged;

}


int main()
{


	cin >> N >> L >> R;
	int i, j;
	bool isfine = true;

	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			cin >> map[i][j];
		}
	}



	int a = 0;
	int check = 0;

	while(isfine == true){
		check = 0;
		bool map_used[50][50]{};
		for(i=0; i<N; i++){
			for(j=0; j<N; j++){
				if(map_used[i][j] == false){
					cur_total_pop = map[i][j];
					open_(i, j, map_used);
					if(cur_total_pop != map[i][j]){
						check = 1;
						neighber_loc.push(make_pair(i, j));
						isfine = modify_pop(map_used);
					}
				}
			}
		}
		if(check == 0) isfine = false;
		else if(isfine == true) a++;
	}

	cout << a;
	


}