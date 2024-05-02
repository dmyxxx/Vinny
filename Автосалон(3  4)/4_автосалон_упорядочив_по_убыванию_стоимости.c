#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

// Структура для хранения информации о продажах автомобилей
typedef struct {
    char date[11];
    char manager[50];
    char brand[50];
    int price;
} CarSale;

// Функция для подсчета стоимости проданных автомобилей каждым менеджером
void countSalesByManager(FILE *input, FILE *output) {
    CarSale sales[100];
    int numSales = 0;

    // Считываем данные из входного файла
    while (fscanf(input, "%s %s %s %d", sales[numSales].date, sales[numSales].manager, sales[numSales].brand, &sales[numSales].price) != EOF) {
        numSales++;
    }

    // Подсчитываем стоимость проданных автомобилей каждым менеджером
    int totalSales[100] = {0}; // Инициализируем массив для хранения общей стоимости продаж каждого менеджера
    char uniqueManagers[100][50]; // Массив для хранения уникальных фамилий менеджеров
    int numUniqueManagers = 0;

    // Проходим по всем продажам и суммируем стоимость продаж для каждого менеджера
    for (int i = 0; i < numSales; i++) {
        int isNewManager = 1;
        for (int j = 0; j < numUniqueManagers; j++) {
            if (strcmp(sales[i].manager, uniqueManagers[j]) == 0) {
                totalSales[j] += sales[i].price;
                isNewManager = 0;
                break;
            }
        }
        if (isNewManager) {
            strcpy(uniqueManagers[numUniqueManagers], sales[i].manager);
            totalSales[numUniqueManagers] = sales[i].price;
            numUniqueManagers++;
        }
    }

    // Сортируем менеджеров и стоимость продаж по убыванию стоимости
    for (int i = 0; i < numUniqueManagers - 1; i++) {
        for (int j = i + 1; j < numUniqueManagers; j++) {
            if (totalSales[i] < totalSales[j]) {
                int tempSales = totalSales[i];
                totalSales[i] = totalSales[j];
                totalSales[j] = tempSales;
                char tempManager[50];
                strcpy(tempManager, uniqueManagers[i]);
                strcpy(uniqueManagers[i], uniqueManagers[j]);
                strcpy(uniqueManagers[j], tempManager);
            }
        }
    }

    // Записываем результаты в выходной файл
    fprintf(output, "Менеджер Стоимость\n");
    for (int i = 0; i < numUniqueManagers; i++) {
        fprintf(output, "%s %d\n", uniqueManagers[i], totalSales[i]);
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

    // Подсчет стоимости проданных автомобилей каждым менеджером
    countSalesByManager(input, output);

    // Закрытие файлов
    fclose(input);
    fclose(output);

    return 0;
}
