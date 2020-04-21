#include <iostream>
#include <algorithm>
using namespace std;

int N, L;


bool check_road(int line[]){

	int table[N], mark[N]={0,};
	copy(line, line+N, table);
	
	int i = 0;
	while( i < N-1 ){

		if(table[i] == table[i+1]){ //같은 층인 경우
			i++;
			continue;
		}
		if (abs(table[i] - table[i+1])>1) return false;//////

		// 다른 층인 경우(한칸차이)
		if(table[i] - table[i+1] == 1){ //현재 층이 다음 층보다 높은 경우
			if(i+L >= N) return false;

			for(int j=i+1; j<=i+L; j++){
				if(mark[j] == 1) return false;
			}
			for(int j=1; j<L; j++){
				if(table[i+j] != table[i+j+1]) return false;
			}
			for(int j=i+1; j<=i+L; j++){
				mark[j] = 1;
			}

			i += L;

		}
		else if(table[i] - table[i+1] == -1){ //다음층보다 낮은경우
			if(i-L+1 < 0) return false;
			for(int j=i; j>i-L; j--){
				if(mark[j] == 1) return false;
			}
			for(int j=0; j<L-1; j++){
				if(table[i-j] != table[i-j-1]) return false;
			}
			for(int j=i; j>i-L; j--){
				mark[j] = 1;
			}
			i++;
		}

	}
	return true;

}


int main()
{
	cin >> N;
	cin >> L;
	int map[N][N];
	for (int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			cin >> map[i][j];
		}
	}

	int road[N];
	int result = 0;


	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			road[j] = map[i][j]; // 가로한줄
		}
		if (check_road(road) == true) {
				result++;
		}
		for(int j=0; j<N; j++){
			road[j] = map[j][i]; //세로한줄
		}
		if (check_road(road) == true){
				result++;
		}
	}
	cout << result;

}