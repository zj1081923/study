#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int r, c, k;
int arr[100][100];
int row_len = 3, col_len = 3;
// 행의개수, 열의개수 

bool compare(pair<int,int> a, pair<int,int> b){
	if(a.second == b.second)
		return a.first < b.first;
	return a.second < b.second;
}

void C_calculate(){
	int i, j, max_len = -1;
	int rlength[col_len]={0,};

	for(i=0; i<col_len; i++){
		vector<int> v;
		// 한 줄을 vector v에 삽입 (0은 넣을 필요 없으므로 넘어감)
		for(j=0; j<row_len; j++){
			if(arr[j][i] == 0) continue;
			v.push_back(arr[j][i]);
		}

		// pair p[100] : 숫자와 숫자개수를 저장할 쌍
		pair<int,int> p[100];
		sort(v.begin(), v.end());
		int loc = 0;
		int cur = v.back();
		v.pop_back();

		p[loc].first = cur;
		p[loc].second = 1;
		while(!v.empty()){
			if(v.back() == cur){
				p[loc].second++;
			}else{
				loc++;
				p[loc].first = v.back();
				p[loc].second = 1;
			}
			cur = v.back();
			v.pop_back();
		}

		// 각 줄의 총 길이 저장(나중에 0 붙일때 사용)
		rlength[i] = 2*(loc+1);

		// pair의 second(숫자개수)를 우선순위로 소팅
		sort(&p[0], &p[loc+1], compare);

		// arr 배열에 업데이트
		for(j=0; j<loc+1; j++){
			arr[j*2][i] = p[j].first;
			arr[j*2+1][i] = p[j].second;
		}

		max_len = max(max_len, rlength[i]); // resize할 때 사용
		max_len = min(max_len, 100); // 100을 넘지 않도록
	}

	// 배열의 row size 업데이트
	row_len = max_len;

	// rlength 이후부터 업데이트된 row size까지 0 추가
	for(i=0; i<col_len; i++){
		for(j=rlength[i]; j<row_len; j++){
			arr[j][i] = 0;
		}
	}

}


void R_calculate(){
	int i, j, max_len=-1;
	int clength[row_len]={0,};
	for(i=0; i<row_len; i++){
		vector<int> v;
		for(j=0; j<col_len; j++){
			if(arr[i][j]==0) continue;
			v.push_back(arr[i][j]);
		}
		pair<int,int> p[100];
		sort(v.begin(), v.end());
		int loc = 0;
		int cur = v.back();
		v.pop_back();
		p[loc].first = cur;
		p[loc].second = 1;
		while(!v.empty()){
			if(v.back() == cur){
				p[loc].second++;
			}else{
				loc++;
				p[loc].first = v.back();
				p[loc].second = 1;
			}
			cur = v.back();
			v.pop_back();
		}

		clength[i] = 2*(loc+1);

		sort(&p[0], &p[loc+1], compare);

		for(j=0; j<loc+1; j++){
			arr[i][j*2] = p[j].first;
			arr[i][j*2+1] = p[j].second;
		}

		max_len = max(max_len, clength[i]);
		max_len = min(max_len, 100);

	}
	col_len = max_len;

	for(i=0; i<row_len; i++){
		for(j=clength[i]; j<col_len; j++){
			arr[i][j] = 0;
		}
	}
}





int array_sorting(){
	int sec = 0, i, j;
	while(arr[r][c] != k){
		int tmp[100] = {0,};
		int num=0, max_len=-1;
		vector<int> v_tmp;
		if(row_len >= col_len){ // R 연산

			R_calculate();

		}else{ // C 연산

			C_calculate();
		}


		sec++;
		if(sec > 100) return -1;
	}
	return sec;
}





int main(int argc, char const *argv[])
{
	cin >> r >> c >> k;
	r--;
	c--;
	int i, j;
	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			cin >> arr[i][j];
		}
	}
	cout << array_sorting();
}