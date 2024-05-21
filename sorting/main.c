/*���������� ��� ������� ���������� �� ��������� ������, ������ ��� ������ ��������� ������� ������ :
1, 2, 3, 4, 5, 6 ���������� ������������ = 3?
�����: �� ������ �������� ���������, �� ������� �� 2 �����: 
�� ��������������� �������� ����� �� ���������� ����� � �� ��������������� ������.
�����, ����� ������������� ���� ������, �������� ���������� ���������� � ��������������� ��� 2 ������� ����������
� ���� ����� ��������� ��� ��� ����� ���������� ��������� SWAP (���� i <= j), 
������� ������������ ��������, �� �� ����� ������ �� ��������� (��� ��� ������� ������ ��� ��������������)
������ ������� ������� ���������� ���������� �������� ���������� �� ������� ����������������� �������� ������, 
������ ��� ���� ������ ��������������, ������� ���������� ��� ����� ����� ������������ ������������, 
����� ��� ������ ������������� ���������� � ������ ���������,�� ����� ���� ����������, 
��� ��� ������� SWAP � ���� ����������� ������� � ��������� ������� �� ���������� ������� ����������������� ��������� ���� ���������.

��� ����� 2.txt ��� ����� ������� ������: ���� ����� ��������� = 1 
(�� ������ �� ��, ��� ������� ������ � ���� �����: 1O, ��� O - �����, � �� ����, � ������ ����������� �������), 
�� ������� ���������� �� ��������������, ��� ��� ����������� ������.
*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <limits.h>

void null_mas(int* mas1, int* mas2, int* mas3, int N) {//��������� ��������
    for (int i = 0; i < N; i++) {
        *(mas1 + i) = 0;
        *(mas2 + i) = 0;
        *(mas3 + i) = 0;
    }
}

void null_per(unsigned long long* num1, unsigned long long* num2) {//��������� ���������
    *(num1) = 0;
    *(num2) = 0;
}

void output_console(char type_sort[], double time, unsigned long long count_sravn, unsigned long long count_swap) {//����� � �������
    if (type_sort == "Quick sort") printf("\n-----------------%s------------------\n", type_sort);
    else printf("\n-----------------%s-----------------\n", type_sort);
    printf("The program took %f seconds to execute\n", time);
    printf("Number of elements comparisons = %llu\n", count_sravn);
    printf("Number of elements permutations = %llu\n", count_swap);
    printf("---------------------------------------------\n");
}

void output_file(char type_sort[], double time, unsigned long long count_sravn, unsigned long long count_swap) { //�������������� � ����
    FILE* output = fopen("output.txt", "a");
    if (output == NULL) perror("OPEN ERROR");
    else fprintf(output, "%s:\nThe program took %f seconds to execute\nNumber of elements comparisons = %llu\nNumber of elements permutations = %llu\n\n", type_sort, time, count_sravn, count_swap);
}

void check_read_error(char name_per[], int *element) { //���������� �������� � ���������
    if (name_per == "choose") {
        if ((scanf("%d", element)) != 1) {
            printf("\nPlease, enter a number\nRestart the program\n");
            return;
        }
        if ((*element != 1) && (*element != 2)) {
            printf("\nPlease, enter 1 or 2\nRestart the program\n");
            return;
        }
    }
    else if (name_per == "count_of_elements") {
        if (scanf("%d", element) != 1) {
            printf("\nPlease, enter a number\nRestart the program\n");
            return;
        }
        if ((*element > INT_MAX) || (*element < 2)) {
            printf("\nPlease, enter a number in the range from 2 to %d\nRestart the program\n", INT_MAX);
            *element = 0;
            return;
        }
    }
}

void generator(int* mas, int N) { //��������� ��������� �����
    srand((unsigned int)time(NULL));
    for (int i = 0; i < N; i++) *(mas + i) = -(15000*15000) + rand() * rand();
}

void swap(int *a, int *b, unsigned long long* count_swap) { //����� ���������� ���� ���������� ����� ��������������
    int tmp = *a;
    *a = *b;
    *b = tmp;
    *(count_swap) = *(count_swap) + 1;
}

void bubble_sort(int* mas, int N, unsigned long long* count_swap, unsigned long long* count_sravn) { //������� ���������� ���������
    int no_swap;

    for (int i = N - 1; i >= 0; i--) {
        no_swap = 1; //����������, ���������� �� ������ ������ ����������������� �������
        for (int j = 0; j < i; j++) {
            if (*(mas + j) > *(mas + j + 1)) { //���� ������� ����� ������ �������� ������, ������ �� �������
                swap(&*(mas + j), &*(mas + j + 1), count_swap);
                no_swap = 0;
            }
            *(count_sravn) = *(count_sravn) + 1;
        }
        if (no_swap) break;
    }
}

void shells_sort(int* mas, int N, unsigned long long* count_swap, unsigned long long* count_sravn) { //������������������� ���������� �����
    int gap = N / 2;//����������� ���������� = �������� �� ���������� ���� �����
    while (gap > 0) {
        for (int i = 0; i < N - gap; i++) {
            int j = i;
            while ((j >= 0) && (mas[j] > mas[j + gap])) {//���� �������, ����������� �� ��������� ���������� ����� �� �������������
                *(count_sravn) = *(count_sravn) + 1;
                swap(&*(mas+j), &*(mas + j + gap), count_swap);//������ �� �������
                j--;
            }
            *(count_sravn) = *(count_sravn)+1;
        }
        gap /= 2;//������ ��� ��������� ���������� � 2 ����
    }
}

void quick_sort(int* mas, int N, unsigned long long* count_swap, unsigned long long* count_sravn) {//������������������� ������� ����������
    if (N == 1) return;

    int i = 0;
    int j = N - 1;
    int mid = *(mas + (N / 2));//������������� �������� �� ����� �����

    while (i <= j) {//���� �������, ���������� �� �������� �����, ������ ��� ����� ��������, ����������� �� �������� ������
        while (*(mas + i) < mid) {//���� ������� ����� �� �������� ������ ���
            i++;//����������� �������
            *(count_sravn) = *(count_sravn) + 1;
        }
        while (*(mas + j) > mid) {//���� ������� ������ �� �������� ������ ���
            j--;//��������� �������
            *(count_sravn) = *(count_sravn) + 1;
        }
        if (i <= j) {//���� ������� �����������
            swap(&*(mas + i), &*(mas + j), count_swap);//������ ������� ������� ����� � ������� ������
            i++;
            j--;
        }
    }

    if (j > 0) quick_sort(mas, j + 1, count_swap, count_sravn);
    if (i < N) quick_sort(&*(mas + i), N - i, count_swap, count_sravn);
}

int main() {
    int* mas_bubble;
    int* mas_shells;
    int* mas_quick;
    int choose = 0;
    unsigned long long count_sravn = 0, count_swap = 0;
    clock_t start, end;
    double time;

    printf("Please choose the input data format:\n1)use a random number generator;\n2)upload your own file\n");
    check_read_error("choose", &choose);

    if (choose == 1) {
        int N = 0;
        printf("\nPlease enter the number of elements:\n");
        check_read_error("count_of_elements", &N);

        if (N != 0) {
            mas_bubble = (int*)malloc(N * sizeof(int));
            mas_shells = (int*)malloc(N * sizeof(int));
            mas_quick = (int*)malloc(N * sizeof(int));
            null_mas(mas_bubble, mas_shells, mas_quick, N);

            generator(mas_bubble, N);
            for (int i = 0; i < N; i++)
                if ((mas_shells != NULL) && (mas_quick != NULL) && (mas_bubble != NULL)) {
                    *(mas_shells + i) = *(mas_bubble + i);
                    *(mas_quick + i) = *(mas_bubble + i);
                }

            start = clock();
            bubble_sort(mas_bubble, N, &count_swap, &count_sravn);
            end = clock();
            time = (double)(end - start) / ((double)CLOCKS_PER_SEC);
            output_console("Bubble sort", time, count_sravn, count_swap);
            output_file("Bubble sort", time, count_sravn, count_swap);
            null_per(&count_sravn, &count_swap);

            start = clock();
            shells_sort(mas_shells, N, &count_swap, &count_sravn);
            end = clock();
            time = (double)(end - start) / ((double)CLOCKS_PER_SEC);
            output_console("Shells sort", time, count_sravn, count_swap);
            output_file("Shells sort", time, count_sravn, count_swap);
            null_per(&count_sravn, &count_swap);

            start = clock();
            quick_sort(mas_quick, N, &count_swap, &count_sravn);
            end = clock();
            time = (double)(end - start) / ((double)CLOCKS_PER_SEC);
            output_console("Quick sort", time, count_sravn, count_swap);
            output_file("Quick sort", time, count_sravn, count_swap);
            null_per(&count_sravn, &count_swap);
        }
    }

    else if (choose == 2) {
        char name_of_file[128];
        printf("\nEnter the name of file with extension\n");
        if (scanf("%s", name_of_file) != 1)
            printf("\nError of reading name of file\n");
        else {
            name_of_file[strlen(name_of_file) + 1] = '\0';
            int N = 1;
            char s;
            FILE* input = fopen(name_of_file, "r");
            if (input == NULL)
                perror("OPEN ERROR");
            else {
                while ((s = fgetc(input)) != EOF) //���� �� �������� ����� �����
                    if (s == ',') //������������ ���������� ���������, ������ �������
                        N++;

                mas_bubble = (int*)malloc(N * sizeof(int));
                mas_shells = (int*)malloc(N * sizeof(int));
                mas_quick = (int*)malloc(N * sizeof(int));
                null_mas(mas_bubble, mas_shells, mas_quick, N);

                fseek(input, 0, SEEK_SET);

                int chislo = 0;
                for (int i = 0; i < N; i++) {
                    if (fscanf(input, "%d %*c", &chislo) != 1)//����������� ����
                        printf("Error of reading element #%d", i + 1);
                    else if ((mas_bubble != NULL) && (mas_shells != NULL) && (mas_quick != NULL)) {
                        *(mas_bubble + i) = chislo;
                        *(mas_shells + i) = chislo;
                        *(mas_quick + i) = chislo;
                    }
                }

                start = clock();
                bubble_sort(mas_bubble, N, &count_swap, &count_sravn);
                end = clock();
                time = (double)(end - start) / ((double)CLOCKS_PER_SEC);
                output_console("Bubble sort", time, count_sravn, count_swap);
                output_file("Bubble sort", time, count_sravn, count_swap);
                null_per(&count_sravn, &count_swap);

                start = clock();
                shells_sort(mas_shells, N, &count_swap, &count_sravn);
                end = clock();
                time = (double)(end - start) / ((double)CLOCKS_PER_SEC);
                output_console("Shells sort", time, count_sravn, count_swap);
                output_file("Shells sort", time, count_sravn, count_swap);
                null_per(&count_sravn, &count_swap);

                start = clock();
                quick_sort(mas_quick, N, &count_swap, &count_sravn);
                end = clock();
                time = (double)(end - start) / ((double)CLOCKS_PER_SEC);
                output_console("Quick sort", time, count_sravn, count_swap);
                output_file("Quick sort", time, count_sravn, count_swap);
                null_per(&count_sravn, &count_swap);
            }
        }
    }

    return 0;
}