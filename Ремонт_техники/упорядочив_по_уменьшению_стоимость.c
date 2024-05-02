#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 200
#define MAX_CUSTOMER_LENGTH 100

// Структура для хранения информации о ремонтах
typedef struct {
    char customer[MAX_CUSTOMER_LENGTH];
    int cost;
} Repair;

// Функция для подсчета общей стоимости ремонтов для каждого заказчика
void calculateRepairCosts(FILE *input, FILE *output) {
    Repair repairs[100];
    int numRepairs = 0;

    // Считываем данные из входного файла
    while (fscanf(input, "%s %*s %*s %d", repairs[numRepairs].customer, &repairs[numRepairs].cost) != EOF) {
        numRepairs++;
    }

    // Подсчитываем общую стоимость ремонтов для каждого заказчика
    int totalCosts[100] = {0}; // Массив для хранения общей стоимости ремонтов для каждого заказчика
    char uniqueCustomers[100][MAX_CUSTOMER_LENGTH]; // Массив для хранения уникальных заказчиков
    int numUniqueCustomers = 0;

    // Проходим по всем ремонтам и суммируем стоимость ремонтов для каждого заказчика
    for (int i = 0; i < numRepairs; i++) {
        int isNewCustomer = 1;
        for (int j = 0; j < numUniqueCustomers; j++) {
            if (strcmp(repairs[i].customer, uniqueCustomers[j]) == 0) {
                totalCosts[j] += repairs[i].cost;
                isNewCustomer = 0;
                break;
            }
        }
        if (isNewCustomer) {
            strcpy(uniqueCustomers[numUniqueCustomers], repairs[i].customer);
            totalCosts[numUniqueCustomers] = repairs[i].cost;
            numUniqueCustomers++;
        }
    }

    // Сортируем результаты по уменьшению стоимости
    for (int i = 0; i < numUniqueCustomers - 1; i++) {
        for (int j = i + 1; j < numUniqueCustomers; j++) {
            if (totalCosts[i] < totalCosts[j]) {
                int tempCost = totalCosts[i];
                totalCosts[i] = totalCosts[j];
                totalCosts[j] = tempCost;

                char tempCustomer[MAX_CUSTOMER_LENGTH];
                strcpy(tempCustomer, uniqueCustomers[i]);
                strcpy(uniqueCustomers[i], uniqueCustomers[j]);
                strcpy(uniqueCustomers[j], tempCustomer);
            }
        }
    }

    // Записываем результаты в выходной файл
    fprintf(output, "Заказчик Стоимость\n");
    for (int i = 0; i < numUniqueCustomers; i++) {
        fprintf(output, "%s %d\n", uniqueCustomers[i], totalCosts[i]);
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

    // Подсчет общей стоимости ремонтов для каждого заказчика
    calculateRepairCosts(input, output);

    // Закрытие файлов
    fclose(input);
    fclose(output);

    return 0;
}
