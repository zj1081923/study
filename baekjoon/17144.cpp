#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;
#define MAX 50


int A[MAX][MAX];
vector<pair<int, int>> mise_loc;
int air_loc[2]; // 0: top, 1: bot


int dx[] = {0, -1, 0, 1};
int dy[] = {1, 0, -1, 0};
void print_(int R, int C){
	int i, j;
	cout<<"---------------------" << endl;
		for(i=0; i<R; i++){
		for(j=0; j<C; j++){
			cout << A[i][j] << " ";
		}
		cout << endl;
	}
}

void air_clearing(int R, int C){
	//위에
	int i, j;
	int topx = air_loc[0];
	int botx = air_loc[1];
	int x = topx, y = C-1;
	for(i=topx-1; i>0; i--){ //4번 아래
		A[i][0] = A[i-1][0];
	}
	for(i=0; i<C-1; i++){ // 3번 왼
		A[0][i] = A[0][i+1];
	}
	for(i=1; i<topx+1; i++){ //2 위
		A[i-1][C-1] = A[i][C-1];
	}
	for(i=C-1; i>1; i--){ //1 오
		A[topx][i] = A[topx][i-1];
	}
	A[topx][1] = 0;

	//아래
	for(i=botx+1; i<R-1; i++){
		A[i][0] = A[i+1][0];
	}
	for(i=0; i<C-1; i++){
		A[R-1][i] = A[R-1][i+1];
	}
	for(i=R-1; i>botx-1; i--){
		A[i][C-1] = A[i-1][C-1];	
	}

	for(i=C-1; i>1; i--){
		A[botx][i] = A[botx][i-1];
	}
	A[botx][1] = 0;
}


int find_mise_loc(int R, int C){
	mise_loc.clear();
	int sum=0;
	int i, j;
	for(i=0; i<R; i++){
		for(j=0; j<C; j++){
			if(A[i][j] != 0 && A[i][j] != -1){
				//mise_loc.push_back(make_pair(i, j));
				sum += A[i][j];
			}
		}
	}
	return sum;
}




void spread_mise(int R, int C){
	int added_mise[R][C]{};
	int i, j, k;

	k = find_mise_loc(R, C);
	int mise_cnt = mise_loc.size();

	for(i=0; i<R; i++){
		for(j=0; j<C; j++){
			if(A[i][j] != 0 && A[i][j] != -1){ //미세먼지가 있을 경우
				for (int dir=0; dir<4; dir++){ //4방향이 범위 안에 들어오면
					if (i+dx[dir] >= 0 && i+dx[dir]<R && j+dy[dir]>=0 && j+dy[dir]<C && A[i+dx[dir]][j+dy[dir]] != -1){ 
						added_mise[i+dx[dir]][j+dy[dir]] += A[i][j]/5;
						added_mise[i][j] -= A[i][j]/5;
					}
				}
			}
		}
	}




	/*for (k=0; k<mise_cnt; k++){
		int divide = 0;
		int cur_x = mise_loc.at(k).first;
		int cur_y = mise_loc.at(k).second;

		for(int dir=0; dir<4; dir++){

			if (cur_x+dx[dir] >= 0 && cur_x+dx[dir]<R && cur_y+dy[dir]>=0 && cur_y+dy[dir]<C && A[cur_x+dx[dir]][cur_y+dy[dir]] != -1){
				added_mise[cur_x+dx[dir]][cur_y+dy[dir]] += A[cur_x][cur_y]/5;
				added_mise[cur_x][cur_y] -= A[cur_x][cur_y]/5;


				if(find(mise_loc.begin(), mise_loc.end(), make_pair(cur_x+dx[dir], cur_y+dy[dir])) == mise_loc.end()){
					mise_loc.push_back(make_pair(cur_x+dx[dir], cur_y+dy[dir]));
				}

			}
		}

	}*/
	for(i=0; i<R; i++){
		for(j=0; j<C; j++){
			A[i][j] += added_mise[i][j];
		}
	}

	//print_(R, C);



}



int main()
{
	int R, C, T;
	int topx = 0, botx = 0; 
	cin >> R;
	cin >> C;
	cin >> T;
	int mise_cnt = 0;
	for (int i=0; i<R; i++){
		for(int j=0; j<C; j++){
			cin >> A[i][j];
		}
	}

	int tmp=0;
	for(int i=0; i<R; i++){
		if (A[i][0] == -1){
			air_loc[tmp] = i;
			tmp++;	
		}
		if(tmp > 2) break;

	}
	for(int i=0; i<T; i++){
		spread_mise(R, C);
		air_clearing(R, C);
	}

	cout << find_mise_loc(R, C);

}