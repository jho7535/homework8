/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  School of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){

	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {

	if (h == NULL) //h가 NULL이면, 
	return -1;

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode의 크기만큼 listNode의 포인터 node에 저장
	node->key = key; //node의 key 부분에 입력받은 key 저장
	node->rlink = NULL; //node의 rlink NULL로 초기화
	node->llink = NULL; //node의 llink NULL로 초기화

	if (h->rlink == h) //h의 rlink가 h일 경우
	/* 첫 노드로 삽입 */
	{
		h->rlink = node; //h의 rlink에 node 저장
		h->llink = node; //h의 llink에 node 저장
		node->rlink = h; //node의 rlink에 h 저장
		node->llink = h; //node의 llink에 h 저장
	} else {
		h->llink->rlink = node; //h의 llink의 rlink에 node 저장
		node->llink = h->llink; //node의 llink에 h의 llink 저장
		h->llink = node; //h의 llink에 node 저장
		node->rlink = h; //node의 rlink에 h 저장
	}

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {

	if (h->llink == h || h == NULL) //h의 llink가 h이거나 h가 NULL일 경우 node가 존재하지 않을 경우
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* nodetoremove = h->llink; //listNode의 포인터 nodetoremove에 h의 llink 저장

	/* link 정리 */
	nodetoremove->llink->rlink = h; //nodetoremove의 llink의 rlink에 h 저장
	h->llink = nodetoremove->llink; //h의 llink에 nodetoremove의 llink 저장

	free(nodetoremove); //nodetoremove에 할당된 메모리 해제

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); 
	//listNode의 포인터 node에 listNode의 크기만큼 메모리 할당
	node->key = key; //node의 key 부분에 입력받은 key 저장
	node->rlink = NULL; //node의 rlink NULL로 초기화
	node->llink = NULL; //node의 llink NULL로 초기화


	node->rlink = h->rlink; //node의 rlink에 h의 rlink 저장
	h->rlink->llink = node; //h의 rlink의 llink에 node 저장
	node->llink = h; //node의 llink에 h 저장
	h->rlink = node; //h의 rlink에 node 저장


	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {

	if (h == NULL || h->rlink == h) //h가 NULL이거나 h의 rlink가 h일 경우
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* nodetoremove = h->rlink; //listNode의 포인터 nodetoremove에 h의 rlink 저장

	/* link 정리 */
	nodetoremove->rlink->llink = h; //nodetoremove의 rlink의 llink에 h 저장
	h->rlink = nodetoremove->rlink; //h의 rlink에 nodetoremove의 rlink 저장

	free(nodetoremove); //nodetoremove에 할당된 메모리 해제

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {


	if(h->rlink == h || h == NULL) { //h의 rlink가 h이거나 h가 NULL일 경우
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->rlink; //listNode의 포인터 n에 h의 rlink 저장 
	listNode *trail = h; //listNode의 포인터 trail에 h 저장
	listNode *middle = h; //listNode의 포인터 middle에 h 저장

	/* 최종 바뀔 링크 유지 */
	h->llink = h->rlink; //h의 llink에 h의 rlink 저장

	while(n != NULL && n != h){ //n이 NULL이 아니고 h도 아닐동안
		trail = middle; //trail에 middle 저장
		middle = n; //middle에 n 저장
		n = n->rlink; //n에 n의 rlink 저장
		middle->rlink = trail; //middle의 rlink에 trail 저장
		middle->llink = n; //middle의 llink에 n 저장
	}

	h->rlink = middle; //h의 rlink에 middle 저장

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {

	if(h == NULL) return -1; //h가 NULL일 경우 노드가 존재하지 않을 경우

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode의 포인터 node에 listNode의 크기만큼 메모리할당
	node->key = key; //node의 key부분에 입력받은 key 저장
	node->llink = node->rlink = NULL; //node의 llink에 node의 rlink 저장,NULL로 초기화

	if (h->rlink == h) //h의 rlink가 h일 경우 
	{
		insertFirst(h, key); //첫번째 노드에 삽입
		return 1;
	}

	listNode* n = h->rlink; //listNode의 n에 h의 rlink 저장

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL && n != h) { //n이 NULL이 아니고 h도 아닐 경우
		if(n->key >= key) { //n의 key가 입력받은 key 보다 클 경우
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->rlink) { //n이 h의 rlink라면
				insertFirst(h, key); //첫번째노드에 삽입
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n; //node의 rlink에 n 저장
				node->llink = n->llink; //node의 llink에 n의 llink 저장
				n->llink->rlink = node; //n의 llink의 rlink에 node 저장
				n->llink = node; //n의 llink에 node 저장
			}
			return 0;
		}

		n = n->rlink; //n에 n의 rlink 저장
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key); //마지막 노드에 삽입
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {

	if (h->rlink == h || h == NULL)  //h의 rlink가 h이거나 h가 NULL일 경우
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->rlink; //listNode의 포인터 n에 h의 rlink 저장

	while(n != NULL && n != h) { //n이 NULL이 아니고 h도 아닐 동안 (노드가 존재할 동안)
		if(n->key == key) { //n의key가 입력받은 key와 같을 때
			if(n == h->rlink) { /* 첫 번째 노드 인경우 */
				deleteFirst(h); //첫번째노드삭제
			} else if (n->rlink == h){ /* 마지막 노드인 경우 */
				deleteLast(h); //마지막노드삭제
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink; //n의 llink의 rlink에 n의 rlink 저장
				n->rlink->llink = n->llink; //n의 rlink의 llink에 n의 llink 저장
				free(n); //n에 할당된 메모리 해제
			}
			return 0;
		}

		n = n->rlink; //n에 n의 rlink 저장
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 0;
}
