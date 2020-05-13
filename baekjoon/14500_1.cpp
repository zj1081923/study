#include <iostream>
using namespace std;
int N, M;
int map[500][500]{};
int MAX = -1;

int d_x_3_2[16] = {0, 1, 0, 1, 1, 2, 1, 2, 0, 2, 0, 2, 0, 2, 0, 2};
int d_y_3_2[16] = {1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0};


bool isvalid(int x, int y){
	if(0<=x && x<N && 0<=y && y<M) return true;
	else return false;
}

int tetromino()
{
	int i, j, type, tmp, k, tmp1;
	for(type=0; type<5; type++){


		if(type == 0){
			for(i=0; i<N; i++){
				for(j=0; j<=M-4; j++){
					tmp = map[i][j] + map[i][j+1] + map[i][j+2] + map[i][j+3];
					MAX = max(tmp, MAX);
				}
			}
		}else if(type == 1){
			for(i=0; i<M; i++){
				for(j=0; j<=N-4; j++){
					tmp = map[j][i] + map[j+1][i] + map[j+2][i] + map[j+3][i];
					MAX = max(tmp, MAX);
				}
			}
		}else if(type == 2){
			for(i=0; i<=N-2; i++){
				for(j=0; j<=M-2; j++){
					tmp = map[i][j] + map[i+1][j] + map[i][j+1] + map[i+1][j+1];
					MAX = max(tmp, MAX);
				}
			}
		}else if(type == 3){
			for(i=0; i<=N-3; i++){
				for(j=0; j<=M-2; j++){
					tmp1 = map[i][j] + map[i][j+1] + map[i+1][j] + map[i+1][j+1] + map[i+2][j] + map[i+2][j+1];
					for(k=0; k<16; k=k+2){
						tmp = tmp1 - map[i+d_x_3_2[k]][j+d_y_3_2[k]] - map[i+d_x_3_2[k+1]][j+d_y_3_2[k+1]];
						MAX = max(tmp, MAX);
					}
				}
			}
		}else if(type == 4){
			for(i=0; i<=N-2; i++){
				for(j=0; j<=M-3; j++){
					tmp1 = map[i][j] + map[i][j+1] + map[i][j+2] + map[i+1][j] + map[i+1][j+1] + map[i+1][j+2];
					for(k=0; k<16; k=k+2){
						tmp = tmp1 - map[i+d_y_3_2[k]][j+d_x_3_2[k]] - map[i+d_y_3_2[k+1]][j+d_x_3_2[k+1]];
						MAX = max(tmp, MAX);
					}
				}
			}
		}

	}

	return MAX;


}







int main()
{
	cin >> N >> M;
	int i, j;
	for(i=0; i<N; i++){
		for(j=0; j<M; j++){
			cin >> map[i][j];
		}
	}

	cout << tetromino();
}