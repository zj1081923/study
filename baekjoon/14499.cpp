#include <iostream>
using namespace std;
#define MAX 20
int N, M;
int x, y;
int dir_num;
int map[MAX][MAX];
int dice[6] = {0,};
// 아래면 idx = 0
// 윗면 idx = 5
int dir_x[] = {0, 0, -1, 1};
int dir_y[] = {1, -1, 0, 0};



void change_dice(int dir){
	int tmp=dice[0];
	if ( dir==1 ){ // 오른쪽으로 ->
		dice[0] = dice[2];
		dice[2] = dice[5];
		dice[5] = dice[3];
		dice[3] = tmp;

	}else if( dir==2 ){ // 왼쪽 <-
		dice[0] = dice[3];
		dice[3] = dice[5];
		dice[5] = dice[2];
		dice[2] = tmp;
	}else if( dir==3 ){ // 위쪽 ↑
		dice[0] = dice[1];
		dice[1] = dice[5];
		dice[5] = dice[4];
		dice[4] = tmp;
	}else if( dir==4 ){ //아래쪽 ↓
		dice[0] = dice[4];
		dice[4] = dice[5];
		dice[5] = dice[1];
		dice[1] = tmp;
	}
}

bool check_valid_xy(int x, int y){
	if(0<=x && x<N && 0<=y && y<M) return true;
	else return false;
}

void moving_on_map(int dir_order[]){
	int cur_dir;
	for(int i=0; i<dir_num; i++){
		cur_dir = dir_order[i];
		if(check_valid_xy(x+dir_x[cur_dir-1], y+dir_y[cur_dir-1])){
			if(map[x][y]==0) map[x][y] = dice[0];
			else{
				dice[0] = map[x][y];
				map[x][y] = 0;
			}
			x = x+dir_x[cur_dir-1];
			y = y+dir_y[cur_dir-1];
			change_dice(cur_dir); 
			cout << dice[5] << endl;
		}
	}
}

int main()
{
	cin >> N >> M >> x >> y >> dir_num;

	for(int i=0; i<N; i++){
		for(int j=0; j<M; j++){
			cin >> map[i][j];
		}
	}

	int dir_order[dir_num];
	for(int i=0; i<dir_num; i++){
		cin >> dir_order[i];
	}

	moving_on_map(dir_order);

}