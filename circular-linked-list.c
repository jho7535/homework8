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

typedef struct Node {	//노드 구조체 정의
	int key;	//노드에 입력할 값 변수
	struct Node* llink;	//왼쪽으로 이동할 링크 포인터
	struct Node* rlink;	//오른쪽으로 이동할 링크 포인터
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
	printf("[----- [Jeong Hanul] [2020039076] -----]\n\n");


	char command;	//명령어를 입력 받을 변수
	int key;	//값을 입력 받을 변수
	listNode* headnode=NULL;	//헤드 노드를 선언하고 NULL 값으로 초기화

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
		scanf(" %c", &command);	//명령어를 입력받아 command에 저장

		switch(command) {
		case 'z': case 'Z':	//z or Z 입력 시
			initialize(&headnode);
			break;
		case 'p': case 'P':	//p or P 입력 시
			printList(headnode);
			break;
		case 'i': case 'I':	//i or I 입력 시
			printf("Your Key = ");
			scanf("%d", &key);	//노드에 넣을 key 값 입력
			insertNode(headnode, key);
			break;
		case 'd': case 'D':	//d or D 입력 시
			printf("Your Key = ");
			scanf("%d", &key);	//노드에서 삭제할 key 값 입력
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':	//n or N 입력 시
			printf("Your Key = ");
			scanf("%d", &key);	//마지막 노드에 넣을 key 값 입력
			insertLast(headnode, key);
			break;
		case 'e': case 'E':	//e or E 입력 시
			deleteLast(headnode);
			break;
		case 'f': case 'F':	//f or F 입력 시
			printf("Your Key = ");
			scanf("%d", &key);	//처음 노드에 넣을 key 값 입력
			insertFirst(headnode, key);
			break;
		case 't': case 'T':	//t or T 입력 시
			deleteFirst(headnode);
			break;
		case 'r': case 'R':	//r or R 입력 시
			invertList(headnode);
			break;
		case 'q': case 'Q':	//q or Q 입력 시
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');	//q or Q 입력시 while문 탈출

	return 1;
}


int initialize(listNode** h) {	//헤드 노드를 초기화하는 함수

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));	//매개변수로 받은 헤드 노드 h에 listNode 사이즈만큼 동적 할당
	(*h)->rlink = *h;	//오른쪽 링크를 자기 자신으로 초기화
	(*h)->llink = *h;	//왼쪽 링크를 자기 자신으로 초기화
	(*h)->key = -9999;	//key값을 -9999로 초기화
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){ //모든 노드 메모리 해제하는 함수

	if(h->rlink == h) //헤드 노드 h의 오른쪽 링크가 자기 자신을 가리키면
	{
		free(h); //h 메모리 해제
		return 1;
	}

	listNode* p = h->rlink;	//리스트 노드 포인터 p를 선언하고 h의 오른쪽 링크로 초기화

	listNode* prev = NULL; //리스트 노드 포인터 prev를 선언하고 NULL로 초기화
	while(p != NULL && p != h) { //p가 NULL이 아니고 p가 h가 아닌 동안 반복
		prev = p; //prev에 p를 대입
		p = p->rlink;	//p에 오른쪽 링크가 가리키는 노드를 대입
		free(prev);	//prev 메모리 해제
	}
	free(h);	//h 메모리 해제
	return 0;
}



void printList(listNode* h) {	//리스트 노드의 순서와 값을 차례대로 출력하는 함수
	int i = 0;	//변수 i를 선언하고 0으로 초기화
	listNode* p;	//리스트 노드 포인터 p를 선언

	printf("\n---PRINT\n");

	if(h == NULL) {	//헤드 노드 h에 값이 없다면
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;	//p에 헤드 노드의 오른쪽 링크가 가리키는 노드 대입

	while(p != NULL && p != h) {	//p가 NULL이 아니고 p가 h가 아닌 동안 반복
		printf("[ [%d]=%d ] ", i, p->key);	//i번째의 key 값 출력
		p = p->rlink;	//p에 다음 노드를 대입
		i++;
	}
	printf("  items = %d\n", i);	//노드의 총 개수 출력


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);	//헤드 노드의 왼쪽 노드, 헤드 노드, 오른쪽 노드의 주소를 차례로 출력

	i = 0;	//i에 0 대입
	p = h->rlink;	//p에 헤드 노드의 오른쪽 링크가 가리키는 노드 대입
	while(p != NULL && p != h) {	//p가 NULL이 아니고 p가 h가 아닌 동안 반복
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);	//i번째의 key 값, 각 노드의 왼쪽 노드, 노드, 오른쪽 노드의 주소를 차례로 출력
		p = p->rlink;	//p에 다음 노드를 대입
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {	//노드에 값을 입력하고 가장 마지막 순서로 삽입하는 함수

	if (h == NULL) //헤드 노드가 NULL인 경우
		return -1;

	listNode* node = (listNode*)malloc(sizeof(listNode)); //리스트 노드 node를 선언하고 동적 할당
	node->key = key; //node의 key 값에 입력 받은 key 대입
	node->rlink = NULL; //node의 오른쪽 링크를 NULL로 초기화
	node->llink = NULL; //node의 왼쪽 링크를 NULL로 초기화

	if (h->rlink == h) //헤드 노드의 오른쪽 링크가 헤드 노드인 경우
	/* 첫 노드로 삽입 */
	{
		h->rlink = node; //헤드 노드의 오른쪽 링크에 node를 대입
		h->llink = node; //헤드 노드의 왼쪽 링크에 node를 대입
		node->rlink = h; //node의 오른쪽 링크에 헤드 노드 대입
		node->llink = h; //node의 왼쪽 링크에 헤드 노드 대입
	} else {
		h->llink->rlink = node; //헤드 노드의 왼쪽 노드의 오른쪽 링크에 node를 대입
		node->llink = h->llink; //node의 왼쪽 링크에 헤드 노드의 왼쪽 링크 대입
		h->llink = node; //헤드 노드의 왼쪽 링크에 node 대입
		node->rlink = h; //node의 오른쪽 링크에 헤드 노드 대입
	}

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {	//마지막 노드를 삭제하는 함수

	if (h->llink == h || h == NULL) //헤드 노드의 왼쪽 링크가 헤드 노드, 또는 헤드 노드가 NULL안 경우
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* nodetoremove = h->llink; //리스트 노드 포인터 nodetoremove를 선언하고 헤드 노드의 왼쪽 링크로 초기화

	/* link 정리 */
	nodetoremove->llink->rlink = h; //nodetoremove의 왼쪽 노드의 오른쪽 링크에 헤드 노드 대입
	h->llink = nodetoremove->llink; //헤드 노드의 왼쪽 링크에 nodetoremove의 왼쪽 링크 대입

	free(nodetoremove); //nodetoremove 메모리 해제

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {	//노드에 값을 입력하고 가장 처음 순서로 삽입하는 함수

	listNode* node = (listNode*)malloc(sizeof(listNode)); //리스트 노드 포인터 node를 선언하고 동적 할당

	node->key = key; //node의 key 값에 입력 받은 key 대입
	node->rlink = NULL; //node의 오른쪽 링크를 NULL로 초기화
	node->llink = NULL; //node의 왼쪽 링크를 NULL로 초기화


	node->rlink = h->rlink; //node의 오른쪽 링크에 헤드 노드의 오른쪽 링크 대입
	h->rlink->llink = node; //헤드 노드의 오른쪽 노드의 왼쪽 링크에 node 대입
	node->llink = h; //node의 왼쪽 링크에 h 대입
	h->rlink = node; //헤드 노드의 오른쪽 링크에 node 대입


	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {	//첫번째 노드를 삭제하는 함수

	if (h == NULL || h->rlink == h) //헤드 노드가 NULL, 또는 헤드 노드의 오른쪽 링크가 헤드 노드인 경우
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* nodetoremove = h->rlink; //리스트 노드 포인터 nodetoremove를 선언하고 헤드 노드의 오른쪽 링크로 초기화

	/* link 정리 */
	nodetoremove->rlink->llink = h; //nodetoremove의 오른쪽 노드의 왼쪽 링크에 헤드 노드 대입
	h->rlink = nodetoremove->rlink; //헤드 노드의 오른쪽 링크에 nodetoremove의 오른쪽 링크 대입

	free(nodetoremove); //nodetoremove 메모리 해제

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {	//노드의 순서를 역순으로 재배치하는 함수


	if(h->rlink == h || h == NULL) { //헤드 노드의 오른쪽 노드가 헤드 노드, 또는 헤드 노드가 NULL인 경우
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->rlink; //리스트 노드 포인터 n을 선언하고 헤드 노드의 오른쪽 링크로 초기화
	listNode *trail = h; //리스트 노드 포인터 trail을 선언하고 헤드 노드로 초기화
	listNode *middle = h; //리스트 노드 포인터 middle을 선언하고 헤드 노드로 초기화

	/* 최종 바뀔 링크 유지 */
	h->llink = h->rlink; //헤드 노드의 왼쪽 링크에 헤드 노드의 오른쪽 링크 대입

	while(n != NULL && n != h){ //n이 NULL, 헤드 노드가 아닌 동안
		trail = middle; //trail에 middle 대입
		middle = n; //middle에 n 대입
		n = n->rlink; //n에 n의 오른쪽 링크 대입
		middle->rlink = trail; //middle의 오른쪽 링크에 trail 대입
		middle->llink = n; //middle의 왼쪽 링크에 n 대입
	}

	h->rlink = middle; //헤드 노드의 오른쪽 링크에 middle 대입

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {	//노드에 값을 대입하는 함수

	if(h == NULL) return -1; //헤드 노드가 NULL인 경우

	listNode* node = (listNode*)malloc(sizeof(listNode)); //리스트 노드 포인터 node를 선언하고 동적 할당
	node->key = key; //node의 key 값에 입력 받은 key 대입
	node->llink = node->rlink = NULL; //node의 양쪽 포인터를 NULL로 초기화

	if (h->rlink == h) //헤드 노드의 오른쪽 링크가 헤드 노드인 경우 
	{
		insertFirst(h, key); //첫번째 순서로 삽입
		return 1;
	}

	listNode* n = h->rlink; //리스트 노드 포인터 n을 선언하고 헤드 노드의 오른쪽 링크로 초기화 

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL && n != h) { //n이 NULL, h가 아닌 동안
		if(n->key >= key) { //리스트 노드 n의 key 값이 입력 받은 key 값보다 크거나 같으면
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->rlink) { //n이 헤드 노드의 오른쪽 링크와 같다면
				insertFirst(h, key); //첫번째 순서로 삽입
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n; //node의 오른쪽 링크에 n 대입
				node->llink = n->llink; //node의 왼쪽 링크에 n의 왼쪽 링크 대입
				n->llink->rlink = node; //n의 왼쪽 노드의 오른쪽 링크에 node 대입
				n->llink = node; //n의 왼쪽 링크에 node 대입
			}
			return 0;
		}

		n = n->rlink; //n에 n의 오른쪽 링크 대입
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key); //마지막 순서로 삽입
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {	//해당하는 key 값인 노드 제거하는 함수

	if (h->rlink == h || h == NULL)  //헤드 노드의 오른쪽 링크가 헤드 노드, 또는 헤드 노드가 NULL인 경우
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->rlink; //리스트 노드 포인터 n을 선언하고 헤드 노드의 오른쪽 링크로 초기화

	while(n != NULL && n != h) { //n이 NULL, 헤드 노드가 아닌 동안
		if(n->key == key) {	//n의 key 값과 입력 받은 key 값이 같다면
			if(n == h->rlink) { /* 첫 번째 노드 인경우 */
				deleteFirst(h); //첫번째 노드 삭제
			} else if (n->rlink == h){ /* 마지막 노드인 경우 */
				deleteLast(h); //마지막 노드 삭제
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink; //n의 왼쪽 노드의 오른쪽 링크에 n의 오른쪽 링크 대입
				n->rlink->llink = n->llink; //n의 오른쪽 노드의 왼쪽 링크에 n의 왼쪽 링크 대입
				free(n); //n 메모리 해제
			}
			return 0;
		}

		n = n->rlink; //n에 n의 오른쪽 링크 대입
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 0;
}
