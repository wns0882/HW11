#include<stdio.h>
#include<stdlib.h>
#define MAX_VERTICES 10
#define MAX_QUEUE_SIZE 100
#define TRUE 1
#define FALSE 0
int visited[MAX_VERTICES];
typedef int element;
typedef struct {
	element  queue[MAX_QUEUE_SIZE];
	int  front, rear;
} QueueType;
void init(QueueType *q)
{
	q->front = q->rear = 0;
}
// 공백 상태 검출 함수
int is_empty(QueueType *q)
{
	return (q->front == q->rear);
}
// 포화 상태 검출 함수
int is_full(QueueType *q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
// 삽입 함수
void enqueue(QueueType *q, element item)
{
	if (is_full(q))
		printf("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}
// 삭제 함수
element dequeue(QueueType *q)
{
	if (is_empty(q))
		printf("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}
// 삭제 함수
element peek(QueueType *q)
{
	if (is_empty(q))
		printf("큐가 공백상태입니다");
	return q->queue[(q->front + 1) % MAX_QUEUE_SIZE];
}
typedef struct GraphNode{
    int vertex;
    struct GraphNode* link; 
}Gnode;
typedef struct Head{
	 int n; //정점의 개수
	 struct GraphNode* Glist[MAX_VERTICES];
}Graphlist;   
int InitializeGraph(Graphlist* h);
void InsertVertex(Graphlist* h);
void InsertEdge(Graphlist*h, int u, int v);
void PrintGraph(Graphlist*h);
void DepthFirstSearch(Graphlist *h, int v);
void BreathFirstSearch(Graphlist*h, int v);
//DepthFirstSearch
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
		case 'z': case 'Z': //z를 입력받을 경우 
			InitializeGraph(graphnode); 
			break;
		case 'v': case 'V'://
			InsertVertex(graphnode);
			break; 
		case 'd': case 'D': //
			printf("vertex: ");
			scanf("%d",&num);
			DepthFirstSearch(graphnode,num);
			for(int i=0;i<MAX_VERTICES;i++){
				visited[i] = 0;
            }
			break;
		case 'p': case 'P': //d를 입력받을 경우 
			PrintGraph(graphnode);
			break;

		case 'e': case 'E': //r을 입력받을 경우 
			printf("your edge: ");
			scanf("%d %d",&u,&v);
			InsertEdge(graphnode,u ,v);			
			break;
		case 'b': case 'B':
			printf("vertex: ");
			scanf("%d",&num);
			BreathFirstSearch(graphnode, num); //t를 입력받을 경우
			break;
		case 'q': case 'Q':
			break;
		default: //위에 커맨드들 중 없는 경우를 입력하면 주의 메세지 출력
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}


	}while(command != 'q' && command != 'Q'); //q를 입력받기 전까지 반복문 실행

	return 1;
}
int InitializeGraph(Graphlist* h){
	h->n = 0;
	for(int i =0;i<MAX_VERTICES;i++){
		h->Glist[i] = NULL;
	}
	return 1;
}
void InsertVertex(Graphlist* h){
	if(((h->n)+1) > MAX_VERTICES){
		printf("vertex is full!!");
		return;
	}
	printf("Current vertex's Num: %d",h->n);
	h->n++;
	
	
}
void InsertEdge(Graphlist* h, int u, int v){
	if(u>=h->n || v>=h->n){
		return;
	}
	Gnode* node;
	node = (Gnode*)malloc(sizeof(Gnode));
	node->vertex = v;
	node->link = h->Glist[u];
	h->Glist[u] = node;
}
void PrintGraph(Graphlist* h){
	for(int i=0;i<h->n;i++){
		Gnode* pnode = h->Glist[i];
		printf("adjList[%d] ",i);
		while(pnode != NULL){
		printf("-> %d", pnode->vertex);
		pnode = pnode->link;
		}
		printf("\n");
	}
}
void BreathFirstSearch(Graphlist *h, int v){
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
void DepthFirstSearch(Graphlist *h, int v){
	Gnode *w;
	visited[v] = TRUE;   
	printf("%d ", v);   
for (w = h->Glist[v]; w; w = w->link){// 인접 정점 탐색 
	if (!visited[w->vertex]){
		DepthFirstSearch(h, w->vertex);
	}
 }
}





