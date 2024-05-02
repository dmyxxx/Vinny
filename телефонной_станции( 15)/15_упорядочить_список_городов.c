#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 200
#define MAX_CITY_LENGTH 100

// Структура для хранения информации о разговоре
typedef struct {
    char city[MAX_CITY_LENGTH];
    int cost;
} Call;

// Функция для сравнения строк (городов) для сортировки
int compare(const void *a, const void *b) {
    const Call *callA = (const Call *)a;
    const Call *callB = (const Call *)b;
    return strcmp(callA->city, callB->city);
}

// Функция для подсчета стоимости разговоров по каждому городу
void calculateCallCosts(FILE *input, FILE *output) {
    Call calls[100];
    int numCalls = 0;

    // Считываем данные из входного файла
    while (fscanf(input, "%*c%d:%*d%s %d", &calls[numCalls].cost, calls[numCalls].city, &calls[numCalls].cost) != EOF) {
        numCalls++;
    }

    // Создаем хэш-таблицу для подсчета общей стоимости разговоров по каждому городу
    int cityCosts[100] = {0}; // Массив для хранения общей стоимости разговоров по каждому городу
    char uniqueCities[100][MAX_CITY_LENGTH]; // Массив для хранения уникальных городов
    int numUniqueCities = 0;

    // Проходим по всем разговорам и суммируем стоимость разговоров по каждому городу
    for (int i = 0; i < numCalls; i++) {
        int isNewCity = 1;
        for (int j = 0; j < numUniqueCities; j++) {
            if (strcmp(calls[i].city, uniqueCities[j]) == 0) {
                cityCosts[j] += calls[i].cost;
                isNewCity = 0;
                break;
            }
        }
        if (isNewCity) {
            strcpy(uniqueCities[numUniqueCities], calls[i].city);
            cityCosts[numUniqueCities] = calls[i].cost;
            numUniqueCities++;
        }
    }

    // Сортируем список по городам
    for (int i = 0; i < numUniqueCities - 1; i++) {
        for (int j = i + 1; j < numUniqueCities; j++) {
            if (strcmp(uniqueCities[i], uniqueCities[j]) > 0) {
                int tempCost = cityCosts[i];
                cityCosts[i] = cityCosts[j];
                cityCosts[j] = tempCost;

                char tempCity[MAX_CITY_LENGTH];
                strcpy(tempCity, uniqueCities[i]);
                strcpy(uniqueCities[i], uniqueCities[j]);
                strcpy(uniqueCities[j], tempCity);
            }
        }
    }

    // Записываем результаты в выходной файл
    fprintf(output, "Город Стоимость\n");
    for (int i = 0; i < numUniqueCities; i++) {
        fprintf(output, "%s %d\n", uniqueCities[i], cityCosts[i]);
    }
}

int main() {
    FILE *input, *output;

    // Открытие входного и выходного файлов
    input = fopen("in.txt", "r");
    if (input == NULL) {
        printf("Cannot open input file.\n");
        return 1;
    }

    output = fopen("out.txt", "w");
    if (output == NULL) {
        printf("Cannot open output file.\n");
        fclose(input);
        return 1;
    }

    // Подсчет стоимости разговоров по каждому городу
    calculateCallCosts(input, output);

    // Закрытие файлов
    fclose(input);
    fclose(output);

    return 0;
}
