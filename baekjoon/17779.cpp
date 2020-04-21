// 게리맨더링2
#include <iostream>
#include <algorithm>
using namespace std;
int N;
int city[20][20];
int Min = 2000;


void calculate_result1(int x, int y, int d1, int d2){
	int i, j;
	int mark[N][N]{};
	pair<int, int> p[4];

	int one=0, two=0, three=0, four=0, five=0;

	p[0].first = x;
	p[0].second = y;
	p[1].first = x+d1;
	p[1].second = y-d1;
	p[2].first = x+d1+d2;
	p[2].second = y-d1+d2;
	p[3].first = x+d2;
	p[3].second = y-d1+d2;

	int range = p[0].second;
	//cout << p[1].first << p[0].second;
	for(i=0; i<p[1].first; i++){ // 1
		if(p[0].first <= i && i<p[1].first) range--;
		for(j=0; j<=range; j++){
			mark[i][j]=1;
			one += city[i][j];
		}
	}

	range = p[1].second-1;
	for(i=p[1].first; i<N; i++){
		if(p[1].first<=i && i<=p[2].first) range++;
		for(j=0; j<range; j++){
			mark[i][j] = 3;
			three += city[i][j];
		}
	}

	range = p[2].second;
	for(i=N-1; i>p[3].first; i--){
		if(p[3].first<i && i<=p[2].first) range++;
		for(j=range; j<N; j++){
			mark[i][j] = 4;
			four += city[i][j];
		}
	}

	range = p[0].second+1;
	for(i=0; i<=p[3].first; i++){
		if(p[0].first<i && i<=p[3].first) range++;
		for(j=range; j<N; j++){
			mark[i][j] = 2;
			two += city[i][j];
		}
	}
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			if(mark[i][j] == 0) five += city[i][j];
		}
	}

	int max_city = max({one, two, three, four, five});
	int min_city = min({one, two, three, four, five});
	int cur_min = max_city-min_city;
	Min = min(cur_min, Min);


}



int main()
{
	int i, j, d1, d2;
	cin >> N;

	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			cin >> city[i][j];
		}
	}

	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			for(d1=0; d1<N; d1++){
				for(d2=0; d2<N; d2++){
					if(i+d1+d2>=N || j-d1<0 || j+d2>=N) continue;
					calculate_result1(i, j, d1, d2);

				}
			}
		}
	}	
	cout << Min;



}