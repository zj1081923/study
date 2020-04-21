#include <iostream>
#include <cmath>
using namespace std;
#define MAX 101




int N;
int map[MAX][MAX]{};
int dx[] = {0, -1, 0, 1};//0, 1, 2, 3
int dy[] = {1, 0, -1, 0};

//0: 오, 1: 위, 2: 왼, 3: 아래

void if_in_check(int x, int y){
	if (0<=x && x<=100 && 0<=y && y<=100){
		map[x][y] = 1;
	}
}

int change_dir(int d){
	return (d+1)%4;
}

int find_square(){
	int i, j, sq=0;
	for(i=1; i<MAX; i++){
		for(j=1; j<MAX; j++){
			if(map[i][j]+map[i][j-1]+map[i-1][j]+map[i-1][j-1] == 4){
				sq++;
			}
		}
	}
	return sq;
}


void after_g(int g, int d, int cnt, int x, int y){ //cnt는 1로 시작
	int size = pow(2, g);
	int total_dir[size];
	int i, cur_g, dir;
	total_dir[0] = d;
	for(cur_g = 1; cur_g<g+1; cur_g++){
		int tmp = cnt;
		for(i=cnt-1; i>=0; i--){
			total_dir[tmp] = change_dir(total_dir[i]);
			tmp++;
		}
		cnt = tmp;
	
	}
	if_in_check(x, y);
	for(i=0; i<cnt; i++){
		dir = total_dir[i];
		x += dx[dir];
		y += dy[dir];
		if_in_check(x, y);
	}

}



int main()
{
	cin >> N;
	int i, x_start, y_start, d_start, g;
	for(i=0; i<N; i++){
		

		cin >> x_start;
		cin >> y_start;
		cin >> d_start;
		cin >> g;
		after_g(g, d_start, 1, y_start, x_start);
	}
	cout << find_square();

}