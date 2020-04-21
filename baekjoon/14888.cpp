#include <iostream>
using namespace std;
#define MAX 1000000000
#define MIN -1000000000

int p, m, x, d, N;
int max_, min_;

//remain은 거꾸로, cur_i는 0부터...
void dfs(int remain_p, int remain_m, int remain_x, int remain_d, int cur_i, int result, int number[]){

	if(cur_i == N){
		max_ = max(max_, result);
		min_ = min(min_, result);
		return;
	}

	int i, tmp;
	if(remain_p > 0){ // 더하기 하고 다음 단계로
		tmp = result + number[cur_i];
		dfs(remain_p-1, remain_m, remain_x, remain_d, cur_i+1, tmp, number);
	}
	if(remain_m > 0){
		tmp = result - number[cur_i];
		dfs(remain_p, remain_m-1, remain_x, remain_d, cur_i+1, tmp, number);
	}
	if(remain_x > 0){
		tmp = result * number[cur_i];
		dfs(remain_p, remain_m, remain_x-1, remain_d, cur_i+1, tmp, number);
	}
	if(remain_d > 0){
		tmp = result / number[cur_i];
		dfs(remain_p, remain_m, remain_x, remain_d-1, cur_i+1, tmp, number);	
	}

}


int main()
{
	cin >> N;
	int number[N];
	for(int i=0; i<N; i++){
		cin >> number[i];
	}
	cin >> p >> m >> x >> d;


	min_ = MAX;
	max_ = MIN;

	dfs(p, m, x, d, 1, number[0], number);
	cout << max_ << endl;
	cout << min_;

	
}