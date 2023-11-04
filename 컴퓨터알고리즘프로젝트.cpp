#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//2019112174 ��â�� �� 21�й� ����� ��

// 1~20 ���,1~20 ���������� �� �迭�� ũ�� ����(���� ���� �ݺ������� 1�� �����Ͽ� 20���� ǥ���ϱ� ���Ͽ� 21�� ���� �Ͽ���.)
#define member_Length 21
#define item_Length 21

//�� �迭��Ҵ� ó���� {0}���� ����
int member_it_satisfied_score[member_Length][item_Length] = { 0 };    //�迭1:member, �迭2: item , score[1][2]: ������ ����(satisfaction_score)
int mark_item[item_Length] = { 0 }; // �ʱ⿣ �������� �迭��Ҹ� 0���� ����. ���� �� �迭�� ������ ���� ���� ��������
int mark_member[member_Length] = { 0 }; // �ʱ⿣ ����� �迭��Ҹ� 0���� ����. ���� �� �迭�� ������ ���� ���� ��������
int result_table[member_Length][item_Length] = { 0 };
int final_table[member_Length][item_Length] = { 0 };

void print_table(int arr[member_Length][item_Length]); // ���ϴ� �迭 ����Լ�(finaltavble)
int Max_item_num(int arr[member_Length][item_Length], int);// ����������� ���·�(��� �Է�) �������� ���� ���� ������ ��ȣ�� �����ϴ� �Լ�
int check_marking(int[]); // ��ŷ�� �ߵƴ��� �ȵƴ��� ���� ����� �Լ�
void duplicating(int[member_Length][item_Length], int[member_Length][item_Length]); //result ���̺��� final ���̺�� �ű�� �Լ�

int Random_Algorithm(int arr[member_Length][item_Length]);// �ش� �Լ��� ���� �Լ���� �����Ͽ���, �������� �����ֽ� �ڷḦ ���� �����߽��ϴ�. 

void print_table(int arr[member_Length][item_Length]); // ���ϴ� �迭 ����Լ�(finaltavble)

int main(void)
{
    int i = 0;
    int sum_satisfaction_score; // 1~20 ����� ���� ������(���� ��Ī��)�� �� ������ ������ ��
    //���� �ҷ����� �ڵ��
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
    //���� �ҷ����� ��

    sum_satisfaction_score = Random_Algorithm(member_it_satisfied_score);

    print_table(final_table);
    printf("\n\tFinally, Total sum of satisfaction scores is ");
    printf("%d\n", sum_satisfaction_score);
    printf("\n\t��ǻ�� �˰��� ���Ĺ� 12��  ��â��,����� ��\n");
    return 0;
}

//���̺� ���� ����Ʈ��(���� ���� �Լ����� final_table ��¿�)
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

int Max_item_num(int arr[member_Length][item_Length], int mem) // ����� �����Ѵٰ� ������ ��, �ش� ������� ���� �������� ���� ������ ����
{
    int max = 0;
    int item_num = 0;
    // ����� ���� �����Ѵٰ� ������ �Լ����� �����ϰ�~
    for (int i = 1; i < 21; i++)  //1~20�������� ������ ������ �ƽø��� ����
    {
        if (max < arr[mem][i] && !mark_item[i]) //��ŷ�� �������� �ƴ� ���¿����� �ƽø�(i�� �������� ��ȣ�� ����)
        {
            max = arr[mem][i]; //�ƽ��� ���ϰ�
            item_num = i;//������ ����
        }
    }
    mark_item[item_num] = 1; //�ƽø� ���� �����ۿ� ���ؼ��� 1�� ��ŷ
    return item_num; //�ش� �����۹�ȣ�� ��ȯ
}
//arr[] �迭 ������ �������� Ȯ�ο� ���� ���� �˰��� �Լ����� ����. ��ŷ�� �� 20�� �ٵƴ���
int check_marking(int arr[])
{
    int cnt = 0;

    for (int i = 1; i < 21; i++)
    {
        if (!arr[i]) //���� �迭�� ���� true(1)�� �ƴϸ� 0�� ��ȯ-> cnt���� 1��������Ŵ
        {
            cnt++;
            return 0;
        }
        else if (cnt == 20) //�迭��Ұ�(1~20)�� �� Ȯ�� �� cnt�� 20�� �Ǹ� (true)1�� ��ȯ
        {
            return 1;
        }
    }
    return 1;
}

//result table�� final table�� �������ִ� �Լ�.(���� ���� �˰��� �Լ��������)
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

//���� �߿�!
//�ִ� ������ ��ȯ�ϴ� �Լ���� ����˴ϴ�.
int Random_Algorithm(int arr[member_Length][item_Length])
{
    srand((unsigned)time(NULL));
    int member, item;
    int temp_score = 0; // �ִ������� �߰� �Ű����� ����
    int socre_of_max = 0;
    int epoch = 0;
    int n = 1000, s = 2000; 
    //n�� �����õ� Ƚ�� epoch+1�ϸ鼭 ->n���� ���� ���� ����(while)������
    //s�� �ִ� ������ �������� ���� (s�� ������ �������� ������ �ִ밪�� �۾���, ������ ������ 1722�� �ִ�� �����ϹǷ� �� �̻󰪸� �����ϸ�ȴ�.)
    //n�� ũ�� Ŭ���� ������ ���� �հ�� 1722�� ���ŵ�(n��100�̸� ���� �޶�����, �� ����� �������� ������ ������ �޶�����.)
    while (epoch < n && socre_of_max < s)
    {
        for (int i = 0; i < 21; i++) //��� ���̺� 0���� �ʱ�ȭ
        {
            for (int j = 0; j < 21; j++)
            {
                result_table[i][j] = 0;
            }
        }
        temp_score = 0;
        epoch += 1;//while���ȿ���epoch�� ������Ű��
        while (!check_marking(mark_item) && !check_marking(mark_member)) //��ŷ�� �� �����۰� ����鿡 ���ؼ��� ���� �˰����� �����Ѵٴ� �ǹ�.
        {
            while (1)
            {
                member = rand() % 20 + 1; // 1~20 ����� �����ϰ� ���� ->random selection of members
                if (!mark_member[member]) break; //���� ��ŷ�� �ȵ� (���� 0��)����� ������ ����x->���� Ȯ�ο�
            }
            mark_member[member] = 1; // ��������� ��ũ
            item = Max_item_num(member_it_satisfied_score, member); //����� ������ ������ ���� �ش� ������ ��ȣ�� ��� ����
            temp_score += member_it_satisfied_score[member][item]; //���� ���� ������ ��ȣ�� ���� ����� ������ ��� ����
            result_table[member][item] = member_it_satisfied_score[member][item];// �ش� �����۰� ������ ��� �迭 ���̺�(result_table)
        }
        if (temp_score > socre_of_max) //temp_score�� �߰� �Ű�����
        {
            for (int i = 0; i < 21; i++) //���� ��� ���̺� 0���� �ʱ�ȭ ��
            {
                for (int j = 0; j < 21; j++)
                {
                    final_table[i][j] = 0;
                }
            }
            duplicating(final_table, result_table); //��� ���̺��� ���� ���̺� ����
            socre_of_max = temp_score;
        }

        for (int m = 1; m < member_Length; m++) // ���̺� ��ȯ�� ���� ���� �� ��� �ʱ�ȭ
        {
            mark_member[m] = 0;
        }
        for (int it = 1; it < item_Length; it++) // ���̺�  ��ȯ�� ���� ���� �� ������ �ʱ�ȭ
        {
            mark_item[it] = 0;
        }
    }
    return socre_of_max;
}
