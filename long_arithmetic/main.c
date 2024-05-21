#define _CRT_SECURE_NO_WARNINGS
#define SIZE 2500
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int overflow = 0;

void input(int number[]) { //��������� ����� �����
	//��������� ����� � ������ ������
	char number_str[SIZE] = { '\0' };
	printf("Enter the nubmer:\n");
	if (scanf("%s", &number_str) == NULL) {
		printf("Error of entering number");
		return -1;
	}
	//
	
	//�������� �� ������������ ���������� ����� (���������� ����)
	int flag = 0;
	if ((number_str[0] < '0' && number_str[0] != '-') || number_str[0] >'9') //�������������� �������� �� ������ ������� '-'
		flag = 1;
	for (int i = 1; i < strlen(number_str); i++)
		if (number_str[i] < '0' || number_str[i] > '9')
			flag = 1;
	if (flag == 1) {
		printf("Please, enter the number, but not any others symbols!");
		input(number); //������� �������� ��������� ��������
		return; //����� ������� �� ���������
	}

	//�������� �� ������������� �����
	if (number_str[0] != '-') {
		for (int i = strlen(number_str); i >= 0; i--) //�������� �� ���� ������ ������
			number_str[i + 1] = number_str[i];
		number_str[0] = '0'; //������ ������� = 0 (��������� �� ������������� �����)
	}
	else {
		number_str[0] = '1'; //������ ������� = 1 (��������� �� ������������� �����)
		number[0] = 1;
	}
	for (int i = 0; i < strlen(number_str) - 1; i++) //��������� ����� �� ���������� ���� � int
		number[SIZE - i] = number_str[strlen(number_str) - 1 - i] - '0';
	//
}

void output(int result[]) { //��������� ������ �����
	int i = 1;
	for (i; result[i] == 0; i++); //���� �� ������ i, ����� ��������� ���������� ����
	printf("Result = ");
	if (i == 2501) //���� ������ i �� ������� (�.�. i = 2501), �� �������� 0
		printf("0");
	if (result[0] == 1) //�������� �� ������������� �����
		printf("-");
	for (i; i <= SIZE; i++)
		printf("%d", result[i]);
	printf("\n");
}

void check_overflow(int overflow, int result[]) { //���������, ���������� ������������
	if (overflow == 1)
		printf("WARNING! Not enough memory\nRestart the program");
	else if (overflow == 2)
		return;
	else
		output(result);
}

void null(int number[]) { //��������� ��������� �������
	for (int i = 0; i < SIZE + 1; i++)
		number[i] = 0;
}

void summator(int znak, int num1[], int num2[], int result[]) { //��������� ������������ ���� �����
	int sum[SIZE + 1] = { 0 };

	if ((znak == 1) && (num2[0] == 0)) // �������� �������� ��� ��������� + ����� �����
		num2[0] = 1;
	else if ((znak == 1) && (num2[0] == 1)) 
		num2[0] = 0;

	int sign; //����������, ���������� �� ����

	if (num1[0] == num2[0]) { //���� ����� ����� �� �����, �� ���������� �� ����������
		int old_digit = 0; //����������, ���������� �� ���������� �������� ������� � ������, ���� ����� > 9
		sum[0] = sign = num1[0]; //�������� ���� ����������
		for (int i = SIZE; i > 0; i--) {
			sum[i] = num1[i] + num2[i] + old_digit;
			old_digit = 0;
			if (sum[i] > 9) { //���� ���������� �������� 1 � ������� ������
				sum[i] = sum[i] % 10;
				old_digit++;
			}
		}
	}

	else { //���� ����� ������ �� �����, �� �� �������� �������� �������
		int old_digit = 0, max = 0;

		//������� ������� �� ������ �����
		for (int i = 1; i < SIZE + 1; i++) {
			if (num1[i] > num2[i]) {
				max = 1; //������ ����� ������
				break;
			}
			else if (num2[i] > num1[i]) {
				max = 2; //������ ����� ������
				break;
			}
		}
		//

		//���� ��� ����� ����� �� ������
		if (max == 0) {
			null(sum);
			sum[0] = sign = 0;
		}
		//

		//���� ������ ����� ������
		else if (max == 1) {
			sum[0] = sign = num1[0];
			for (int i = SIZE; i > 0; i--) {
				sum[i] = num1[i] - num2[i] - old_digit; //�� �������� ��� ������� �����
				old_digit = 0;
				if (sum[i] < 0) { //������ ����� > 0, ���� ��� <0
					sum[i] = sum[i] + 10;
					old_digit++;
				}
			}
		}
		//

		//���� ������ ����� ������
		else {
			sum[0] = sign = num2[0];
			for (int i = SIZE; i > 0; i--) {
				sum[i] = num2[i] - num1[i] - old_digit; //�� �������� ��� ������� �����
				old_digit = 0;
				if (sum[i] < 0) { //������ ����� > 0, ���� ��� <0
					sum[i] = sum[i] + 10;
					old_digit++;
				}
			}
		}
		//
	}

	//�������� �� ������������
	if (sum[0] != sign) {
		overflow = 1;
		return;
	}
	//

	//���������� ����������
	result[0] = sign;
	for (int i = 1; i < SIZE + 1; i++)
		result[i] = sum[i];
	//
}

void multiplication(int num1[], int num2[], int result[]) //��������� ������������ ���� �����
{
	int multi[SIZE + 1] = { 0 };

	//���������� ������� �����
	int k;
	for (k = 1; num1[k] == 0; k++);
	int size_num1 = (SIZE + 1) - k;
	for (k = 1; num2[k] == 0; k++);
	int size_num2 = (SIZE + 1) - k;
	//

	//���������� ���� ������������
	if (num1[0] == num2[0])
		multi[0] = 0;
	else
		multi[0] = 1;
	int sign = multi[0];
	//

	//����������� "� ���"
	for (int i = 0; i < size_num1; i++)
		for (int j = 0; j < size_num2; j++)
			multi[SIZE - i - j] += num1[SIZE - i] * num2[SIZE - j];
	//

	//������������ �� 1 ����� � ������ ������
	for (int i = SIZE; i > 1; i--) {
		if (multi[i] > 9) {
			multi[i - 1] += multi[i] / 10;
			multi[i] %= 10;
		}
	}
	//

	//�������� �� ������������
	if (multi[0] != sign) {
		overflow = 1;
		return;
	}
	//

	//��������� ���������
	result[0] = sign;
	for (int i = 0; i < SIZE; i++)
		result[SIZE - i] = multi[SIZE - i];
	//
}

void exp(int num1[], int num2[], int result[]) { //��������� ���������� � �������
	//�������� �� ���� ������������ �������
	if (num2[0] == 1) {
		printf("WARNING! This program can raise only to a power >= 0");
		overflow = 2;
		return;
	}
	//

	//������� -1, ������� ����� ���������� � num2 �� ������ �������� ���������
	int unit[SIZE + 1] = { 0 };
	unit[0] = 1;
	unit[SIZE] = 1;
	int i;
	//

	//������� ����� base = ������������ num1, � ������� ����� ������������ ���������� � ������� ����������
	int base[SIZE + 1];
	for (int j = 0; j < SIZE + 1; j++)
		base[j] = num1[j];
	//

	//���� ���������� ��������� � ������� = 0
	for (i = 1; num2[i] == 0; i++);
	if (i == SIZE + 1) {
		printf("Result = 1");
		return;
	}
	//

	//���� ��������� ���������� � ������� = 1
	if ((i == SIZE) && (num2[i] == 1)){
		output(num1);
		return;
	}
	//

	do {
		multiplication(base, num1, result); //�������� base �� num1
		for (int j = 0; j < SIZE + 1; j++)
			base[j] = result[j]; //���������� ��������� � base
		null(result);

		summator(0, num2, unit, result); //�������� ������� �� num2
		for (int j = 0; j < SIZE + 1; j++)
			num2[j] = result[j]; //���������� ��������� � num2
		null(result);

		for (i = 1; num2[i] == 0; i++);
	} while ((i != SIZE) || (num2[i] != 1)); //������ ��� ���������, �� ����������� �� num2

	//�������� �� ������������ ������
	for (i = 1; base[i] == 0; i++);
	if (i == SIZE + 1)
		overflow = 1;
	else
		for (i = 0; i < SIZE + 1; i++)
			result[i] = base[i];
	//
}

void factorial(int num[], int result[]) { //���������, ����������� ��������� �����
	//�������� �� ���� �������������� �����
	if (num[0] == 1) {
		printf("WARNING! The factorial of negative number is undefined");
		overflow = 2;
		return;
	}
	//
	
	//������� -1, ������� ����� ���������� � num �� ������ �������� ���������
	int unit[SIZE + 1] = { 0 };
	unit[0] = 1;
	unit[SIZE] = 1;
	//

	//������� ����� = 1, � ������� ����� ������������ ��������� ���������� 
	int base[SIZE + 1] = { 0 };
	base[SIZE] = 1;
	//

	//���� ��������� ����� = 0!
	int i;
	for (i = 1; num[i] == 0; i++);
	if ((i == SIZE + 1)|| (i == SIZE)) {
		output(base);
		overflow = 2;
		return;
	}
	//

	do {
		multiplication(base, num, result); //�������� base �� num
		for (int j = 0; j < SIZE + 1; j++)
			base[j] = result[j]; //���������� ��������� � base
		null(result);

		summator(0, num, unit, result); //�������� 1 �� num
		for (int j = 0; j < SIZE + 1; j++)
			num[j] = result[j]; //���������� ��������� � num
		null(result);

		for (i = 1; num[i] == 0; i++);
	} while ((i != SIZE) || (num[i] != 1)); //������ ��� ���������, �� ����������� �� num

	//�������� �� ������������ ������
	for (i = 1; base[i] == 0; i++);
	if (i == SIZE + 1)
		overflow = 1;
	else
		for (i = 0; i < SIZE + 1; i++)
			result[i] = base[i];
	//
}

void range(int num1[], int num2[], int result[]) { //���������, ������������� ����� �� num1 �� num2 
	//������� -1, ������� ����� ���������� � num �� ������ �������� ���������
	int minus[SIZE + 1] = { 0 };
	minus[0] = 1;
	minus[SIZE] = 1;
	//

	//������� 1, ������� ����� ��� �������� ��������� ����� � �������
	int plus[SIZE + 1] = { 0 };
	plus[SIZE] = 1;
	//

	//�������� �� ��������� �����
	int i;
	int k = 0;
	for (i = 1; i < SIZE + 1; i++)
		if (num1[i] == num2[i])
			k++;
	if (k == SIZE) {
		if (num1[0] != num2[0])
			return;
		else {
			for (i = 0; i < SIZE + 1; i++)
				result[i] = num1[i];
			return;
		}
	}
	//

	//��������, ���� num1 > num2
	int max = 0;
	for (i = 1; i < SIZE + 1; i++) {
		if (num1[i] > num2[i]) {
			max = 1; //������ ����� ������
			break;
		}
	}
	if (max == 1) { //������������ ���������� num1 � num2
		int temp[SIZE + 1] = { 0 };
		for (i = 0; i < SIZE + 1; i++) {
			temp[i] = num1[i];
			num1[i] = num2[i];
			num2[i] = temp[i];
		}
	}
	//

	//������ � �������������� �������
	int flag = 0;
	if ((num1[0] == 1) && (num2[0] == 1)) {
		num1[0] = 0;
		num2[0] = 0;
		flag = 1;
	}
	else if ((num1[0] == 0) && (num2[0] == 1)) {
		num2[0] = 0;
		summator(0, num1, plus, result);
		for (int j = 0; j < SIZE + 1; j++)
			num1[j] = result[j];
		null(result);
		flag = 1;
	}
	//

	//������� base = num1 + num2
	int base[SIZE + 1] = { 0 };
	summator(0, num1, num2, result);	
	for (int j = 0; j < SIZE + 1; j++)
		base[j] = result[j];
	null(result);
	//

	// ���������� ���������� ��������� � [num1;num2]
	int size[SIZE + 1] = { 0 };
	summator(1, num2, num1, result);
	summator(0, result, plus, size);
	//

	//����������� base �� ���������� �����
	multiplication(base, size, result);
	for (int j = 0; j < SIZE + 1; j++)
		base[j] = result[j];
	//

	//���������� �������� ������� �� 2 � �������� �� ������������� �����
	int pred = 0;
	for (i = 1; i < SIZE + 1; i++) {
		base[i] += 10 * pred;
		pred = 0;
		if (base[i] % 2 == 0) 
			base[i] /= 2;
		else {
			pred++;
			base[i] /= 2;
		}
	}
	//

	//�������� �� ������������ ������
	for (i = 1; base[i] == 0; i++);
	if (i == SIZE + 1)
		overflow = 1;
	else
		for (i = 0; i < SIZE + 1; i++)
			result[i] = base[i];

	//�������� �� ������������� �����
	if (flag == 1) result[0] = 1;
	//
}

int main() {
	clock_t start, end;
	double time = 0;
	int choose;
	int num1[SIZE + 1] = { 0 };
	int num2[SIZE + 1] = { 0 };
	int result[SIZE + 1] = { 0 };
	printf("Please select the action : \n1)The addition of two numbers; \n2)The subtraction of two numbers; \n3)The multiplication of two numbers; \n4)Exponentiation\n5)The factorial of a number; \n6)The sum of all numbers in this range\n");
	if (scanf("%d", &choose) != 1) {
		printf("Error of entering");
		return -1;
	}

	if (choose == 1) {
		input(num1);
		input(num2);
		start = clock();
		summator(0, num1, num2, result);
		end = clock();
		check_overflow(overflow, result);
	}
	else if (choose == 2){
		input(num1);
		input(num2);
		start = clock();
		summator(1, num1, num2, result);
		end = clock();
		check_overflow(overflow, result);
	}
	else if (choose == 3) {
		input(num1);
		input(num2);
		start = clock();
		multiplication(num1, num2, result);
		end = clock();
		check_overflow(overflow, result);
	}
	else if (choose == 4) {
		input(num1);
		input(num2);
		start = clock();
		exp(num1, num2, result);
		end = clock();
		check_overflow(overflow, result);
	}
	else if (choose == 5) {
		input(num1);
		start = clock();
		factorial(num1, result);
		end = clock();
		check_overflow(overflow, result);
	}
	else if (choose == 6) {
		input(num1);
		input(num2);
		start = clock();
		range(num1, num2, result);
		end = clock();
		check_overflow(overflow, result);
	}
	else {
		printf("WARNING! Enter the number of action in range [1;6]\nRestart the program\n");
		return -1;
	}
	
	time = (double)(end - start) / ((double)CLOCKS_PER_SEC);
	printf("The program took %f seconds to execute \n", time);

	return 0;
}