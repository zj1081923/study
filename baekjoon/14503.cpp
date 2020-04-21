#include <iostream>
using namespace std;

int result=0;
int N, M;


int turn_left(int dir){
	if ( dir == 0 ) return 3;
	else if (dir == 1) return 0;
	else if (dir == 2) return 1;
	else return 2;
}

int go_back (int dir){
	if (dir == 0) return 2;
	else if (dir == 1) return 3;
	else if (dir == 2) return 0;
	else return 1;
}



int main()
{
	cin >> N;
	cin >> M;

	int cur_x, cur_y, dir;

	cin >> cur_x;
	cin >> cur_y;
	cin >> dir;

	int room[N][M];
	int i, j;
	for(int i=0; i<N; i++){
		for(int j=0; j<M; j++){
			cin >> room[i][j];
		}
	}

	int cleaned4 = 0;
	// 0(북)보고있을때는 3(서)
	// 1(동)보고있을때는 0(북)
	// 2(남)보고있을때는 1(동)
	// 3(서)보고있을때는 2(남) 
	
	int dir_x[4] = {-1, 0, 1, 0}; //동서남북 (1, 2, 3, 0)
	int dir_y[4] = {0, 1, 0, -1};
	int check = 0;
	while(1){
		cleaned4 = 0;
		if (room[cur_x][cur_y] == 0){
			room[cur_x][cur_y] = 2; // 현재위치를 청소한다
			result++;
		}
		int tmp_dir = dir;
		for(i=0; i<4; i++){
			tmp_dir = turn_left(tmp_dir);
			int tmp_x = cur_x + dir_x[tmp_dir];
			int tmp_y = cur_y + dir_y[tmp_dir];



			if (room[tmp_x][tmp_y] == 0){//왼쪽이 청소할 수 있다면
				dir = tmp_dir;
				cur_x = tmp_x;
				cur_y = tmp_y;
				break;
			}else if (room[tmp_x][tmp_y] == 1 || room[tmp_x][tmp_y] == 2){
				cleaned4++;
			}
		}
		if(cleaned4 == 4){
			cleaned4 = 0; //네방향 모두 청소가 되어있거나 벽인 경우에는
			int dr_idx = go_back(dir);
			int tmp_x = cur_x + dir_x[dr_idx];
			int tmp_y = cur_y + dir_y[dr_idx];//후진을 살펴본다.
			if(room[tmp_x][tmp_y] == 1) break; //뒤에가 벽이면 작동을 멈춘다.
			else{ //뒤가 벽이 아니면 현재 위치를 뒤로 바꾼다.
				cur_x = tmp_x;
				cur_y = tmp_y;
			}
		}
	}

	
	cout << result;

}
