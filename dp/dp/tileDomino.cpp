#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;
int arr_ori[] = {1,1,1,1,1,1,1,1,1,1,1,2,3,4,2,2,2};
//int arr_ori[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,3,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22};
//int arr[] = {1,2,1};
int *arr;

typedef struct node{
	int data;
	struct node *next;
}node;

vector<node*> list;

void printNode(node* head)
{
    /* go to the last node */
    node *cursor = head;
    while(cursor != NULL){
		printf("%d ->", cursor->data);
        cursor = cursor->next;
	}
    printf("\n");
}

int isExist(vector<node*> list, node* head, int count){
	int size = list.size();	
	
	//printf(">>>>>>>>>>>>>>");
	//printNode(head);
    for(int i = 0; i < size; i++){
		
		int match = 0;
		//printNode(list[i]);
		node* cur2 = list[i];
		node* cur1 = head;
        while((cur1 != NULL) && (cur2 != NULL)){
			if(cur1->data == cur2->data)
				match++;
			cur1 = cur1->next;
			cur2=cur2->next;
		}
		if(match == count){
			//printf(" match\n");
			//printf("============\n");
			return 1;
		}
    }
	//printf("not match\n");
	//printf("============\n");
    return 0;
}

node* create(int data,node* next)
{
    node* new_node = (node*)malloc(sizeof(node));
    if(new_node == NULL)
    {
        printf("Error creating a new node.\n");
        exit(0);
    }
    new_node->data = data;
    new_node->next = next;
 
    return new_node;
}

void insertInOrder(node** head, int data)
{
    /* go to the last node */
    node *cursor = *head;

	/* create a new node */
    node* new_node =  create(data,NULL);
	if((*head == NULL) || (cursor->data > data)){
		new_node->next = *head;
		*head = new_node;
	}else{
		while((cursor->next != NULL) && (cursor->next->data <= data)){
			cursor = cursor->next;
		}
		new_node->next = cursor->next;
		cursor->next = new_node;		 
	}
    
}

int countWays(int n){
	int count = 0;
	printf("1<<n = %d\n", 1<<n);
	// iterate over all the subsets
	for (int i=0; i < (1<<n); i++)
	{
		//printf(">>>>> i = %d\n", i);
		// generate the i-th subset
		//Vector subset=new Vector();
		int sum = 0;
		int pro = 1;
		node *head = NULL;
		int c = 0;
		for (int k=0; k < n; k++)
		{			
			if ((i&(1<<k)) > 0){				
				sum += arr[k];
				pro *= arr[k];
				if(head == NULL){
					head = create(arr[k],NULL);
				}else{
					insertInOrder(&head,arr[k]);
				}
				c++;
			}
		}
		
		{
			if(sum > pro){
				if(isExist(list, head, c) == 0){
					list.push_back(head);
					printNode(head);
                    count++;
					printf(" --> OK");
                }else{
					printf(" --> Duplicated");
				}		
				
			}else{
				printf(" --> NG");
			}
		}
		printf("\n");
		
	}
	return count;
}

int countOne(int n){
	int count = 0;
	for(int i = 0; i < n; i++){
		if(arr_ori[i] == 1)
			count++;
	}
	int size_arr = n - count +1;
	arr = (int*) malloc(sizeof(int)*(size_arr));
	int flag = 0;
	int j = 0;
	for(int i = 0; i< n; i++){
		if(arr_ori[i] == 1){
			if (flag==0){
				arr[j++] = arr_ori[i];
				flag = 1;
			}
		}else{
			arr[j++] = arr_ori[i];
		}
	}
	for(int i = 0; i < size_arr; i++){
		printf("%d,", arr[i]);
	}

	int total = countWays(size_arr);
	printf("total = %d, count = %d \n", total, count);
	total *= (count-1);
	
	return total;
}



int main(){
	
	int n = sizeof(arr_ori)/sizeof(int);
	printf("%d \n", countOne(n));
	getchar();
	return 0;
}