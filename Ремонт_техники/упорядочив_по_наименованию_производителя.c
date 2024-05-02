#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 200
#define MAX_MANUFACTURER_LENGTH 100
#define MAX_DATE_LENGTH 11

// Структура для хранения информации о ремонтах
typedef struct {
    char customer[MAX_LINE_LENGTH];
    char device[MAX_LINE_LENGTH];
    char manufacturer[MAX_MANUFACTURER_LENGTH];
    char date[MAX_DATE_LENGTH];
} Repair;

// Функция для подсчета процента невыполненных ремонтов по каждому производителю
void calculateUnfinishedRepairs(FILE *input, FILE *output) {
    Repair repairs[100];
    int numRepairs = 0;

    // Считываем данные из входного файла
    while (fscanf(input, "%s %s %s %s", repairs[numRepairs].customer, repairs[numRepairs].device, repairs[numRepairs].manufacturer, repairs[numRepairs].date) != EOF) {
        numRepairs++;
    }

    // Подсчитываем количество выполненных и невыполненных ремонтов для каждого производителя
    int totalRepairs[100] = {0}; // Массив для хранения общего количества ремонтов для каждого производителя
    int unfinishedRepairs[100] = {0}; // Массив для хранения количества невыполненных ремонтов для каждого производителя
    char uniqueManufacturers[100][MAX_MANUFACTURER_LENGTH]; // Массив для хранения уникальных производителей
    int numUniqueManufacturers = 0;

    // Проходим по всем ремонтам и считаем количество выполненных и невыполненных ремонтов для каждого производителя
    for (int i = 0; i < numRepairs; i++) {
        int isNewManufacturer = 1;
        for (int j = 0; j < numUniqueManufacturers; j++) {
            if (strcmp(repairs[i].manufacturer, uniqueManufacturers[j]) == 0) {
                totalRepairs[j]++;
                if (strcmp(repairs[i].date, "") == 0) {
                    unfinishedRepairs[j]++;
                }
                isNewManufacturer = 0;
                break;
            }
        }
        if (isNewManufacturer) {
            strcpy(uniqueManufacturers[numUniqueManufacturers], repairs[i].manufacturer);
            totalRepairs[numUniqueManufacturers]++;
            if (strcmp(repairs[i].date, "") == 0) {
                unfinishedRepairs[numUniqueManufacturers]++;
            }
            numUniqueManufacturers++;
        }
    }

    // Рассчитываем процент невыполненных ремонтов для каждого производителя
    float percentUnfinished[100];
    for (int i = 0; i < numUniqueManufacturers; i++) {
        percentUnfinished[i] = (float)unfinishedRepairs[i] / totalRepairs[i] * 100;
    }

    // Сортируем результаты по наименованию производителя
    for (int i = 0; i < numUniqueManufacturers - 1; i++) {
        for (int j = i + 1; j < numUniqueManufacturers; j++) {
            if (strcmp(uniqueManufacturers[i], uniqueManufacturers[j]) > 0) {
                int tempTotal = totalRepairs[i];
                totalRepairs[i] = totalRepairs[j];
                totalRepairs[j] = tempTotal;

                int tempUnfinished = unfinishedRepairs[i];
                unfinishedRepairs[i] = unfinishedRepairs[j];
                unfinishedRepairs[j] = tempUnfinished;

                float tempPercent = percentUnfinished[i];
                percentUnfinished[i] = percentUnfinished[j];
                percentUnfinished[j] = tempPercent;

                char tempManufacturer[MAX_MANUFACTURER_LENGTH];
                strcpy(tempManufacturer, uniqueManufacturers[i]);
                strcpy(uniqueManufacturers[i], uniqueManufacturers[j]);
                strcpy(uniqueManufacturers[j], tempManufacturer);
            }
        }
    }

    // Записываем результаты в выходной файл
    fprintf(output, "Производитель Процент\n");
    for (int i = 0; i < numUniqueManufacturers; i++) {
        fprintf(output, "%s %.2f%%\n", uniqueManufacturers[i], percentUnfinished[i]);
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

    // Подсчет процента невыполненных ремонтов по каждому производителю
    calculateUnfinishedRepairs(input, output);

    // Закрытие файлов
    fclose(input);
    fclose(output);

    return 0;
}
