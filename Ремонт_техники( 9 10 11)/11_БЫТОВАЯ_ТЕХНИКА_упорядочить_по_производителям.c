#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 200
#define MAX_MANUFACTURER_LENGTH 100
#define MAX_DATE_LENGTH 11

// Структура для хранения информации о ремонтах
typedef struct {
    char date[MAX_DATE_LENGTH];
    char client[MAX_LINE_LENGTH];
    char name[MAX_LINE_LENGTH];
    char manufacturer[MAX_MANUFACTURER_LENGTH];
    char category[MAX_LINE_LENGTH];
} Repair;

// Функция для сравнения строк (производителей) для сортировки
int compare(const void *a, const void *b) {
    const Repair *repairA = (const Repair *)a;
    const Repair *repairB = (const Repair *)b;
    return strcmp(repairA->manufacturer, repairB->manufacturer);
}

// Функция для формирования списка сложных ремонтов
void filterAndSortRepairs(FILE *input, FILE *output) {
    Repair repairs[100];
    int numRepairs = 0;

    // Считываем данные из входного файла
    while (fscanf(input, "%s %s %s %s %s", repairs[numRepairs].date, repairs[numRepairs].client, repairs[numRepairs].name, repairs[numRepairs].manufacturer, repairs[numRepairs].category) != EOF) {
        numRepairs++;
    }

    // Отфильтровываем записи по категории "Сложный"
    Repair complexRepairs[100];
    int numComplexRepairs = 0;
    for (int i = 0; i < numRepairs; i++) {
        if (strcmp(repairs[i].category, "Сложный") == 0) {
            strcpy(complexRepairs[numComplexRepairs].date, repairs[i].date);
            strcpy(complexRepairs[numComplexRepairs].client, repairs[i].client);
            strcpy(complexRepairs[numComplexRepairs].name, repairs[i].name);
            strcpy(complexRepairs[numComplexRepairs].manufacturer, repairs[i].manufacturer);
            strcpy(complexRepairs[numComplexRepairs].category, repairs[i].category);
            numComplexRepairs++;
        }
    }

    // Сортируем список сложных ремонтов по производителям
    qsort(complexRepairs, numComplexRepairs, sizeof(Repair), compare);

    // Записываем результаты в выходной файл
    fprintf(output, "Дата обращения Название Производитель Категория\n");
    for (int i = 0; i < numComplexRepairs; i++) {
        fprintf(output, "%s %s %s %s\n", complexRepairs[i].date, complexRepairs[i].name, complexRepairs[i].manufacturer, complexRepairs[i].category);
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

    // Фильтрация и сортировка ремонтов
    filterAndSortRepairs(input, output);

    // Закрытие файлов
    fclose(input);
    fclose(output);

    return 0;
}
