#include <iostream>
using namespace std;
#define MAX 1000
int N;
int min_ = MAX;
int power[20][20];


int get_team_power1(int mark_team[]){

    int link=0, start=0;

    int start_team[N/2]={0,};
    int link_team[N/2]={0,};
    int i, j, ii=0, jj=0;
    for(i=0; i<N; i++){
        if(mark_team[i]==0){
            link_team[ii] = i;
            ii++;
        }else {
            start_team[jj] = i;
            jj++;
        }
    }
    for(i=0; i<N/2; i++){
        for(j=i+1; j<N/2; j++){
            link = link + power[link_team[i]][link_team[j]] + power[link_team[j]][link_team[i]];
            start = start + power[start_team[i]][start_team[j]] + power[start_team[j]][start_team[i]];
        }
    }
    return abs(start - link);
}


void dfs1(int start_mem_num, int selected_i, int mark_team[]){
    int i, j;
    if(start_mem_num == N/2){
        min_ = min(min_, get_team_power1(mark_team));
    }

    for(i=selected_i+1; i<N; i++){
        mark_team[i]=1;
        dfs1(start_mem_num+1, i, mark_team);
        mark_team[i]=0;
    }
}



int main()
{
    int i, j;
    cin >> N;

    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            cin >> power[i][j];
        }
    }

    int mark_team[N]={0,};
    mark_team[0]=1;
    dfs1(1, 0, mark_team);

    cout << min_;

}