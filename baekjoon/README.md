## Contents
* [1753. 최단경로](#1753)
* [3190. 뱀](#3190)
* [17140. 이차원 배열과 연산](#17140)


***
<a name="3190"/>

# 3190. 뱀

```cpp
typedef struct Snake{
	Snake(int l, int d) : length(l), dir(d) {}
	queue<pair<int,int>> body;
	int length;
	int dir;
}Snake;
```
* body: 뱀의 몸이 위치한 좌표를 queue에 저장. body의 front는 tail, back은 head.
* length: 뱀의 전체 길이
* dir: 뱀의 방향(UP, RIGHT, DOWN, LEFT)

	`vector<pair<int,char>> snake_dir_info;`

* input으로 받아올 뱀의 방향 변환 정보를 저장. pair의 first에는 초, second에는 방향(왼쪽, 오른쪽)   


	`int Dummy_start(Snake snake)`

while loop를 돌며 map을 수정  
0: 빈칸, 1: 뱀, 9: 사과
1. 현재 방향에 따라 머리가 위치하게 될 좌표를 구한다.
2. 좌표가 유효한지 확인한다.
	* 벽에 닿거나 자기 몸에 부딪히면 return
3. 늘린 머리를 body queue에 추가한다.
4. 머리의 위치에 사과가 없으면
	* map에서 꼬리를 없앤다.
	* body queue를 pop한다.
5. 늘린 머리를 map에 1로 표시해준다.
6. 시간을 체크해 현재 시간이 방향을 바꿔야 할 시간이라면 snake의 dir(방향)을 바꿔준다.
	* snake.dir을 업데이트하고 snake_dir_info는 pop해준다.
  
	`int Dummy_start(Snake snake)`
***
<a name="17140"/>

# 17140. 이차원 배열과 연산

`int array_sorting()`

`arr[r][c]=k`가 될 때까지 아래를 반복한다.
1. `row의 길이 ≥ col의 길이`이면 `R_calculate()` R 연산 실행
2. `row의 길이 < col의 길이`이면 `C_calculate()` C 연산 실행
3. `sec`(시간) += 1
4. `sec`이 100보다 크다면 -1 리턴

  
`void C_calculate()`

아래를 반복한다.
1. 세로 한 줄을 `vector v`에 넣는다.
2. v를 오름차순으로 정렬한다.
3. `pair p` 배열에 숫자와 숫자의 개수를 저장한다.
```cpp
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
```
`p[x].first`에는 숫자가, `p[x].second`에는 개수가 저장된다.
4. `pair p`배열을 second를 우선순위로 정렬한다.
5. `pair p` 배열을 이용해 `arr`배열에 업데이트 한다.
6. `max_len`을 구하고 `row_len`(행 크기)를 max_len으로 업데이트한다.
```cpp
max_len = max(max_len, rlength[i]);
max_len = min(max_len, 100); // 100을 넘지 않도록
row_len = max_len;
```
7. rlength 이후부터 업데이트 된 row size까지 0을 추가한다.

  
`R_calculate()`도 동일하다.

***
<a name="1753"/>

# 1753. 최단경로

간선 정보를 저장할 2차원 배열을 만들었더니 노드가 최대 20000개여서 크기가 너무 컸다.
`vector<pair<int, int>> adj_node[V];`
로 간선 정보를 저장했다. `adj_node[i][j].first`는 i 노드와 인접한 노드 숫자이고, `adj_node[i][j].second`는 i 노드에서 인접한 노드까지의 가중치이다.   

```cpp
int dist[V]; fill_n(dist, V, INF);
dist[K] = 0;
```
`dist`에는 K에서 출발해서 해당 노드까지 도달했을 때 드는 최소 비용을 저장한다.   

`priority_queue<pair<int, int>, vector<pair<int, int>>, compare> h;`
first에 노드 번호, second에 가중치를 저장한다. 우선순위는 second로 두었다.
1. `h`의 top 노드를 빼고, 인접한 노드들을 돌면서 w를 계산한다.
2. 계산된 w가 저장된 `dist`보다 작다면 업데이트하고, `h`에 정보를 push한다.   
h가 빌때까지 위 과정을 반복한다.
