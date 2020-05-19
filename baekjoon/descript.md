## Contents
* [3190. 뱀](#3100)


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