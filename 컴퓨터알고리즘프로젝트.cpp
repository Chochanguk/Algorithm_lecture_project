#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//2019112174 조창욱 및 21학번 백승익 팀

// 1~20 멤버,1~20 아이템으로 각 배열의 크기 정의(추후 각종 반복문에서 1로 시작하여 20까지 표향하기 위하여 21로 지정 하였음.)
#define member_Length 21
#define item_Length 21

//각 배열요소는 처음엔 {0}으로 정의
int member_it_satisfied_score[member_Length][item_Length] = { 0 };    //배열1:member, 배열2: item , score[1][2]: 만족도 점수(satisfaction_score)
int mark_item[item_Length] = { 0 }; // 초기엔 아이템의 배열요소를 0으로 설정. 추후 이 배열에 구해진 값을 집어 넣을예정
int mark_member[member_Length] = { 0 }; // 초기엔 멤버의 배열요소를 0으로 설정. 추후 이 배열에 구해진 값을 집어 넣을예정
int result_table[member_Length][item_Length] = { 0 };
int final_table[member_Length][item_Length] = { 0 };

void print_table(int arr[member_Length][item_Length]); // 원하는 배열 출력함수(finaltavble)
int Max_item_num(int arr[member_Length][item_Length], int);// 멤버가고정된 상태로(멤버 입력) 만족도가 가장 높은 아이템 번호를 지정하는 함수
int check_marking(int[]); // 마킹이 잘됐는지 안됐는지 오류 검출용 함수
void duplicating(int[member_Length][item_Length], int[member_Length][item_Length]); //result 테이블을 final 테이블로 옮기는 함수

int Random_Algorithm(int arr[member_Length][item_Length]);// 해당 함수는 위의 함수들과 연계하였고, 교수님이 나눠주신 자료를 토대로 구현했습니다. 

void print_table(int arr[member_Length][item_Length]); // 원하는 배열 출력함수(finaltavble)

int main(void)
{
    int i = 0;
    int sum_satisfaction_score; // 1~20 멤버가 가진 아이템(최종 매칭된)의 총 만족도 점수의 합
    //파일 불러오는 코드들
    FILE* fp = fopen("satisfaction.txt", "r");
    
    char buffer[256], * token;

    while (!feof(fp)) {
        int a = 0, b = 0;
        i = 0;
        fgets(buffer, 256, fp);
        token = strtok(buffer, " ");
        while (token != NULL) {
            if (i == 0) {
                a = atoi(token);
            }
            else if (i == 1) {
                b = atoi(token);
            }
            else if (i == 2) {
                member_it_satisfied_score[a][b] = atoi(token);
            }
            i++;
            token = strtok(NULL, " ");
        }
    }

    fclose(fp);
    //파일 불러오기 끝

    sum_satisfaction_score = Random_Algorithm(member_it_satisfied_score);

    print_table(final_table);
    printf("\n\tFinally, Total sum of satisfaction scores is ");
    printf("%d\n", sum_satisfaction_score);
    printf("\n\t컴퓨터 알고리즘 오후반 12조  조창욱,백승익 팀\n");
    return 0;
}

//테이블 값들 프린트용(추후 메인 함수에서 final_table 출력용)
void print_table(int arr[member_Length][item_Length])
{
    for (int i = 1; i < 21; i++)
    {
        for (int j = 1; j < 21; j++)
        {
            if (arr[i][j] != 0)
                printf("\tMember%d is satisfied for item %d with satisfaction score %d \n", i, j, arr[i][j]);
        }
    }
}

int Max_item_num(int arr[member_Length][item_Length], int mem) // 멤버를 고정한다고 가정할 때, 해당 멤버에게 가장 만족도가 높은 아이템 지정
{
    int max = 0;
    int item_num = 0;
    // 멤버의 값을 고정한다고 가정한 함수임을 인지하고~
    for (int i = 1; i < 21; i++)  //1~20번까지의 아이템 각각의 맥시멈을 구함
    {
        if (max < arr[mem][i] && !mark_item[i]) //마킹된 아이템이 아닌 상태에서의 맥시멈(i는 아이템의 번호를 뜻함)
        {
            max = arr[mem][i]; //맥스를 구하고
            item_num = i;//아이템 지정
        }
    }
    mark_item[item_num] = 1; //맥시멈 값인 아이템에 대해서는 1로 마킹
    return item_num; //해당 아이템번호를 반환
}
//arr[] 배열 값들이 가능한지 확인용 추후 랜덤 알고리즘 함수에서 사용됨. 마킹이 총 20개 다됐는지
int check_marking(int arr[])
{
    int cnt = 0;

    for (int i = 1; i < 21; i++)
    {
        if (!arr[i]) //만약 배열의 값이 true(1)이 아니면 0을 반환-> cnt값을 1씩증가시킴
        {
            cnt++;
            return 0;
        }
        else if (cnt == 20) //배열요소값(1~20)을 다 확인 후 cnt가 20이 되면 (true)1을 반환
        {
            return 1;
        }
    }
    return 1;
}

//result table을 final table에 복제해주는 함수.(추후 랜덤 알고리즘 함수에서사용)
void duplicating(int duplicated[member_Length][item_Length], int original[member_Length][item_Length])
{
    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            duplicated[i][j] = original[i][j];
        }
    }
}

//제일 중요!
//최대 점수를 반환하는 함수라고 보면됩니다.
int Random_Algorithm(int arr[member_Length][item_Length])
{
    srand((unsigned)time(NULL));
    int member, item;
    int temp_score = 0; // 최대점수의 중간 매개변수 역할
    int socre_of_max = 0;
    int epoch = 0;
    int n = 1000, s = 2000; 
    //n은 랜덤시도 횟수 epoch+1하면서 ->n으로 가면 랜덤 종료(while)문에서
    //s는 최대 만족도 점수까지 시행 (s가 작으면 작을수록 총합의 최대값이 작아짐, 하지만 시행결과 1722가 최대로 수렴하므로 그 이상값만 시행하면된다.)
    //n이 크면 클수록 만족도 점수 합계는 1722로 수렴됨(n이100이면 값은 달라지고, 각 멤버별 아이템의 만족도 점수도 달라진다.)
    while (epoch < n && socre_of_max < s)
    {
        for (int i = 0; i < 21; i++) //결과 테이블 0으로 초기화
        {
            for (int j = 0; j < 21; j++)
            {
                result_table[i][j] = 0;
            }
        }
        temp_score = 0;
        epoch += 1;//while문안에서epoch값 증가시키기
        while (!check_marking(mark_item) && !check_marking(mark_member)) //마킹이 된 아이템과 멤버들에 대해서만 랜덤 알고리즘을 시행한다는 의미.
        {
            while (1)
            {
                member = rand() % 20 + 1; // 1~20 멤버를 랜덤하게 지정 ->random selection of members
                if (!mark_member[member]) break; //만약 마킹이 안된 (값이 0인)멤버가 있으면 실행x->오류 확인용
            }
            mark_member[member] = 1; // 멤버에대해 마크
            item = Max_item_num(member_it_satisfied_score, member); //멤버별 만족도 점수에 대해 해당 아이템 번호를 담는 변수
            temp_score += member_it_satisfied_score[member][item]; //위의 변수 아이템 번호에 대해 멤버별 점수를 담는 변수
            result_table[member][item] = member_it_satisfied_score[member][item];// 해당 아이템과 점수를 담는 배열 테이블(result_table)
        }
        if (temp_score > socre_of_max) //temp_score는 중간 매개변수
        {
            for (int i = 0; i < 21; i++) //최종 결과 테이블 0으로 초기화 후
            {
                for (int j = 0; j < 21; j++)
                {
                    final_table[i][j] = 0;
                }
            }
            duplicating(final_table, result_table); //결과 테이블을 최종 테이블에 저장
            socre_of_max = temp_score;
        }

        for (int m = 1; m < member_Length; m++) // 테이블에 반환된 값을 담은 후 멤버 초기화
        {
            mark_member[m] = 0;
        }
        for (int it = 1; it < item_Length; it++) // 테이블에  반환된 값을 담은 후 아이템 초기화
        {
            mark_item[it] = 0;
        }
    }
    return socre_of_max;
}
