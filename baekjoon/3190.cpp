#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int N, K, L;
// N: map 크기, K: 사과의 개수, L: 뱀의 방향변환 횟수
int map[101][101]{};
enum {UP, RIGHT, DOWN, LEFT};
// 왼쪽이면 -1 오른쪽이면 +1

int dirx[] = {-1, 0, 1, 0};
int diry[] = {0, 1, 0, -1};

typedef struct Snake{
	Snake(int l, int d) : length(l), dir(d) {}
	queue<pair<int,int>> body; // body의 front는 뱀의 tail, back은 뱀의 head
	int length;
	int dir;
}Snake;


vector<pair<int,char>> snake_dir_info;


bool is_valid(int x, int y){
	if(0<=x && x<N && 0<=y && y<N && map[x][y] != 1) return true;
	else return false;
}

int Dummy_start(Snake snake){

	reverse(snake_dir_info.begin(), snake_dir_info.end());

	int sec = 1, nextx=0, nexty=1, i, j;

	while(true){

		nextx = snake.body.back().first + dirx[snake.dir];
		nexty = snake.body.back().second + diry[snake.dir];
		
		// 벽에 닿거나 자기 몸에 부딪히면 return
		if(!is_valid(nextx, nexty)){
			return sec;
		}


		// 늘린 머리를 body에 추가
		snake.body.push(make_pair(nextx, nexty));
		
		if(map[nextx][nexty] != 9){ // 사과가 아니면
			//map에서 꼬리를 없애고 body에도 꼬리를 pop
			map[snake.body.front().first][snake.body.front().second] = 0;
			snake.body.pop();
		}

		// 늘린 머리를 map에 표시해줌 (뱀은 1)
		map[nextx][nexty] = 1;

		// 현재 시간이 방향을 바꿔야 할 시간이라면 snake의 dir(방향)을 바꾸어줌
		if(sec == snake_dir_info.back().first){
			if(snake_dir_info.back().second == 'L'){
				snake.dir = (snake.dir+3)%4;
			}else{
				snake.dir = (snake.dir+1)%4;
			}
			snake_dir_info.pop_back();
		}


		sec++;
	}



}


int main()
{
	cin >> N >> K;
	int i, j, t, t1;
	for(i=0; i<K; i++){
		cin >> t;
		cin >> t1;
		map[t-1][t1-1] = 9;
	}
	char tt;
	cin >> L;
	for(i=0; i<L; i++){
		cin >> t >> tt;
		snake_dir_info.push_back(make_pair(t, tt));
	}

	Snake snake = {1, RIGHT};
	snake.body.push(make_pair(0, 0));
	map[0][0] = 1;

	cout << Dummy_start(snake);
	

}