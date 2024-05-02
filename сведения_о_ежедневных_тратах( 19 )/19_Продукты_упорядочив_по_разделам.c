#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 200
#define MAX_CATEGORY_LENGTH 100

// Структура для хранения информации о тратах
typedef struct {
    char date[6];
    char category[MAX_CATEGORY_LENGTH];
    char item[MAX_CATEGORY_LENGTH];
    int amount;
} Expense;

// Функция для сравнения строк (разделов) для сортировки
int compare(const void *a, const void *b) {
    const Expense *expenseA = (const Expense *)a;
    const Expense *expenseB = (const Expense *)b;
    return strcmp(expenseA->category, expenseB->category);
}

// Функция для формирования списка трат по статье "Продукты" и упорядочивания по разделам
void listExpensesByCategory(FILE *input, FILE *output, const char *desiredCategory) {
    Expense expenses[100];
    int numExpenses = 0;

    // Инициализируем хэш-таблицу
    for (int i = 0; i < 100; i++) {
        strcpy(expenses[i].category, "");
        strcpy(expenses[i].item, "");
        expenses[i].amount = 0;
    }

    // Считываем данные из входного файла и сохраняем их в структурах Expense
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, input) != NULL) {
        sscanf(line, "%5s %99s %99[^\n] %d", expenses[numExpenses].date, expenses[numExpenses].category, expenses[numExpenses].item, &expenses[numExpenses].amount);
        if (strcmp(expenses[numExpenses].category, desiredCategory) == 0) {
            numExpenses++;
        }
    }

    // Сортируем список трат по разделам
    qsort(expenses, numExpenses, sizeof(Expense), compare);

    // Записываем результаты в выходной файл
    fprintf(output, "Дата Раздел Сумма\n");
    for (int i = 0; i < numExpenses; i++) {
        fprintf(output, "%s %s %d\n", expenses[i].date, expenses[i].item, expenses[i].amount);
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


    // Формирование списка трат по статье "Продукты" и упорядочивание по разделам
    listExpensesByCategory(input, output, "Продукты");

    // Закрытие файлов
    fclose(input);
    fclose(output);

    return 0;
}
