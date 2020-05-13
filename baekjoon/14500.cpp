#include <iostream>
#include <algorithm>
using namespace std;
int N, M;
int MAX = -1;
int paper_map[500][500]{};

int d_x_3_2[8][4]={{0, 1, 2, 2},
				   {2, 2, 1, 0},
				   {0, 1, 2, 0},
				   {0, 0, 1, 2},
				   {0, 1, 1, 2},
				   {1, 2, 1, 0},
				   {0, 1, 1, 2},
				   {1, 1, 0, 2}};
int d_y_3_2[8][4]={{0, 0, 0, 1},
				   {0, 1, 1, 1},
				   {0, 0, 0, 1},
				   {0, 1, 1, 1},
					{0, 0, 1, 1},
					{0, 0, 1, 1},
					{0, 0, 1, 0},
					{0, 1, 1, 1}};



int get_max_sum(){
	int i, j, shape, k, type;
	int tmp_max, tmp1, tmp2;
	for(type=0; type<5; type++){
		tmp_max = 0;
		//cout << "---type = "<<type << "---" << endl;
		if(type == 0){
			for(i=0; i<N; i++){
				tmp2 = paper_map[i][0] + paper_map[i][1] + paper_map[i][2] + paper_map[i][3];
				tmp1 = tmp2;
				for(j=4; j<M; j++){
					//cout << i << ", "<< j<<endl;
					tmp1 = tmp1 - paper_map[i][j-4] + paper_map[i][j];
					tmp_max = max({tmp_max, tmp2, tmp1});
				}
			}
		}else if(type == 1){
			for(i=0; i<M; i++){
				tmp2 = paper_map[0][i] + paper_map[1][i] + paper_map[2][i] + paper_map[3][i];
				tmp1 = tmp2;
				//cout << tmp1 << endl;
				for(j=4; j<N; j++){
					//cout << j << ", "<<i<<endl;
					tmp1 = tmp1 - paper_map[j-4][i] + paper_map[j][i];
					//cout << tmp1 << endl;
					tmp_max = max({tmp_max, tmp2, tmp1});
				}
			}
		}else if(type == 2){
			for(i=0; i<N-1; i++){
				tmp2 = paper_map[i][0] + paper_map[i][1] + paper_map[i+1][0] + paper_map[i+1][1];
				tmp1 = tmp2;
				//cout << "@@ "<<tmp_max<<endl;
 				for(j=2; j<M; j++){
					//cout << i << ", "<< j<<endl;
					tmp1 = tmp1 - paper_map[i][j-2] - paper_map[i+1][j-2] + paper_map[i][j] + paper_map[i+1][j];
					//cout << "? : "<<tmp1<<endl;
					//cout << "MAX = " << MAX << endl;
					tmp_max = max({tmp2, tmp_max, tmp1});
				}
			}

		}else if(type == 3){
			for(i=0; i<N-2; i++){
				for(j=0; j<M-1; j++){
					//cout << i << ", "<< j<<endl;
					int score[8]={0,};
					for(shape=0; shape<8; shape++){
						for(k=0; k<4; k++){
							score[shape] += paper_map[i+d_x_3_2[shape][k]][j+d_y_3_2[shape][k]];
						}
					}
					/*for(k=0; k<8; k++){
						cout<<score[k]<<" "<<endl;
					}cout << endl;*/
					tmp1 = *max_element(score, score+8);
					tmp_max = max(tmp_max, tmp1);

				}
			}
		}else if(type == 4){
			for(i=0; i<N-1; i++){
				for(j=0; j<M-2; j++){
					//cout << i << ", "<< j<<endl;
					int score[8]={0,};
					for(shape=0; shape<8; shape++){
						for(k=0; k<4; k++){
							score[shape] += paper_map[i+d_y_3_2[shape][k]][j+d_x_3_2[shape][k]];
						}
						//if(shape == 1) cout << score[shape]<< endl;
					}
					tmp1 = *max_element(score, score+8);
					tmp_max = max(tmp_max, tmp1);
					//cout << tmp1 << endl;
					//cout << tmp_max << endl;

				}
			}
		}
		//cout <<"?? : "<<tmp_max << " MAX = " << MAX << endl;
		MAX = max(MAX, tmp_max);
	}
	return MAX;
}





int main()
{
	cin >> N >> M;
	int i, j;

	for(i=0; i<N; i++){
		for(j=0; j<M; j++){
			cin >> paper_map[i][j];
		}
	}
	//cout << endl << "answer : ";
	cout << get_max_sum();
}