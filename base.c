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

PERSON people_array[50] = {0}; // PERSON 구조체 배열. 초기값은 모두 0.
PERSON * people_linked_list = NULL; // PERSON 구조체 linked list. main 함수에서 HEAD 노드 추가 
FILE * file; // 파일 디스크립터.
void q1(), q2(), q3(), q4(), q5(), q6(); // 1법부터 6번까지의 문제를 해결할 코드를 다음과 같은 함수의 형태로 적으면 됩니다.

////////////////////////////
////////////////////////////
////////////////////////////

PERSON * ll_create_node()
{
   PERSON * node = (PERSON *) malloc(sizeof(PERSON));
   node->next = NULL;
   return node;
}

int main(void)
{
    people_linked_list = ll_create_node(); //HEAD 노드 생성.
    strcpy(people_linked_list->name, "HEAD"); //HEAD 노드의 name은 HEAD.

    q1();
    q2();
    q3();
   /* q4();
    q5();
    q6();*/
}

void ll_insert_node(PERSON * head, PERSON p) //번호순에 맞게 추가 
{
    PERSON * prev = head;
    PERSON * ptr = head->next;

    while (ptr)
    {
        prev = ptr;

        if (ptr->index >= p.index) ptr = ptr->next;
        else break;
    }

    PERSON * newnode = ll_create_node();

    prev->next = newnode;
    *newnode = p;
    newnode->next = ptr;

}

void ll_add_node(PERSON * head, PERSON p) //마지막에 추가
{
    PERSON * prev = head;
    PERSON * ptr = head->next;

    while (ptr)
    {
        prev = ptr;
        ptr = ptr->next;
    }

    PERSON * newnode = ll_create_node();

    prev->next = newnode;
    *newnode = p;
    newnode->next = ptr;

}


int ll_remove_node(PERSON * head, int index) // 해당 인덱스의 구조체 제거, -1 반환시 리스트 비어있는 것임.
{
    PERSON * prev = head;
    PERSON * ptr = head->next;

    while (ptr)
    {
        if (ptr->index == index) break;

        prev = ptr;
        ptr = ptr->next;
    }

    if (!ptr) return -1;

    PERSON * nextp = ptr->next;
    prev->next = nextp;
    free(ptr);

    return 0;
}

void ll_print_nodes(PERSON * head, int from, int to) // 링크드 리스트의 모든 노드들의 정보를 출력함.
{
    printf("[리스트에서의 인덱스, 번호, 날짜, 지불여부, 이름, 나이, 출신대학, 직업]\n");

    PERSON * ptr = head->next;

    for (int i=0; i<from && ptr; i++) ptr = ptr->next;

    for (int i=from; i<=to && ptr; i++, ptr = ptr->next)
    {

        printf("#%2d: %3d %11s %3d %30s %2d %30s %20s\n", 
            i, ptr->index, ptr->date, ptr->paid, ptr->name,
            ptr->age, ptr->univ, ptr->job);
    }
    if (!ptr) printf("인덱스의 범위를 벗어났습니다.\n");
}
void ll_sync_with_array(PERSON * head, PERSON array[]) // 링크드 리스트를 초기화하고 배열과 동기화함.
{
    for (int index=1; ll_remove_node(head, index) != -1; index++);
    for (PERSON * p = array; *p->name; p++)
        ll_add_node(head, *p);
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
    for (PERSON * p = people_array; *(p->name); p++) 
        ll_add_node(people_linked_list, *p);

    //TODO: 성이 '최' 이거나 가천대 소속일 경우 터미널에 정보 출력하기.
}

//문제 2번
void q2() 
{
      //Selection sort로 번호순대로 배열 정렬
    for (PERSON* p = people_array; *(p + 1)->name; p++)
    {
        PERSON* min = p;
        
        for (PERSON* j = p + 1; *j->name; j++)
            if (j->index < min->index) {
                min = j;
            }

        
        printf("%d/%s/%d/%s/%d/%s/%s\n", min->index, min->date, min->paid, min->name, min->age, min->univ, min->job);

        PERSON tmp = *min;
        *min = *p;
        *p = tmp;
    }

    //배열에 정렬한 것들을 링크드 리스트에 다시 작성.
    ll_sync_with_array(people_linked_list, people_array);
    int a = 3;
}

//문제 3번
void q3()
{
    int flag20 = 0;
    int flag30 = 0;
    int flag40 = 0;
    int flag50 = 0;
    int flag60 = 0;
    int flag70 = 0;

    file = fopen("P5-1.txt", "w");

    //Selection sort로 번호순대로 배열 정렬
    for (PERSON* p = people_array; *(p + 1)->name; p++)
    {
        PERSON* min = p;

        for (PERSON* j = p + 1; *j->name; j++)
            if (j->age < min->age) {
                min = j;
            }

        if (min->age >= 20 && min->age < 30) {
            if (flag20 == 0)  fprintf(file, "Age : 20 ~ 29\n");
            fprintf(file, "%d/%s/%d/%s/%d/%s/%s\n", min->index, min->date, min->paid, min->name, min->age, min->univ, min->job);
            flag20 = 1;
            
        }
        if (min->age >= 30 && min->age < 40) {
            if (flag30 == 0)  fprintf(file, "\nAge : 30 ~ 39\n");
            fprintf(file, "%d/%s/%d/%s/%d/%s/%s\n", min->index, min->date, min->paid, min->name, min->age, min->univ, min->job);
            flag30 = 1;
        }
        if (min->age >= 40 && min->age < 50) {
            if (flag40 == 0)  fprintf(file, "\nAge : 40 ~ 49\n");
            fprintf(file, "%d/%s/%d/%s/%d/%s/%s\n", min->index, min->date, min->paid, min->name, min->age, min->univ, min->job);
            flag40 = 1;
        }
        if (min->age >= 50 && min->age < 60) {
            if (flag50 == 0)  fprintf(file, "\nAge : 50 ~ 59\n");
            fprintf(file, "%d/%s/%d/%s/%d/%s/%s\n", min->index, min->date, min->paid, min->name, min->age, min->univ, min->job);
            flag50 = 1;
        } 
        if (min->age >= 60 && min->age < 70) {
            if (flag60 == 0)  fprintf(file, "\nAge : 60 ~ 69\n");
            fprintf(file, "%d/%s/%d/%s/%d/%s/%s\n", min->index, min->date, min->paid, min->name, min->age, min->univ, min->job);
            flag60 = 1;
        }
        if (min->age >= 70 && min->age < 80) {
            if (flag70 == 0)  fprintf(file, "\nAge : 70 ~ 79\n");
            fprintf(file, "%d/%s/%d/%s/%d/%s/%s\n", min->index, min->date, min->paid, min->name, min->age, min->univ, min->job);
            flag70 = 1;
        }
        PERSON tmp = *min;
        *min = *p;
        *p = tmp;
    }

    fclose(file);


}

//문제 4번
void q4() {}

//문제 5번
void q5() {}

//문제 6번
void q6() {}
