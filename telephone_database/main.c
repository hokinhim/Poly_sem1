#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#define MAX 15
#define LEN 50
#include <stdio.h>
#include <string.h>

int main() {

    char base[MAX][LEN] =
    { "Agutin Maksim 89244786543",
    "Mikyshin Anatoly 89215300000",
    "Simanchyk Jaroslava 89650875643",
    "Akopyn Ruben 89320987687",
    "Maslina Jana 89139856787",
    "Mas El Habr 89081345091",
    "Son 89982340976",
    "Daughter 89861231232",
    "Wife 89245610384",
    "Mom 89295038120",
    "Father 89981340934",
    "Loans 89184091342",
    "Savchenko Semen 89762342190",
    "Sergeeva Olga 89129806578833" };
    char name[1][LEN] = { "" };

    while (1) {
        if (scanf("%s", &name[0]) == 1) {

            int count = MAX, flag = 0;
            char base_2[MAX][LEN];

            for (int i = 0; i < MAX; i++) {
                strncpy(base_2[i], base[i], LEN);
            }

            for (int i = 0; i < MAX; i++) {
                if (strstr(strlwr(base_2[i]), strlwr(name[0])) > NULL) {
                    if (flag == 0) {
                        printf("The following subscribers were found:\n");
                        flag = 1;
                    }
                    printf("%s\n", base[i]);
                }
                else {
                    count -= 1;
                }
                if (count == 0) {
                    printf("No results were found for this search: '%s'\n", name[0]);
                }
            }
        }
        else {
            printf("ERROR");
        }
    }

    return 0;
}