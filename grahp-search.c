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
// ���� ���� ���� �Լ�
int is_empty(QueueType *q)
{
	return (q->front == q->rear);
}
// ��ȭ ���� ���� �Լ�
int is_full(QueueType *q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
// ���� �Լ�
void enqueue(QueueType *q, element item)
{
	if (is_full(q))
		printf("ť�� ��ȭ�����Դϴ�");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}
// ���� �Լ�
element dequeue(QueueType *q)
{
	if (is_empty(q))
		printf("ť�� ��������Դϴ�");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}
// ���� �Լ�
element peek(QueueType *q)
{
	if (is_empty(q))
		printf("ť�� ��������Դϴ�");
	return q->queue[(q->front + 1) % MAX_QUEUE_SIZE];
}
typedef struct GraphNode{
    int vertex;
    struct GraphNode* link; 
}Gnode;
typedef struct Head{
	 int n; //������ ����
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
	char command; //Ŀ�ǵ带 �Է¹��� ���� ����
	int key; //int�� ���� key ���� 
	Graphlist* graphnode  = (Graphlist*)malloc(sizeof(Graphlist));
	int u,v;
	int num;
	 	

	do{
		printf("\n\n");
		printf("[----- [���ؿ�] [2019038010] -----]");
        printf("----------------------------------------------------------------\n");
		printf("                   Graph Searches                               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph       = z                                     \n");
		printf(" Insert Vertex          = v      Insert Edge                = e \n");
		printf(" Depth First Search     = d      Breath First Search        = b \n");
		printf(" Print Graph            = p      Quit                       = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);//command �Է� �޴´�

		switch(command) {
		case 'z': case 'Z': //z�� �Է¹��� ��� 
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
		case 'p': case 'P': //d�� �Է¹��� ��� 
			PrintGraph(graphnode);
			break;

		case 'e': case 'E': //r�� �Է¹��� ��� 
			printf("your edge: ");
			scanf("%d %d",&u,&v);
			InsertEdge(graphnode,u ,v);			
			break;
		case 'b': case 'B':
			printf("vertex: ");
			scanf("%d",&num);
			BreathFirstSearch(graphnode, num); //t�� �Է¹��� ���
			break;
		case 'q': case 'Q':
			break;
		default: //���� Ŀ�ǵ�� �� ���� ��츦 �Է��ϸ� ���� �޼��� ���
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}


	}while(command != 'q' && command != 'Q'); //q�� �Է¹ޱ� ������ �ݺ��� ����

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
	init(&q);    				// ť �ʱ� ȭ 
	visited[v] = TRUE;      // ���� v �湮 ǥ�� 
	printf("%d ", v);          // �湮�� ���� ��� 
	enqueue(&q, v);			// ���������� ť�� ���� 
	while (!is_empty(&q)) {
		v = dequeue(&q);		// ť�� ����� ���� ���� 
		for (w = h->Glist[v]; w; w = w->link) //���� ���� Ž��
			if (!visited[w->vertex]) {	// �̹湮 ���� Ž�� 
				visited[w->vertex] = TRUE;   // �湮 ǥ��
				printf("%d ", w->vertex);
				enqueue(&q, w->vertex);	//������ ť�� ����
			}
	}
}
void DepthFirstSearch(Graphlist *h, int v){
	Gnode *w;
	visited[v] = TRUE;   
	printf("%d ", v);   
for (w = h->Glist[v]; w; w = w->link){// ���� ���� Ž�� 
	if (!visited[w->vertex]){
		DepthFirstSearch(h, w->vertex);
	}
 }
}





