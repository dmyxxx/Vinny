#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

// Структура для хранения информации о книгах, взятых читателями
typedef struct {
    char date[11];
    char reader[50];
    int numBooks;
} BookRecord;

// Функция для подсчета количества книг, взятых каждым читателем за все время
void countBooksByReader(FILE *input, FILE *output) {
    BookRecord records[100];
    int numRecords = 0;

    // Считываем данные из входного файла
    while (fscanf(input, "%s %s %d", records[numRecords].date, records[numRecords].reader, &records[numRecords].numBooks) != EOF) {
        numRecords++;
    }

    // Подсчитываем количество книг, взятых каждым читателем за все время
    int totalBooks[100] = {0}; // Массив для хранения общего количества книг каждого читателя
    char uniqueReaders[100][50]; // Массив для хранения уникальных фамилий читателей
    int numUniqueReaders = 0;

    // Проходим по всем записям и суммируем количество книг для каждого читателя
    for (int i = 0; i < numRecords; i++) {
        int isNewReader = 1;
        for (int j = 0; j < numUniqueReaders; j++) {
            if (strcmp(records[i].reader, uniqueReaders[j]) == 0) {
                totalBooks[j] += records[i].numBooks;
                isNewReader = 0;
                break;
            }
        }
        if (isNewReader) {
            strcpy(uniqueReaders[numUniqueReaders], records[i].reader);
            totalBooks[numUniqueReaders] = records[i].numBooks;
            numUniqueReaders++;
        }
    }

    // Сортируем читателей и количество книг по фамилии читателя
    for (int i = 0; i < numUniqueReaders - 1; i++) {
        for (int j = i + 1; j < numUniqueReaders; j++) {
            if (strcmp(uniqueReaders[i], uniqueReaders[j]) > 0) {
                int tempBooks = totalBooks[i];
                totalBooks[i] = totalBooks[j];
                totalBooks[j] = tempBooks;
                char tempReader[50];
                strcpy(tempReader, uniqueReaders[i]);
                strcpy(uniqueReaders[i], uniqueReaders[j]);
                strcpy(uniqueReaders[j], tempReader);
            }
        }
    }

    // Записываем результаты в выходной файл
    fprintf(output, "Читатель Количество\n");
    for (int i = 0; i < numUniqueReaders; i++) {
        fprintf(output, "%s %d\n", uniqueReaders[i], totalBooks[i]);
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

    // Подсчет количества книг, взятых каждым читателем за все время
    countBooksByReader(input, output);

    // Закрытие файлов
    fclose(input);
    fclose(output);

    return 0;
}
