#include<stdio.h>
#include<stdlib.h>
#define MAX_VERTICES 10 //vertex�� �ִ� �� ����
#define MAX_QUEUE_SIZE 100//ť�� �ִ� �� ����
#define TRUE 1
#define FALSE 0
int visited[MAX_VERTICES];//�迭�� ���� ������ ����
typedef int element;//int �ڷ����� element�� ����
typedef struct { //�ڷᱸ�� ť�� ����ϱ� ���� ť ����ü ����
	element  queue[MAX_QUEUE_SIZE];
	int  front, rear;
} QueueType; //����ü ��Ī QueueType ����
void init(QueueType *q) 
{
	q->front = q->rear = 0;
}
int is_empty(QueueType *q) // ���� ���� ���� �Լ�
{
	return (q->front == q->rear);
}
int is_full(QueueType *q)// ��ȭ ���� ���� �Լ�
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
void enqueue(QueueType *q, element item)// ���� �Լ�
{
	if (is_full(q))
		printf("ť�� ��ȭ�����Դϴ�");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}

element dequeue(QueueType *q) //���� �Լ�
{
	if (is_empty(q))
		printf("ť�� ��������Դϴ�");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}

/*element peek(QueueType *q)
{
	if (is_empty(q))
		printf("ť�� ��������Դϴ�");
	return q->queue[(q->front + 1) % MAX_QUEUE_SIZE];
}*/
typedef struct GraphNode{ //GraphNode ����ü ����
    int vertex;
    struct GraphNode* link; 
}Gnode; //��Ī ����
typedef struct Head{
	 int n; //������ ����
	 struct GraphNode* Glist[MAX_VERTICES];//�׷��� ���� ����Ʈ ���� �� �迭 ����
}Graphlist;//��Ī ����
int InitializeGraph(Graphlist* h);
void InsertVertex(Graphlist* h);
void InsertEdge(Graphlist*h, int u, int v);
void PrintGraph(Graphlist*h);
void DepthFirstSearch(Graphlist *h, int v);
void BreathFirstSearch(Graphlist*h, int v);
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
		case 'v': case 'V'://v�� �Է¹��� ���
			InsertVertex(graphnode);
			break; 
		case 'd': case 'D': //d�� �Է¹��� ���
			printf("vertex: ");
			scanf("%d",&num);
			DepthFirstSearch(graphnode,num);
			for(int i=0;i<MAX_VERTICES;i++){ //dfs,bfs�� �������� �� visite �迭 �ʱ�ȭ
				visited[i] = 0;
            }
			break;
		case 'p': case 'P': //p�� �Է¹��� ��� 
			PrintGraph(graphnode);
			break;

		case 'e': case 'E': //e�� �Է¹��� ��� 
			printf("your edge: ");
			scanf("%d %d",&u,&v);
			InsertEdge(graphnode,u ,v);			
			break;
		case 'b': case 'B'://b�� �Է¹��� ���
			printf("vertex: ");
			scanf("%d",&num);
			BreathFirstSearch(graphnode, num); 
			break;
		case 'q': case 'Q'://q�� �Է¹��� ���
			break;
		default: //���� Ŀ�ǵ�� �� ���� ��츦 �Է��ϸ� ���� �޼��� ���
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}


	}while(command != 'q' && command != 'Q'); //q�� �Է¹ޱ� ������ �ݺ��� ����

	return 1;
}
int InitializeGraph(Graphlist* h){ //�׷����� �ʱ�ȭ ���ִ� �Լ�
	h->n = 0;
	for(int i =0;i<MAX_VERTICES;i++){
		h->Glist[i] = NULL; //Glist�� NULL�� �ʱ�ȭ
	}
	return 1;
}
void InsertVertex(Graphlist* h){ //vertex�� �߰��ϴ� �Լ�
	if(((h->n)+1) > MAX_VERTICES){ //vertex�� 10���� ä������ �� ���� �޼��� ���
		printf("vertex is full!!");
		return;
	}
	printf("Current vertex's Num: %d",h->n);//���� vertex �� ���
	h->n++;//vertex ���� ����
	
	
}
void InsertEdge(Graphlist* h, int u, int v){//�׷��� ����� edge�� �߰��ϴ� �Լ�
	if(u>=h->n || v>=h->n){ //�Է��� ��尡 ���� ���  ���� 
		return;
	}
	Gnode* node;
	node = (Gnode*)malloc(sizeof(Gnode));
	node->vertex = v; //���ο� ��忡 �Է¹��� ��� ����
	node->link = h->Glist[u];//����Ʈ�ȿ� ����� ���� ����
	h->Glist[u] = node;//���� ��带 ����
}
void PrintGraph(Graphlist* h){//�׷����� ����ϴ� �Լ�
	for(int i=0;i<h->n;i++){ 
		Gnode* pnode = h->Glist[i]; //�׷����� �����ϴ� ����Ʈ�� ����
		printf("adjList[%d] ",i);
		while(pnode != NULL){ //����Ʈ�� ������ �ݺ�
		printf("-> %d", pnode->vertex); //����� �� ���
		pnode = pnode->link;//��带 ��ĭ�� �̵�
		}
		printf("\n");
	}
}
void BreathFirstSearch(Graphlist *h, int v){ //���� �켱 Ž��
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
void DepthFirstSearch(Graphlist *h, int v){//���� �켱 Ž��
	Gnode *w;
	visited[v] = TRUE;   //�湮�� ��带 ǥ��
	printf("%d ", v);   //Ž���� ����� �� ���
for (w = h->Glist[v]; w; w = w->link){
	if (!visited[w->vertex]){ //����� ���� �������� ������ ���� Ž�� ����
		DepthFirstSearch(h, w->vertex);//���� ��� Ž�� ����
	}
 }
}





