#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STR_LEN 100 // char 배열로 문자열 변수를 만들때, 배열의 크기를 지정

typedef struct PERSON PERSON; // struct PERSON 을 PERSON으로 단축해서 쓸 수 있도록 함.
struct PERSON // PERSON 구조체. 4개의 문자열, 3개의 정수.
{
    char name[MAX_STR_LEN], date[MAX_STR_LEN];
    char univ[MAX_STR_LEN], job[MAX_STR_LEN];
    int paid, age, index;
    PERSON * next;
};

PERSON people_array[50] = {0}; // PERSON 구조체 배열.
PERSON * people_linked_list = NULL; // PERSON 구조체 linked list. 
FILE * file; // 파일 디스크립터.
void q1(), q2(), q3(), q4(), q5(), q6(); // 1법부터 6번까지의 문제를 해결할 코드를 다음과 같은 함수의 형태로 적으면 됩니다.

////////////////////////////
////////////////////////////
////////////////////////////

int main(void)
{
    people_linked_list = ll_create_node(); //HEAD 노드 생성.

    q1();
    /*q2();
    q3();
    q4();
    q5();
    q6();*/
}

#define POSITION_LAST 99999 
#define POSITION_FIRST 0

PERSON * ll_create_node()
{
   PERSON * node = (PERSON *) malloc(sizeof(PERSON));
   node->next = NULL;
   return node;
}

PERSON * ll_get_node_at(int position)
{
    int out_of_range = 0;
    PERSON * ptr = people_linked_list;

    for (int i=0; i<position && !out_of_range; i++)
    {
        if (ptr != NULL) ptr = ptr->next;
        else out_of_range = 1;
    }

    return out_of_range ? NULL : ptr;
}

void ll_print_nodes(int from, int to)
{
    printf("[리스트에서의 인덱스, 번호, 날짜, 지불여부, 이름, 나이, 출신대학, 직업]\n");
    for (int i=from; i<=to; i++)
    {
        PERSON * p = ll_get_node_at(i);
        if (p == NULL) return;

        printf("#%2d: %3d %11s %3d %30s %2d %30s %20s\n", 
            i, p->index, p->date, p->paid, p->name,
            p->age, p->univ, p->job);
    }
}

int ll_add_node_at(PERSON p, int position)
{
    PERSON * ptr = people_linked_list;
    PERSON * newnode = ll_create_node();
    int index_count = 0;
    *newnode = p;

    if (ptr == NULL)
    {
        people_linked_list = newnode;
        *people_linked_list = p;
    }
    else
    {
        if (position != 0)
        {
            while (ptr->next != NULL && index_count != position-1)
            {
                ptr = ptr->next;
                index_count++;
            }

            newnode->next = ptr->next;
            ptr->next = newnode;
        }
        else
        {
            newnode->next = people_linked_list;
            people_linked_list = newnode;
        }
    }

    return position != index_count;

}

int ll_remove_node_at(int position)
{
    PERSON * ptr = people_linked_list;
    int index_count = 0;

    if (ptr == NULL) return -1;
    else if (ptr->next == NULL) people_linked_list = NULL;
    else
    {
        if (position != 0)
        {
            while (ptr->next->next != NULL && index_count != position-1)
            {
                ptr = ptr->next;
                index_count++;
            }

            PERSON * next = ptr->next;
            ptr->next = ptr->next->next;
            free(next); 

        }
        else
        {
            PERSON * next = ptr->next;
            free(ptr);
            people_linked_list = next;
        }
    }

    return position != index_count;
}


/////////////////////
/////////////////////
/////////////////////

//문제 1번
void q1()
{
    file = fopen("registraion_data.txt", "r");

    int people_count = 0;
    while (1)
    {
        char thisline[MAX_STR_LEN];
        char tmp_str[7][MAX_STR_LEN] = {0}; 
        char * thisline_cur = thisline;
        char * tmpstr_cur = tmp_str[0];

        if (fgets(thisline, MAX_STR_LEN, file) == NULL) break;

        for (int slash_count = 0; slash_count < 7; slash_count++)
        {
            while (*thisline_cur != '/')
            {
                if (*thisline_cur == '\0' || *thisline_cur == '\r' || *thisline_cur == '\n')
                {
                    slash_count = 7;
                    break;
                }

                *(tmpstr_cur++) = *(thisline_cur++);
            }
            
            thisline_cur++;
            tmpstr_cur = tmp_str[slash_count+1]; 
        }

        people_array[people_count].index = atoi(tmp_str[0]);
        people_array[people_count].age = atoi(tmp_str[4]);
        
        people_array[people_count].paid = strcmp(tmp_str[2], "yes") ? 0 : 1;

        strcpy(people_array[people_count].date, tmp_str[1]);
        strcpy(people_array[people_count].name, tmp_str[3]);
        strcpy(people_array[people_count].univ, tmp_str[5]);
        strcpy(people_array[people_count].job, tmp_str[6]);

        people_count++;
    }
    fclose(file);

    ////

    //링크드 리스트에 배열의 구조체들을 추가함.
    for (int i=0; *people_array[i].name; i++) 
        ll_add_node_at(people_array[i], POSITION_LAST);

    ll_print_nodes(0,999);
    ll_remove_node_at(999);
    ll_print_nodes(0,999);
    //TODO: 성이 '최' 이거나 가천대 소속일 경우 터미널에 정보 출력하기.
}

//문제 2번
void q2() {}

//문제 3번
void q3() {}

//문제 4번
void q4() {}

//문제 5번
void q5() {}

//문제 6번
void q6() {}
