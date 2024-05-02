#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 200
#define MAX_SENDER_LENGTH 100
#define MAX_DATE_LENGTH 6

// Структура для хранения информации о движении документов
typedef struct {
    char date[MAX_DATE_LENGTH];
    char document[MAX_LINE_LENGTH];
    char sender[MAX_SENDER_LENGTH];
    char recipient[MAX_SENDER_LENGTH];
} DocumentMovement;

// Функция для сравнения строк (отправителей) для сортировки
int compare(const void *a, const void *b) {
    const DocumentMovement *movementA = (const DocumentMovement *)a;
    const DocumentMovement *movementB = (const DocumentMovement *)b;
    return strcmp(movementA->sender, movementB->sender);
}

// Функция для формирования списка служебных записок, упорядоченного по отправителю
void filterAndSortDocuments(FILE *input, FILE *output) {
    DocumentMovement movements[100];
    int numMovements = 0;

    // Считываем данные из входного файла
    while (fscanf(input, "%s %s %s %s", movements[numMovements].date, movements[numMovements].document, movements[numMovements].sender, movements[numMovements].recipient) != EOF) {
        numMovements++;
    }

    // Отфильтровываем только служебные записки
    DocumentMovement memos[100];
    int numMemos = 0;
    for (int i = 0; i < numMovements; i++) {
        if (strcmp(movements[i].document, "Служебная") == 0) {
            strcpy(memos[numMemos].date, movements[i].date);
            strcpy(memos[numMemos].sender, movements[i].sender);
            strcpy(memos[numMemos].recipient, movements[i].recipient);
            numMemos++;
        }
    }

    // Сортируем список служебных записок по отправителю
    qsort(memos, numMemos, sizeof(DocumentMovement), compare);

    // Записываем результаты в выходной файл
    fprintf(output, "Дата регистрации Отправитель Получатель\n");
    for (int i = 0; i < numMemos; i++) {
        fprintf(output, "%s %s %s\n", memos[i].date, memos[i].sender, memos[i].recipient);
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

    // Фильтрация и сортировка служебных записок
    filterAndSortDocuments(input, output);

    // Закрытие файлов
    fclose(input);
    fclose(output);

    return 0;
}
