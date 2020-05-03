#include<iostream>
using namespace std;
int N, M;
int city[50][50];
int chicken_loc_x[13]; //치킨집 위치 저장
int chicken_loc_y[13];
int chicken_num=0; // ㅊ ㅣ킨 개수 저장
int house_num=0; // 집 개수 저장
int MIN = 1000000;

int get_min_distance(int select_num, int selected_chicken[], int x, int y){
	int i, j, dist=1000000, tmp_dist;
	for(i=0; i<select_num; i++){
		tmp_dist = abs(x-chicken_loc_x[selected_chicken[i]])+abs(y-chicken_loc_y[selected_chicken[i]]);
		if(tmp_dist < dist) dist = tmp_dist;
	}
	return dist;
}


int get_chicken_distance(int total_num, int selected_chicken[]){
	int i, j, city_dist=0;
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			if(city[i][j] == 1){ //집이라면
				city_dist += get_min_distance(total_num, selected_chicken, i, j);
			}
		}
	}
	return city_dist;

}


int get_chicken_distance1(int total_num, int selected_chicken[], pair<int, int> house_loc[]){
	int i, j, city_dst = 0;

	for(i=0; i<house_num; i++){
		city_dst += get_min_distance(total_num, selected_chicken, house_loc[i].first, house_loc[i].second);
	}
	return city_dst;

}



void dfs(int select_num, int selected_chicken[], int cur_idx, pair<int,int> house_loc[]){
	// dfs 로 조합 구함

	
	/*
	select_num 전 dfs에서 고른 치킨집
	selected_chicken 지금까지 골라진 치킨집 목록
	cur_idx 치킨집 개수, 현재 dfs에서 저장되어야 할 인덱스
	house_loc 집 위치
	*/

	int i, j;
	//dfs 시작할때마다 최솟값 구함
	MIN = min(MIN, get_chicken_distance1(cur_idx, selected_chicken, house_loc));


	if(cur_idx == M){
		return;
	}

	int tmp=0;
	for(i = select_num+1; i<chicken_num; i++){
		selected_chicken[cur_idx] = i;
		dfs(i, selected_chicken, cur_idx+1, house_loc);
	}


}


int main()
{

	cin >> N >> M;
	pair<int, int> house_loc[2*N];
	int i, j;
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			cin >> city[i][j];
			if (city[i][j] == 2){
				chicken_loc_x[chicken_num] = i;
				chicken_loc_y[chicken_num] = j;
				chicken_num++;
			}
			else if(city[i][j] == 1){
				house_loc[house_num].first = i;
				house_loc[house_num].second = j;
				house_num++;
			}
		}
	}

	int selected_chicken[M]={0,};

	dfs(-1, selected_chicken, 0, house_loc);

	cout << MIN;




}