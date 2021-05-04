/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}

void inorderTraversal(Node* ptr) //중위 순회로 키값을 출력한다
{
	if(ptr) //ptr의 값이 NULL이 아닐때 조건문 실행
	{
		inorderTraversal(ptr->left); //inorderTraversal을 ptr의 왼쪽 자식으로 노드를 전달해 재귀함수를 호출
		printf("[ %d ]\t", ptr->key); /*가장 아래 레벨의 자손에 왼쪽값을 출력후 그 노드의 부모노드로 올라와 부모노드를 출력한다.
		부모노드의 오른쪽 자식노드가 있을 시 오른쪽 자식노드 출력 후 부모노드의 부모노드로 올라가 같은방식으로 출력*/
		inorderTraversal(ptr->right); //inorderTraversal을 ptr의 오른쪽 자식으로 노드를 전달해 재귀함수를 호출
	}

}

void preorderTraversal(Node* ptr) //전위 순회로 키값을 출력한다
{
	if(ptr) //ptr의 값이 NULL이 아닐때 조건문 실행
	{
		printf("[ %d ]\t", ptr->key); //루트노드 부터 출력하며, 왼쪽 자식노드를 순서대로 출력후 가장 아래에 있는 오른쪽 자식노드부토 루트노드로 올라오며 출력
		preorderTraversal(ptr->left); //preorderTraversal을 ptr의 왼쪽 자식으로 노드를 전달해 재귀함수를 호출
		preorderTraversal(ptr->right); //preorderTraversal을 ptr의 오른쪽 자식으로 노드를 전달해 재귀함수를 호출
	}
}

void postorderTraversal(Node* ptr) //후위 순회로 키값을 출력한다
{
	if(ptr) //ptr의 값이 NULL이 아닐때 조건문 실행
	{
		postorderTraversal(ptr->left); //postorderTraversal를 ptr의 왼쪽 자식으로 노드를 전달해 재귀함수를 호출
		postorderTraversal(ptr->right); //postorderTraversal를 ptr의 오른쪽 자식으로 노드를 전달해 재귀함수를 호출
		printf("[ %d ]\t", ptr->key); /*가장 아래있는 왼쪽 자식노드를 가 먼저 출력하고 그 노드의 부모노드의 오른쪽 자식이 있을 경우 오른쪽 자식노드도 출력한다
		그 다음 부모노드로 올라가 같은 방식으로 출력한다.*/
	}
}

int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node)); //새노드 newNode 동적할당 한다
	Node* temp = head->left; //임시로 쓰일 temp노드를 root로 가져온다
	Node* parent = NULL; //부모노드 임시 설정

	newNode->key = key; //newNode의 값에 key값을 넣는다
	newNode -> left = NULL; //newNode의 left를 NULL로 설정
	newNode -> right = NULL; //newNode의 right를 NULL로 설정
 
	
	if(temp == NULL) //temp가 NULL일때 즉 루트가 아무것도 없을때
	{
		head ->left = newNode; //head의 left를 newNode로 설정
		return 0; //0리턴을 통해 함수 종료
	}
	
	while(temp != NULL) //temp가 NULL이 아닐경우 반복
	{
		if(temp->key > key) //temp노드 안에 값이 key보다 클경우
		{
			parent = temp; //부모노드를 temp로 설정
			temp = temp->left; //temp를 왼쪽 자식노드로 이동
			if(temp == NULL) //만약 temp가 NULL일경우
			{
				parent->left = newNode; //부모노드의 왼쪽노드로 newNode로 설정
				return 0; //0리턴을 통해 함수 종료
			}
		}
		else //그렇지 않을 경우
		{
			parent = temp; //부모노드를 temp로 설정
			temp = temp->right; //temp를 오른쪽 자식노드로 이동
			if(temp == NULL) //만약 temp가 NULL일경우
			{
				parent->right = newNode; //부모노드의 오른쪽노드로 newNode로 설정
				return 0; //0리턴을 통해 함수 종료
			}

		}
	}
	return 0; //0리턴을 통해 함수 종료
}

int deleteLeafNode(Node* head, int key)
{
	Node* temp = head->left; //임시로 쓰일 temp노드를 root로 가져온다
	Node* parent = NULL; //부모노드 임시 설정

	if(temp->key == key) //temp노드 안에 값이 key일 경우
	{
		if(temp->right == NULL && temp->left == NULL) //temp가 leaf 노드일 경우, 즉 찾는 값이 루트노드에 있는 경우
		{
			head->left = NULL; //헤드의 left를 NULL로 설정
			free(temp); //루트노드 삭제
			return 0; //0리턴을 통해 함수 종료
		}
		else //그렇지 않을 경우
		{
			printf("The node [%d] is not a leaf", key); 
			return 0; //0리턴을 통해 함수 종료
		}
	}
	while(temp != NULL) //temp가 NULL이 아닐경우 반복한다
	{
		parent = temp; //부모노드를 temp로 설정
		if(temp->key > key) //temp노드 안에 값이 key보다 클경우
		{
			if(temp->left != NULL) //temp의 완쪽 자식이 NULL이 아닐경우
			{
				temp = temp->left; //temp를 왼쪽 자식으로 이동

				if(temp->key == key) //temp노드 안에 값이 key일경우
				{
					if(temp->right == NULL && temp->left == NULL) //temp가 leaf 노드일 경우
					{
						parent->left = NULL; //부모노드의 왼쪽자식노드 가리키는 값을 NULL로 설정
						free(temp); //temp 노드 삭제
						return 0; //0리턴을 통해 함수 종료
					}
					else //그렇지 않을 경우
					{
						printf("The node [%d] is not a leaf", key);
						return 0; //0리턴을 통해 함수 종료
					}
				}
			}
		}
		else if (temp->key < key) //temp노드 안에 값이 key보다 작을경우
		{
			if(temp->right != NULL) //temp의 오른쪽 자식노드가 NULL이 아닐경우
			{
				temp = temp->right; //temp를 오른쪽 자식노드로 이동
			
				if(temp->key == key) //temp노드 안에값이 key일경우
				{
					if(temp->right == NULL && temp->left == NULL) //temp노드가 leaf노드 일경우
					{
						parent->right = NULL; //부모 노드의 오른쪽 자식을 가리키는 값을 NULL로 설정
						free(temp); //temp 노드 삭제
						return 0; //0리턴을 통해 함수 종료
					}
					else //그렇지 않을 경우
					{
						printf("The node [%d] is not a leaf", key);
						return 0; //0리턴을 통해 함수 종료
					}
				}	
			}
		}
	}
	return 0; //0리턴을 통해 함수 종료
}

Node* searchRecursive(Node* ptr, int key)
{
	if(!ptr) //ptr이 아닐경우
		return NULL; //NULL리턴으로 함수종료
	if(key == ptr->key) //key값이 ptr노드안에 값일 경우
		return ptr; //ptr을 리턴함으로서 함수 종료
	if(key < ptr->key) //ptr노드 안에 값이 key보다 클경우
		return searchRecursive(ptr->left, key); //ptr의 왼쪽 자식으로 이동하고, searchRecursive 재귀함수로 부른다.
	return searchRecursive(ptr->right, key); //ptr의 오른쪽 자식으로 이동하고, searchRecursive 재귀함수로 부른다.
}

Node* searchIterative(Node* head, int key)
{
	Node* temp = head->left; //temp노드를 루트 노드로 설정
	
	while(temp) //temp가 NULL이 아닐경우 반복한다
	{
		if(key == temp->key) //temp노드 안에 값이 key일경우
			return temp; //temp노드를 리턴함으로서 함수 종료
		if(temp->key > key) //temp노드 안에 값이 key보다 클경우
			temp = temp->left; //temp노드를 왼쪽 자식노드로 이동
		else //그렇지 않을 경우
			temp = temp->right; //temp노드를 오른쪽 자식노드로 이동
	}
	return NULL; //NULL을 리턴함으로서 함수 종료
}


int freeBST(Node* head)
{
	Node* temp = head->left; //루트노드를 temp에 불러온다

	freeNode(temp); //temp를 freeNode 함수로 이동시켜 
	free(head);
	return 0;
}

void freeNode(Node* ptr) //후위 순회 방식으로 노드할당 해제
{
	if(ptr != NULL) //ptr이 NULL이 아닐경우
	{
		freeNode(ptr->left); //ptr의 왼쪽 자식으로 이동한 후 freeNode를 재귀함수로 호출
		freeNode(ptr->right); //ptr의 오른쪽 자식으로 이동한 후 freeNode를 재귀함수로 호출
		free(ptr); //ptr을 동적할당 해제를 통해 노드 삭제
	}
}
