#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

// Структура для хранения информации о марке
typedef struct {
    int year;
    int count;
} StampInfo;

// Функция для сравнения марок по году выпуска (для сортировки)
int compare(const void *a, const void *b) {
    const StampInfo *stampA = (const StampInfo *)a;
    const StampInfo *stampB = (const StampInfo *)b;
    return stampA->year - stampB->year;
}

// Функция для формирования списка количества марок по годам выпуска
void countStampsByYear(FILE *input, FILE *output) {
    StampInfo stamps[100] = {0}; // Инициализация массива для хранения информации о марках
    int num_stamps = 0;

    // Считываем данные из входного файла
    int year;
    char mark[MAX_LINE_LENGTH];
    char country[MAX_LINE_LENGTH];
    int album, price;
    while (fscanf(input, "%s %s %d %d %d", mark, country, &year, &album, &price) == 5) {
        // Проверяем, существует ли уже информация о марке с данным годом выпуска
        int exists = 0;
        for (int i = 0; i < num_stamps; ++i) {
            if (stamps[i].year == year) {
                exists = 1;
                stamps[i].count++;
                break;
            }
        }

        // Если информация о марке с данным годом выпуска не существует, добавляем ее
        if (!exists) {
            stamps[num_stamps].year = year;
            stamps[num_stamps].count = 1;
            num_stamps++;
        }
    }

    // Сортируем список по году выпуска
    qsort(stamps, num_stamps, sizeof(StampInfo), compare);

    // Записываем результаты в выходной файл
    fprintf(output, "Год Количество\n");
    for (int i = 0; i < num_stamps; ++i) {
        fprintf(output, "%d %d\n", stamps[i].year, stamps[i].count);
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

    // Формирование списка количества марок по годам выпуска
    countStampsByYear(input, output);

    // Закрытие файлов
    fclose(input);
    fclose(output);

    return 0;
}
