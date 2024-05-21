#define _CRT_SECURE_NO_WARNINGS
#define SIZE 2500
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int overflow = 0;

void input(int number[]) { //процедура ввода числа
	//считываем число в пустой массив
	char number_str[SIZE] = { '\0' };
	printf("Enter the nubmer:\n");
	if (scanf("%s", &number_str) == NULL) {
		printf("Error of entering number");
		return -1;
	}
	//
	
	//проверка на корректность введенного числа (отсеивание букв)
	int flag = 0;
	if ((number_str[0] < '0' && number_str[0] != '-') || number_str[0] >'9') //дополнительная проверка на первый элемент '-'
		flag = 1;
	for (int i = 1; i < strlen(number_str); i++)
		if (number_str[i] < '0' || number_str[i] > '9')
			flag = 1;
	if (flag == 1) {
		printf("Please, enter the number, but not any others symbols!");
		input(number); //сначала вызываем процедуру повторно
		return; //затем выходим из процедуры
	}

	//проверка на положительное число
	if (number_str[0] != '-') {
		for (int i = strlen(number_str); i >= 0; i--) //сдвигаем на один разряд вправо
			number_str[i + 1] = number_str[i];
		number_str[0] = '0'; //первый элемент = 0 (указывает на положительное число)
	}
	else {
		number_str[0] = '1'; //первый элемент = 1 (указывает на отрицательное число)
		number[0] = 1;
	}
	for (int i = 0; i < strlen(number_str) - 1; i++) //переводим число из строкового типа в int
		number[SIZE - i] = number_str[strlen(number_str) - 1 - i] - '0';
	//
}

void output(int result[]) { //процедура вывода числа
	int i = 1;
	for (i; result[i] == 0; i++); //идем до такого i, когда кончаются незначащие нули
	printf("Result = ");
	if (i == 2501) //если такого i не нашлось (т.е. i = 2501), то печатаем 0
		printf("0");
	if (result[0] == 1) //проверка на отрицательное число
		printf("-");
	for (i; i <= SIZE; i++)
		printf("%d", result[i]);
	printf("\n");
}

void check_overflow(int overflow, int result[]) { //процедура, выявляющая переполнение
	if (overflow == 1)
		printf("WARNING! Not enough memory\nRestart the program");
	else if (overflow == 2)
		return;
	else
		output(result);
}

void null(int number[]) { //процедура обнуления массива
	for (int i = 0; i < SIZE + 1; i++)
		number[i] = 0;
}

void summator(int znak, int num1[], int num2[], int result[]) { //процедура суммирования двух чисел
	int sum[SIZE + 1] = { 0 };

	if ((znak == 1) && (num2[0] == 0)) // проверка сложение или вычитание + смена знака
		num2[0] = 1;
	else if ((znak == 1) && (num2[0] == 1)) 
		num2[0] = 0;

	int sign; //переменная, отвечающая за знак

	if (num1[0] == num2[0]) { //если числа равны по знаку, то складываем их поразрядно
		int old_digit = 0; //переменная, отвечающая за увеличение старшего разряда в случае, если сумма > 9
		sum[0] = sign = num1[0]; //передаем знак результату
		for (int i = SIZE; i > 0; i--) {
			sum[i] = num1[i] + num2[i] + old_digit;
			old_digit = 0;
			if (sum[i] > 9) { //если необходимо добавить 1 в старший разряд
				sum[i] = sum[i] % 10;
				old_digit++;
			}
		}
	}

	else { //если числа разные по знаку, то из большего вычитаем меньшее
		int old_digit = 0, max = 0;

		//находим большее по модулю число
		for (int i = 1; i < SIZE + 1; i++) {
			if (num1[i] > num2[i]) {
				max = 1; //первое число больше
				break;
			}
			else if (num2[i] > num1[i]) {
				max = 2; //второе число больше
				break;
			}
		}
		//

		//если два числа равны по модулю
		if (max == 0) {
			null(sum);
			sum[0] = sign = 0;
		}
		//

		//если первое число больше
		else if (max == 1) {
			sum[0] = sign = num1[0];
			for (int i = SIZE; i > 0; i--) {
				sum[i] = num1[i] - num2[i] - old_digit; //не забываем про занятую часть
				old_digit = 0;
				if (sum[i] < 0) { //делаем цифру > 0, если она <0
					sum[i] = sum[i] + 10;
					old_digit++;
				}
			}
		}
		//

		//если второе число больше
		else {
			sum[0] = sign = num2[0];
			for (int i = SIZE; i > 0; i--) {
				sum[i] = num2[i] - num1[i] - old_digit; //не забываем про занятую часть
				old_digit = 0;
				if (sum[i] < 0) { //делаем цифру > 0, если она <0
					sum[i] = sum[i] + 10;
					old_digit++;
				}
			}
		}
		//
	}

	//проверка на переполнение
	if (sum[0] != sign) {
		overflow = 1;
		return;
	}
	//

	//оформление результата
	result[0] = sign;
	for (int i = 1; i < SIZE + 1; i++)
		result[i] = sum[i];
	//
}

void multiplication(int num1[], int num2[], int result[]) //процедура произведения двух чисел
{
	int multi[SIZE + 1] = { 0 };

	//определяем размеры чисел
	int k;
	for (k = 1; num1[k] == 0; k++);
	int size_num1 = (SIZE + 1) - k;
	for (k = 1; num2[k] == 0; k++);
	int size_num2 = (SIZE + 1) - k;
	//

	//определяем знак произведения
	if (num1[0] == num2[0])
		multi[0] = 0;
	else
		multi[0] = 1;
	int sign = multi[0];
	//

	//перемножаем "в лоб"
	for (int i = 0; i < size_num1; i++)
		for (int j = 0; j < size_num2; j++)
			multi[SIZE - i - j] += num1[SIZE - i] * num2[SIZE - j];
	//

	//распределяем по 1 цифре в каждую ячейку
	for (int i = SIZE; i > 1; i--) {
		if (multi[i] > 9) {
			multi[i - 1] += multi[i] / 10;
			multi[i] %= 10;
		}
	}
	//

	//проверка на переполнение
	if (multi[0] != sign) {
		overflow = 1;
		return;
	}
	//

	//оформляем результат
	result[0] = sign;
	for (int i = 0; i < SIZE; i++)
		result[SIZE - i] = multi[SIZE - i];
	//
}

void exp(int num1[], int num2[], int result[]) { //процедура возведения в степень
	//проверка на ввод отрцательной степени
	if (num2[0] == 1) {
		printf("WARNING! This program can raise only to a power >= 0");
		overflow = 2;
		return;
	}
	//

	//создаем -1, которую будем складывать с num2 на каждой этерации процедуры
	int unit[SIZE + 1] = { 0 };
	unit[0] = 1;
	unit[SIZE] = 1;
	int i;
	//

	//создаем число base = изначальному num1, в которое будет записываться возведение в степень постепенно
	int base[SIZE + 1];
	for (int j = 0; j < SIZE + 1; j++)
		base[j] = num1[j];
	//

	//если необходимо возводить в степень = 0
	for (i = 1; num2[i] == 0; i++);
	if (i == SIZE + 1) {
		printf("Result = 1");
		return;
	}
	//

	//если возводить необходимо в степень = 1
	if ((i == SIZE) && (num2[i] == 1)){
		output(num1);
		return;
	}
	//

	do {
		multiplication(base, num1, result); //умножаем base на num1
		for (int j = 0; j < SIZE + 1; j++)
			base[j] = result[j]; //записываем результат в base
		null(result);

		summator(0, num2, unit, result); //вычитаем единицу из num2
		for (int j = 0; j < SIZE + 1; j++)
			num2[j] = result[j]; //записываем результат в num2
		null(result);

		for (i = 1; num2[i] == 0; i++);
	} while ((i != SIZE) || (num2[i] != 1)); //каждый раз проверяем, не закончилось ли num2

	//проверка на переполнение буфера
	for (i = 1; base[i] == 0; i++);
	if (i == SIZE + 1)
		overflow = 1;
	else
		for (i = 0; i < SIZE + 1; i++)
			result[i] = base[i];
	//
}

void factorial(int num[], int result[]) { //процедура, вычисляющая факториал числа
	//проверка на ввод отрицательного числа
	if (num[0] == 1) {
		printf("WARNING! The factorial of negative number is undefined");
		overflow = 2;
		return;
	}
	//
	
	//создаем -1, которую будем складывать с num на каждой этерации процедуры
	int unit[SIZE + 1] = { 0 };
	unit[0] = 1;
	unit[SIZE] = 1;
	//

	//создаем число = 1, в которое будет записываться факториал постепенно 
	int base[SIZE + 1] = { 0 };
	base[SIZE] = 1;
	//

	//если факториал числа = 0!
	int i;
	for (i = 1; num[i] == 0; i++);
	if ((i == SIZE + 1)|| (i == SIZE)) {
		output(base);
		overflow = 2;
		return;
	}
	//

	do {
		multiplication(base, num, result); //умножаем base на num
		for (int j = 0; j < SIZE + 1; j++)
			base[j] = result[j]; //записываем результат в base
		null(result);

		summator(0, num, unit, result); //вычитаем 1 из num
		for (int j = 0; j < SIZE + 1; j++)
			num[j] = result[j]; //записываем результат в num
		null(result);

		for (i = 1; num[i] == 0; i++);
	} while ((i != SIZE) || (num[i] != 1)); //каждый раз проверяем, не закончилось ли num

	//проверка на переполнение буфера
	for (i = 1; base[i] == 0; i++);
	if (i == SIZE + 1)
		overflow = 1;
	else
		for (i = 0; i < SIZE + 1; i++)
			result[i] = base[i];
	//
}

void range(int num1[], int num2[], int result[]) { //процедура, высчитывающая сумму от num1 до num2 
	//создаем -1, которую будем складывать с num на каждой этерации процедуры
	int minus[SIZE + 1] = { 0 };
	minus[0] = 1;
	minus[SIZE] = 1;
	//

	//создаем 1, которая нужна для подсчета количтсва чисел в отрезке
	int plus[SIZE + 1] = { 0 };
	plus[SIZE] = 1;
	//

	//проверка на равенство чисел
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

	//проверка, если num1 > num2
	int max = 0;
	for (i = 1; i < SIZE + 1; i++) {
		if (num1[i] > num2[i]) {
			max = 1; //первое число больше
			break;
		}
	}
	if (max == 1) { //обмениваемся значениями num1 с num2
		int temp[SIZE + 1] = { 0 };
		for (i = 0; i < SIZE + 1; i++) {
			temp[i] = num1[i];
			num1[i] = num2[i];
			num2[i] = temp[i];
		}
	}
	//

	//работа с отрицательными числами
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

	//создаем base = num1 + num2
	int base[SIZE + 1] = { 0 };
	summator(0, num1, num2, result);	
	for (int j = 0; j < SIZE + 1; j++)
		base[j] = result[j];
	null(result);
	//

	// определяем количество элементов в [num1;num2]
	int size[SIZE + 1] = { 0 };
	summator(1, num2, num1, result);
	summator(0, result, plus, size);
	//

	//перемножаем base на количество чисел
	multiplication(base, size, result);
	for (int j = 0; j < SIZE + 1; j++)
		base[j] = result[j];
	//

	//гениальный алгоритм деления на 2 с условием на отрицательные числа
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

	//проверка на переполнение буфера
	for (i = 1; base[i] == 0; i++);
	if (i == SIZE + 1)
		overflow = 1;
	else
		for (i = 0; i < SIZE + 1; i++)
			result[i] = base[i];

	//проверка на отрицательные числа
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