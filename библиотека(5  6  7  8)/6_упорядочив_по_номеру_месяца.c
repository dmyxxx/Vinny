#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 100

// Структура для хранения информации о книгах, взятых читателями
typedef struct {
    int day;
    int month;
    int year;
    char reader[50];
    int numBooks;
} BookRecord;

// Функция для подсчета количества книг, взятых за каждый месяц текущего года
void countBooksByMonth(FILE *input, FILE *output) {
    BookRecord records[100];
    int numRecords = 0;

    // Считываем данные из входного файла
    while (fscanf(input, "%d.%d.%d %s %d", &records[numRecords].day, &records[numRecords].month, &records[numRecords].year, records[numRecords].reader, &records[numRecords].numBooks) != EOF) {
        numRecords++;
    }

    // Подсчитываем количество книг, взятых за каждый месяц текущего года
    int totalBooks[13] = {0}; // Массив для хранения общего количества книг в каждом месяце
    for (int i = 0; i < numRecords; i++) {
        if (records[i].year == 2022) { // Проверяем, что запись относится к текущему году
            totalBooks[records[i].month] += records[i].numBooks;
        }
    }

    // Записываем результаты в выходной файл
    fprintf(output, "Месяц года Количество\n");
    for (int i = 1; i <= 12; i++) {
        fprintf(output, "%02d.2022 %d\n", i, totalBooks[i]);
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

    // Подсчет количества книг, взятых за каждый месяц текущего года
    countBooksByMonth(input, output);

    // Закрытие файлов
    fclose(input);
    fclose(output);

    return 0;
}
