#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

// Структура для хранения информации о марке
typedef struct {
    char country[MAX_LINE_LENGTH];
    int total_price;
} StampInfo;

// Функция для сравнения марок по стране (для сортировки)
int compare(const void *a, const void *b) {
    const StampInfo *stampA = (const StampInfo *)a;
    const StampInfo *stampB = (const StampInfo *)b;
    return strcmp(stampA->country, stampB->country);
}

// Функция для формирования списка общей стоимости марок по странам
void calculateTotalPriceByCountry(FILE *input, FILE *output) {
    StampInfo stamps[100] = {0}; // Инициализация массива для хранения информации о марках
    int num_stamps = 0;

    // Считываем данные из входного файла
    char mark[MAX_LINE_LENGTH];
    char country[MAX_LINE_LENGTH];
    int album, year, price;
    while (fscanf(input, "%s %s %d %d %d", mark, country, &album, &year, &price) == 5) {
        // Проверяем, существует ли уже информация о марках из данной страны
        int exists = 0;
        for (int i = 0; i < num_stamps; ++i) {
            if (strcmp(stamps[i].country, country) == 0) {
                exists = 1;
                stamps[i].total_price += price;
                break;
            }
        }

        // Если информация о марках из данной страны не существует, добавляем ее
        if (!exists) {
            strcpy(stamps[num_stamps].country, country);
            stamps[num_stamps].total_price = price;
            num_stamps++;
        }
    }

    // Сортируем список по названию страны
    qsort(stamps, num_stamps, sizeof(StampInfo), compare);

    // Записываем результаты в выходной файл
    fprintf(output, "Страна Стоимость\n");
    for (int i = 0; i < num_stamps; ++i) {
        fprintf(output, "%s %d\n", stamps[i].country, stamps[i].total_price);
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

    // Формирование списка общей стоимости марок по странам
    calculateTotalPriceByCountry(input, output);

    // Закрытие файлов
    fclose(input);
    fclose(output);

    return 0;
}
