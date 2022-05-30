#include<stdio.h>
#include<stdlib.h>
#define MAX_VERTICES 10 //vertex의 최대 수 정의
#define MAX_QUEUE_SIZE 100//큐의 최대 수 정의
#define TRUE 1
#define FALSE 0
int visited[MAX_VERTICES];//배열을 전역 변수로 정의
typedef int element;//int 자료형을 element로 정의
typedef struct { //자료구조 큐를 사용하기 위해 큐 구조체 정의
	element  queue[MAX_QUEUE_SIZE];
	int  front, rear;
} QueueType; //구조체 별칭 QueueType 선언
void init(QueueType *q) 
{
	q->front = q->rear = 0;
}
int is_empty(QueueType *q) // 공백 상태 검출 함수
{
	return (q->front == q->rear);
}
int is_full(QueueType *q)// 포화 상태 검출 함수
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
void enqueue(QueueType *q, element item)// 삽입 함수
{
	if (is_full(q))
		printf("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}

element dequeue(QueueType *q) //삭제 함수
{
	if (is_empty(q))
		printf("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}

/*element peek(QueueType *q)
{
	if (is_empty(q))
		printf("큐가 공백상태입니다");
	return q->queue[(q->front + 1) % MAX_QUEUE_SIZE];
}*/
typedef struct GraphNode{ //GraphNode 구조체 선언
    int vertex;
    struct GraphNode* link; 
}Gnode; //별칭 설정
typedef struct Head{
	 int n; //정점의 개수
	 struct GraphNode* Glist[MAX_VERTICES];//그래프 인접 리스트 저장 할 배열 선언
}Graphlist;//별칭 설정
int InitializeGraph(Graphlist* h);
void InsertVertex(Graphlist* h);
void InsertEdge(Graphlist*h, int u, int v);
void PrintGraph(Graphlist*h);
void DepthFirstSearch(Graphlist *h, int v);
void BreathFirstSearch(Graphlist*h, int v);
int main()
{
	char command; //커맨드를 입력받을 변수 선언
	int key; //int형 변수 key 선언 
	Graphlist* graphnode  = (Graphlist*)malloc(sizeof(Graphlist));
	int u,v;
	int num;
	 	

	do{
		printf("\n\n");
		printf("[----- [박준용] [2019038010] -----]");
        printf("----------------------------------------------------------------\n");
		printf("                   Graph Searches                               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph       = z                                     \n");
		printf(" Insert Vertex          = v      Insert Edge                = e \n");
		printf(" Depth First Search     = d      Breath First Search        = b \n");
		printf(" Print Graph            = p      Quit                       = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);//command 입력 받는다

		switch(command) {
		case 'z': case 'Z': //z를 입력받은 경우 
			InitializeGraph(graphnode); 
			break;
		case 'v': case 'V'://v를 입력받은 경우
			InsertVertex(graphnode);
			break; 
		case 'd': case 'D': //d를 입력받은 경우
			printf("vertex: ");
			scanf("%d",&num);
			DepthFirstSearch(graphnode,num);
			for(int i=0;i<MAX_VERTICES;i++){ //dfs,bfs를 실행했을 때 visite 배열 초기화
				visited[i] = 0;
            }
			break;
		case 'p': case 'P': //p를 입력받은 경우 
			PrintGraph(graphnode);
			break;

		case 'e': case 'E': //e를 입력받을 경우 
			printf("your edge: ");
			scanf("%d %d",&u,&v);
			InsertEdge(graphnode,u ,v);			
			break;
		case 'b': case 'B'://b를 입력받은 경우
			printf("vertex: ");
			scanf("%d",&num);
			BreathFirstSearch(graphnode, num); 
			break;
		case 'q': case 'Q'://q를 입력받은 경우
			break;
		default: //위에 커맨드들 중 없는 경우를 입력하면 주의 메세지 출력
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}


	}while(command != 'q' && command != 'Q'); //q를 입력받기 전까지 반복문 실행

	return 1;
}
int InitializeGraph(Graphlist* h){ //그래프를 초기화 해주는 함수
	h->n = 0;
	for(int i =0;i<MAX_VERTICES;i++){
		h->Glist[i] = NULL; //Glist를 NULL로 초기화
	}
	return 1;
}
void InsertVertex(Graphlist* h){ //vertex를 추가하는 함수
	if(((h->n)+1) > MAX_VERTICES){ //vertex가 10개가 채워졌을 때 오류 메세지 출력
		printf("vertex is full!!");
		return;
	}
	printf("Current vertex's Num: %d",h->n);//현재 vertex 수 출력
	h->n++;//vertex 갯수 증가
	
	
}
void InsertEdge(Graphlist* h, int u, int v){//그래프 노드의 edge를 추가하는 함수
	if(u>=h->n || v>=h->n){ //입력한 노드가 없는 경우  리턴 
		return;
	}
	Gnode* node;
	node = (Gnode*)malloc(sizeof(Gnode));
	node->vertex = v; //새로운 노드에 입력받은 노드 저장
	node->link = h->Glist[u];//리스트안에 저장된 노드와 연결
	h->Glist[u] = node;//양쪽 노드를 연결
}
void PrintGraph(Graphlist* h){//그래프를 출력하는 함수
	for(int i=0;i<h->n;i++){ 
		Gnode* pnode = h->Glist[i]; //그래프를 저장하는 리스트를 대입
		printf("adjList[%d] ",i);
		while(pnode != NULL){ //리스트의 끝까지 반복
		printf("-> %d", pnode->vertex); //노드의 값 출력
		pnode = pnode->link;//노드를 한칸씩 이동
		}
		printf("\n");
	}
}
void BreathFirstSearch(Graphlist *h, int v){ //넓이 우선 탐색
	Gnode* w;
	QueueType q;
	init(&q);    				// 큐 초기 화 
	visited[v] = TRUE;      // 정점 v 방문 표시 
	printf("%d ", v);          // 방문한 정점 출력 
	enqueue(&q, v);			// 시작정점을 큐에 저장 
	while (!is_empty(&q)) {
		v = dequeue(&q);		// 큐에 저장된 정점 선택 
		for (w = h->Glist[v]; w; w = w->link) //인접 정점 탐색
			if (!visited[w->vertex]) {	// 미방문 정점 탐색 
				visited[w->vertex] = TRUE;   // 방문 표시
				printf("%d ", w->vertex);
				enqueue(&q, w->vertex);	//정점을 큐에 삽입
			}
	}
}
void DepthFirstSearch(Graphlist *h, int v){//깊이 우선 탐색
	Gnode *w;
	visited[v] = TRUE;   //방문한 노드를 표시
	printf("%d ", v);   //탐색한 노드의 값 출력
for (w = h->Glist[v]; w; w = w->link){
	if (!visited[w->vertex]){ //노드의 값이 존재하지 않으면 다음 탐색 실행
		DepthFirstSearch(h, w->vertex);//다음 노드 탐색 실행
	}
 }
}





