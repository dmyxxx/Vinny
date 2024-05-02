#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 200
#define MAX_HALL_LENGTH 100

// Структура для хранения информации о продаже билетов
typedef struct {
    char time[MAX_LINE_LENGTH];
    char hall[MAX_HALL_LENGTH];
    char movie[MAX_LINE_LENGTH];
    int soldTickets;
} TicketSale;

// Функция для сравнения строк (залов) для сортировки
int compare(const void *a, const void *b) {
    const TicketSale *saleA = (const TicketSale *)a;
    const TicketSale *saleB = (const TicketSale *)b;
    return strcmp(saleA->hall, saleB->hall);
}

// Функция для подсчета количества проданных билетов по каждому залу
void calculateTicketSales(FILE *input, FILE *output) {
    TicketSale sales[100];
    int numSales = 0;

    // Считываем данные из входного файла
    while (fscanf(input, "%s %s %[^0-9]%d", sales[numSales].time, sales[numSales].hall, sales[numSales].movie, &sales[numSales].soldTickets) != EOF) {
        numSales++;
    }

    // Подсчитываем количество проданных билетов для каждого зала
    int totalSales[100] = {0}; // Массив для хранения общего количества проданных билетов для каждого зала
    char uniqueHalls[100][MAX_HALL_LENGTH]; // Массив для хранения уникальных залов
    int numUniqueHalls = 0;

    // Проходим по всем продажам и суммируем количество проданных билетов для каждого зала
    for (int i = 0; i < numSales; i++) {
        int isNewHall = 1;
        for (int j = 0; j < numUniqueHalls; j++) {
            if (strcmp(sales[i].hall, uniqueHalls[j]) == 0) {
                totalSales[j] += sales[i].soldTickets;
                isNewHall = 0;
                break;
            }
        }
        if (isNewHall) {
            strcpy(uniqueHalls[numUniqueHalls], sales[i].hall);
            totalSales[numUniqueHalls] = sales[i].soldTickets;
            numUniqueHalls++;
        }
    }

    // Сортируем результаты по названию зала
    for (int i = 0; i < numUniqueHalls - 1; i++) {
        for (int j = i + 1; j < numUniqueHalls; j++) {
            if (strcmp(uniqueHalls[i], uniqueHalls[j]) > 0) {
                int tempSales = totalSales[i];
                totalSales[i] = totalSales[j];
                totalSales[j] = tempSales;

                char tempHall[MAX_HALL_LENGTH];
                strcpy(tempHall, uniqueHalls[i]);
                strcpy(uniqueHalls[i], uniqueHalls[j]);
                strcpy(uniqueHalls[j], tempHall);
            }
        }
    }

    // Записываем результаты в выходной файл
    fprintf(output, "Зал Продано\n");
    for (int i = 0; i < numUniqueHalls; i++) {
        fprintf(output, "%s %d\n", uniqueHalls[i], totalSales[i]);
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

    // Подсчет количества проданных билетов по каждому залу
    calculateTicketSales(input, output);

    // Закрытие файлов
    fclose(input);
    fclose(output);

    return 0;
}
