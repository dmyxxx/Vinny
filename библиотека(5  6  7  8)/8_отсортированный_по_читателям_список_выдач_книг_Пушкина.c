#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 200
#define MAX_BOOK_LENGTH 100
#define MAX_READER_LENGTH 100
#define MAX_DATE_LENGTH 11
#define TARGET_AUTHOR "Пушкин"

// Структура для хранения информации о книгах
typedef struct {
    char date[MAX_DATE_LENGTH];
    char reader[MAX_READER_LENGTH];
    char book[MAX_BOOK_LENGTH];
    char author[MAX_READER_LENGTH];
} BookRecord;

// Функция для сравнения строк (читателей) для сортировки
int compare(const void *a, const void *b) {
    const BookRecord *recordA = (const BookRecord *)a;
    const BookRecord *recordB = (const BookRecord *)b;
    return strcmp(recordA->reader, recordB->reader);
}

// Функция для фильтрации и сортировки записей о книгах Пушкина по читателям
void sortPushkinBooks(FILE *input, FILE *output) {
    BookRecord records[100];
    int numRecords = 0;

    // Считываем данные из входного файла
    while (fscanf(input, "%s %s %[^\n]", records[numRecords].date, records[numRecords].reader, records[numRecords].book) != EOF) {
        // Считываем остаток строки в поле автора книги
        fgets(records[numRecords].author, MAX_READER_LENGTH, input);
        // Удаляем лишние пробелы и символ переноса строки из автора
        records[numRecords].author[strcspn(records[numRecords].author, "\r\n")] = 0;

        numRecords++;
    }

    // Отфильтровываем записи о книгах Пушкина
    int pushkinCount = 0;
    for (int i = 0; i < numRecords; i++) {
        if (strstr(records[i].author, TARGET_AUTHOR) != NULL) {
            // Записываем только читателей и книги Пушкина
            fprintf(output, "%s\n%s\n", records[i].reader, records[i].book);
            pushkinCount++;
        }
    }

    // Если не найдено книг Пушкина, сообщаем об этом
    if (pushkinCount == 0) {
        fprintf(output, "Нет записей о книгах Пушкина\n");
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

    // Сортировка и запись в выходной файл
    sortPushkinBooks(input, output);

    // Закрытие файлов
    fclose(input);
    fclose(output);

    return 0;
}
