#define LEN (30 + 1)
#include <stdio.h>
#include <time.h>

int dlina_stroki(char* stroka) {//бшвхякемхе дкхмш ярпнйх - юкэрепмюрхбю STRLEN()
	int dlina = 0, i = 0;
	while (stroka[i++] != '\0') dlina++;
	return dlina;
}

int matrix_create(int len[LEN][LEN], char* stroka, int left, int right) {
	if (len[left][right] == -1)
		if (stroka[left] == stroka[right]) len[left][right] = (matrix_create(len, stroka, left + 1, right - 1) + 2); //еякх щкелемрш пюбмш, рн сдюкърэ щкелемрш ме мюдн, щрн еярэ оюкхмдпнл => опхаюбкъел 2
		else if (matrix_create(len, stroka, left + 1, right) > matrix_create(len, stroka, left, right - 1)) len[left][right] = matrix_create(len, stroka, left + 1, right);//еякх щкелемрш ме пюбмш, рн сдюкъел рнр щкелемр, йнрнпши дюяр мюханкэьсч дкхмс
		else len[left][right] = matrix_create(len, stroka, left, right - 1);
	return len[left][right];
}

void palindrome_create(int len[LEN][LEN], char* stroka, char* palindrome, int left, int right, int left_palindrome, int right_palindrome) {
	while (left <= right)//опнбепйю мю бшунд хг ярпнйх
		if ((left == right) && (len[left][right]) == 1) palindrome[left_palindrome++] = stroka[left++];//еякх днькх дн опедекю х опх щрнл яннрберярбсчыхи щкелемр люяяхбю онкнфхрекем, гюохяшбюел ецн б оюкхмдпнл + хмйпхлемжхъ
		else {
			if (stroka[left] == stroka[right]) {//еякх щкелемрш ярпнйх я цпюмхвмшлх хмдейяюлх пюбмш
				palindrome[left_palindrome++] = stroka[left++];//гюохяшюел б оюкхмдпнл якебю + хмйпхлемжхъ
				palindrome[right_palindrome--] = stroka[right--];//гюохяшбюел б оюкхмдпнл яопюбю + хмйпхлемжхъ
			}
			else {
				if (len[left + 1][right] > len[left][right - 1]) left++; //еякх щкелемр люяяхбю, ярнъыхи мю 1 онгхжхч мхфе, анкэье вел щкелемр люяяхбю, ярнъыхи мю ндмс онгхжхч кебее
				else right--;//сбекхвхбюел кебсч цпюмхжс, хмюве слемэьюел опюбсч цпюмхжс
			}
		}
}

int main() {
	char stroka[LEN] = { 0 }, palindrome[LEN] = {0};
	printf("Enter the string:\n");
	gets(stroka);
	int n = dlina_stroki(stroka); int len[LEN][LEN] = { 0 };

	//дбслепмши люяяхб, упюмъыхи б яеае люйяхлюкэмсч дкхмс ондоюкхмдпнлнб дкъ ярпнйх (ондярпнйх), щкелемрш йнрнпни нцпюмхвемш нр i дн j
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
			if (i == j) len[i][j] = 1;//дхюцнмюкэ = 1, р.е. ондярпнйю, нцпюмхвеммюъ нр i дн j (i = j), р.е дкхмю пюбмю 1, нмю яюлю х еярэ оюкхмдпнл
			else if (i > j) len[i][j] = 0;//мхфмъъ вюярэ нрмняхрекэмн дхюцнмюкх = 0
			else len[i][j] = -1;//бепумюъъ вюярэ нрмняхрекэмн дхюцнмюкх = -1 (нцпюмхвхбюел пюанвсч накюярэ)
		}
	//мюханкэьюъ дкхмю оюкхмдпнлю асдер гюохяюмю б опюбнл бепумел сцкс люрпхжш

	clock_t start = clock();
	matrix_create(len, stroka, 0, n-1);//онярпнемхе люрпхжш дкхм
	palindrome_create(len, stroka, palindrome, 0, n-1, 0, len[0][n-1] - 1);//онярпнемхе онкнбхмш оюкхмдпнлю
	clock_t end = clock();
	double time = (double)(end - start) / ((double)CLOCKS_PER_SEC);
	printf("%s\n", palindrome);

	int k = 0, m = 0, flag = 0;
	for (k; k < dlina_stroki(stroka); k++) {
		if (palindrome[m] != stroka[k]) {
			printf("%d - %c\n", k + 1, stroka[k]);//бшбнд сдюкеммнцн щкелемрю
			flag = 1;
		}
		else flag = 0;
		if (flag == 0) m++;
	}
	printf("The program took %f seconds to execute\n", time);
	return 0;
}