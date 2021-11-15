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

PERSON people_array[30] = {0}; // PERSON 구조체 배열.
PERSON * people_linked_list = NULL; // PERSON 구조체 linked list. 
FILE * file; // 파일 디스크립터.
void q1(), q2(), q3(), q4(), q5(), q6(); // 1법부터 6번까지의 문제를 해결할 코드를 다음과 같은 함수의 형태로 적으면 됩니다.

////////////////////////////
////////////////////////////
////////////////////////////

int main(void)
{
    q1();
    /*q2();
    q3();
    q4();
    q5();
    q6();*/
}

// 링크드 리스트 관련 함수들
//
//////// ll_create_node() : 동적 메모리 할당으로 구조체 변수 하나를 메모리에 생성 후, 구조체 변수 주소 포인터를 반환.
//
//////// ll_add_node_at(구조체, 인덱스) : people_linked_list의 인덱스 번째에 있는 값을 뒤로 밀어내고 인수로 받은 구조체를 삽입.
// ll_add_node_at(구조체, POSITION_LAST) 를 사용하여 구조체를 리스트의 마지막에 추가 가능. 리스트에 값을 추가할때 루프에서 사용하기 좋음.
// 0을 반환할때: 인덱스에 값이 정상적으로 추가됨.
// 1을 반환할때: 인덱스보다 링크드 리스트의 사이즈가 작아서 마지막 위치에 추가함. 
//
//////// ll_remove_node_at(인덱스) : people_linked_list의 인덱스 번째에 있는 값을 제거하고 빈 자리를 뒤에 있던 값으로 채움.
// ll_remove_node_at(POSITION_FIRST) 를 사용하여 리스트의 첫번째 구조체 제거 가능. 리스트를 초기화할때 루프에서 사용하기 좋음.
// -1을 반환할때: 리스트가 비어 있어서 제거할 구조체가 없음.
// 0을 반환할때: 인덱스 번째의 구조체를 정상적으로 제거함.
// 1을 반환할때: 인덱스보다 리스트의 크기가 작아서 마지막 번째의 구조체를 제거함.
//
#define POSITION_LAST 99999 
#define POSITION_FIRST 0

PERSON * ll_create_node()
{
    return (PERSON *) malloc(sizeof(PERSON));
}

int ll_add_node_at(PERSON p, int position)
{
    PERSON * ptr = people_linked_list;
    int index_count = 0;

    if (ptr == NULL)
    {
        people_linked_list = ll_create_node();
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

            PERSON * prev_next = ptr->next;
            ptr->next = ll_create_node(); 
            *(ptr->next) = p;
            ptr->next->next = prev_next;
        }
        else
        {
            PERSON * prev = ptr;
            people_linked_list = ll_create_node();
            *people_linked_list = p;
            people_linked_list->next = prev; 
        }
    }

    return position != index_count;

}

int ll_remove_node_at(int position)
{
    PERSON * ptr = people_linked_list;
    int index_count = 0;

    if (ptr == NULL) return -1;
    else
    {
        if (position != 0)
        {
            while (ptr->next != NULL && index_count != position-1)
            {
                ptr = ptr->next;
                index_count++;
            }

            PERSON * next = ptr->next->next;
            free(ptr->next); 
            ptr->next = next; 
        }
        else
        {
            PERSON * next = ptr->next;
            free(ptr);
            ptr = next;
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

    PERSON aaa = {"1", "3", "5", "7", 9,11,13};
    ll_add_node_at(aaa, 0);
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
