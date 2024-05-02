#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 200
#define MAX_SECTION_LENGTH 100

// Структура для хранения информации о записи
typedef struct {
    char section[MAX_SECTION_LENGTH];
} Record;

// Функция для подсчета количества записей по каждому разделу
void countRecords(FILE *input, FILE *output) {
    Record records[100];
    int numRecords = 0;

    // Считываем данные из входного файла
    while (fscanf(input, "%s %*s %*s %*s", records[numRecords].section) != EOF) {
        numRecords++;
    }

    // Создаем хэш-таблицу для подсчета количества записей по каждому разделу
    int sectionCounts[100] = {0}; // Массив для хранения количества записей по каждому разделу
    char uniqueSections[100][MAX_SECTION_LENGTH]; // Массив для хранения уникальных разделов
    int numUniqueSections = 0;

    // Проходим по всем записям и подсчитываем количество записей по каждому разделу
    for (int i = 0; i < numRecords; i++) {
        int isNewSection = 1;
        for (int j = 0; j < numUniqueSections; j++) {
            if (strcmp(records[i].section, uniqueSections[j]) == 0) {
                sectionCounts[j]++;
                isNewSection = 0;
                break;
            }
        }
        if (isNewSection) {
            strcpy(uniqueSections[numUniqueSections], records[i].section);
            sectionCounts[numUniqueSections]++;
            numUniqueSections++;
        }
    }

    // Записываем результаты в выходной файл
    fprintf(output, "Раздел спецификации Количество\n");
    for (int i = 0; i < numUniqueSections; i++) {
        fprintf(output, "%s %d\n", uniqueSections[i], sectionCounts[i]);
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

    // Подсчет количества записей по каждому разделу
    countRecords(input, output);

    // Закрытие файлов
    fclose(input);
    fclose(output);

    return 0;
}
