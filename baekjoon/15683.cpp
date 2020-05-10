#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int N, M;
int map[8][8];
typedef struct CCTV{
	int x;
	int y;
	int type;
}CCTV;




CCTV cctv[8];
int cctv_num=0;
int blank = 0;
int min_cannotsee=100000000;

int way_3[] = {0, 3, 2, -1, -2, -1};

int get_cannotsee_number(CCTV cctv[], queue<int> dir1[]){
	int copied_map[8][8]{};
	copy(&map[0][0], &map[0][0]+8*8, &copied_map[0][0]);
	int i, j, way, tmp_x, tmp_y, cansee=0, x, y;
	queue<int> dir[cctv_num];


	for(i=0; i<cctv_num; i++){
		dir[i] = dir1[i];
	} // queue dir 복사

	for(i=0; i<cctv_num; i++){
		while(!dir[i].empty()){
			way = dir[i].front();
			x = cctv[i].x;
			y = cctv[i].y;
			tmp_x = cctv[i].x;
			tmp_y = cctv[i].y;

			dir[i].pop();
			if(way == 1){
				tmp_y++;
				while(copied_map[x][tmp_y] != 6 && tmp_y < M){
					if(copied_map[x][tmp_y] == 0){
						copied_map[x][tmp_y] = 9;
						cansee++;
					}
					tmp_y++;
				}
			}else if(way == 2){
				tmp_x++;
				while(copied_map[tmp_x][y] != 6 && tmp_x < N){
					if(copied_map[tmp_x][y] == 0){
						copied_map[tmp_x][y] = 9;
						cansee++;
					}
					tmp_x++;
				}
			}else if(way == 3){
				tmp_y--;
				while(copied_map[x][tmp_y] != 6 && tmp_y >= 0){
					if(copied_map[x][tmp_y] == 0){
						copied_map[x][tmp_y] = 9;
						cansee++;
					}
					tmp_y--;
				}
			}else if(way == 4){
				tmp_x--;
				while(copied_map[tmp_x][y] != 6 && tmp_x >= 0){
					if(copied_map[tmp_x][y] == 0){
						copied_map[tmp_x][y] = 9;
						cansee++;
					}
					tmp_x--;
				}
			}
		}
	}
	return blank-cansee;
}




void DFS(CCTV cctv[], int cur_i, queue<int> dir[]){
	if(cur_i == cctv_num){
		min_cannotsee = min(min_cannotsee, get_cannotsee_number(cctv, dir));
		return;
	}

	int i, j;
	int cur_type = cctv[cur_i].type;
	if(cur_type == 1){
		for(i=1; i<5; i++){
			dir[cur_i].push(i);
			DFS(cctv, cur_i+1, dir);
			dir[cur_i].pop();
		}
	}else if(cur_type == 2){
		for(i=1; i<3; i++){
			dir[cur_i].push(i);
			dir[cur_i].push(i+2);
			DFS(cctv, cur_i+1, dir);
			dir[cur_i].pop();
			dir[cur_i].pop();
		}
	}else if(cur_type == 3){
		for(i=1; i<5; i++){
			dir[cur_i].push(i);
			if(i == 4) dir[cur_i].push(1);
			else dir[cur_i].push(i+1);
			DFS(cctv, cur_i+1, dir);
			dir[cur_i].pop();
			dir[cur_i].pop();
		}
	}else if(cur_type == 4){
		for(i=1; i<5; i++){
			dir[cur_i].push(i);
			dir[cur_i].push(i+way_3[i]);
			dir[cur_i].push(i+way_3[i+1]);
			DFS(cctv, cur_i+1, dir);
			dir[cur_i].pop();
			dir[cur_i].pop();
			dir[cur_i].pop();
		}
	}else if(cur_type == 5){
		for(i=1; i<5; i++){
			dir[cur_i].push(i);
		}
		DFS(cctv, cur_i+1, dir);
		for(i=1; i<5; i++){
			dir[cur_i].pop();
		}
	}

}




int main()
{
	cin >> N >> M;
	int i, j;
	for(i=0; i<N; i++){
		for(j=0; j<M; j++){
			cin >> map[i][j];
			if(1<=map[i][j] && map[i][j]<=5){
				cctv[cctv_num].x = i;
				cctv[cctv_num].y = j;
				cctv[cctv_num].type = map[i][j];
				cctv_num++;
			}else if(map[i][j]==0) blank++;
		}
	}

	queue<int> dir[cctv_num];
	DFS(cctv, 0, dir);

	cout << min_cannotsee;
}