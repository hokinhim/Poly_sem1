#define LEN (30 + 1)
#include <stdio.h>
#include <time.h>

int dlina_stroki(char* stroka) {//���������� ����� ������ - ������������ STRLEN()
	int dlina = 0, i = 0;
	while (stroka[i++] != '\0') dlina++;
	return dlina;
}

int matrix_create(int len[LEN][LEN], char* stroka, int left, int right) {
	if (len[left][right] == -1)
		if (stroka[left] == stroka[right]) len[left][right] = (matrix_create(len, stroka, left + 1, right - 1) + 2); //���� �������� �����, �� ������� �������� �� ����, ��� ���� ��������� => ���������� 2
		else if (matrix_create(len, stroka, left + 1, right) > matrix_create(len, stroka, left, right - 1)) len[left][right] = matrix_create(len, stroka, left + 1, right);//���� �������� �� �����, �� ������� ��� �������, ������� ���� ���������� �����
		else len[left][right] = matrix_create(len, stroka, left, right - 1);
	return len[left][right];
}

void palindrome_create(int len[LEN][LEN], char* stroka, char* palindrome, int left, int right, int left_palindrome, int right_palindrome) {
	while (left <= right)//�������� �� ����� �� ������
		if ((left == right) && (len[left][right]) == 1) palindrome[left_palindrome++] = stroka[left++];//���� ����� �� ������� � ��� ���� ��������������� ������� ������� �����������, ���������� ��� � ��������� + �����������
		else {
			if (stroka[left] == stroka[right]) {//���� �������� ������ � ���������� ��������� �����
				palindrome[left_palindrome++] = stroka[left++];//��������� � ��������� ����� + �����������
				palindrome[right_palindrome--] = stroka[right--];//���������� � ��������� ������ + �����������
			}
			else {
				if (len[left + 1][right] > len[left][right - 1]) left++; //���� ������� �������, ������� �� 1 ������� ����, ������ ��� ������� �������, ������� �� ���� ������� �����
				else right--;//����������� ����� �������, ����� ��������� ������ �������
			}
		}
}

int main() {
	char stroka[LEN] = { 0 }, palindrome[LEN] = {0};
	printf("Enter the string:\n");
	gets(stroka);
	int n = dlina_stroki(stroka); int len[LEN][LEN] = { 0 };

	//��������� ������, �������� � ���� ������������ ����� �������������� ��� ������ (���������), �������� ������� ���������� �� i �� j
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
			if (i == j) len[i][j] = 1;//��������� = 1, �.�. ���������, ������������ �� i �� j (i = j), �.� ����� ����� 1, ��� ���� � ���� ���������
			else if (i > j) len[i][j] = 0;//������ ����� ������������ ��������� = 0
			else len[i][j] = -1;//�������� ����� ������������ ��������� = -1 (������������ ������� �������)
		}
	//���������� ����� ���������� ����� �������� � ������ ������� ���� �������

	clock_t start = clock();
	matrix_create(len, stroka, 0, n-1);//���������� ������� ����
	palindrome_create(len, stroka, palindrome, 0, n-1, 0, len[0][n-1] - 1);//���������� �������� ����������
	clock_t end = clock();
	double time = (double)(end - start) / ((double)CLOCKS_PER_SEC);
	printf("%s\n", palindrome);

	int k = 0, m = 0, flag = 0;
	for (k; k < dlina_stroki(stroka); k++) {
		if (palindrome[m] != stroka[k]) {
			printf("%d - %c\n", k + 1, stroka[k]);//����� ���������� ��������
			flag = 1;
		}
		else flag = 0;
		if (flag == 0) m++;
	}
	printf("The program took %f seconds to execute\n", time);
	return 0;
}