#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int K;
int TN[4][8]{};

typedef struct SPIN{
	int TN;
	int dir;
}SPIN;

SPIN spin_info[100];


int get_score(){
	int score = 0, i;
	for(i=0; i<4; i++){
		if(TN[i][0] == 1){
			score += 1*pow(2,i);
		}
	}
	return score;
}


void spin_with_dir(int TN_spin_dir[]){
	int i, j, tmp;
	for(i=0; i<4; i++){
		// 시계방향이라면
		if(TN_spin_dir[i] == 1){
			tmp = TN[i][7];
			for(j=7; j>0; j--){
				TN[i][j] = TN[i][j-1];
			}TN[i][0] = tmp;	
		}
		// 반시계방향이라면
		else if(TN_spin_dir[i] == -1){
			tmp = TN[i][0];
			for(j=0; j<7; j++){
				TN[i][j] = TN[i][j+1];
			}TN[i][7] = tmp;
		}
	}
}





void spining_TN(){
	int i, j, cur_tn, moving_tn;
	for(i=0; i<K; i++){
		int TN_spin_dir[4]={0,};
		cur_tn = spin_info[i].TN;
		TN_spin_dir[cur_tn] = spin_info[i].dir;

		moving_tn = cur_tn;
		while(moving_tn > 0){
			// 극이 같은 경우
			if(TN[moving_tn][6] == TN[moving_tn-1][2]) break;
			// 극이 다른 경우
			else{
				TN_spin_dir[moving_tn-1] = TN_spin_dir[moving_tn]*(-1);
				moving_tn--;	
			}
		}
		moving_tn = cur_tn;
		while(moving_tn < 3){
			// 극이 같은 경우
			if(TN[moving_tn][2] == TN[moving_tn+1][6]) break;
			else{
				TN_spin_dir[moving_tn+1] = TN_spin_dir[moving_tn]*(-1);
				moving_tn++;
			}
		}

		spin_with_dir(TN_spin_dir);

	}
}



int main()
{
	int i, j;
	char tmp1[10], tmp[10];
	for(i=0; i<4; i++){
		for(j=0; j<8; j++){
			cin >> tmp[j];
			TN[i][j] = tmp[j]-'0';
		}
	}
	cin >> K;
	for(i=0; i<K; i++){
		cin >> spin_info[i].TN >> spin_info[i].dir;
		spin_info[i].TN--;
	}
	spining_TN();
	cout << get_score();
}