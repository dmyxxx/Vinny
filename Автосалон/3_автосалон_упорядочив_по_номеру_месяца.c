#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

// Структура для хранения информации о продажах автомобилей
typedef struct {
    int day;
    int month;
    int year;
    char manager[50];
    char brand[50];
    int price;
} CarSale;

// Функция для подсчета количества проданных автомобилей за каждый месяц
void countSales(FILE *input, FILE *output) {
    CarSale sales[100];
    int numSales = 0;

    // Считываем данные из входного файла
    while (fscanf(input, "%d.%d.%d %s %s %d", &sales[numSales].day, &sales[numSales].month, &sales[numSales].year,
                  sales[numSales].manager, sales[numSales].brand, &sales[numSales].price) != EOF) {
        numSales++;
                  }

    // Подсчитываем количество проданных автомобилей за каждый месяц
    int countPerMonth[13] = {0}; // Индекс 0 не используется, начинаем с индекса 1 для января
    for (int i = 0; i < numSales; i++) {
        countPerMonth[sales[i].month]++;
    }

    // Записываем результаты в выходной файл
    fprintf(output, "Месяц года Количество\n");
    for (int i = 1; i <= 12; i++) {
        fprintf(output, "%02d.%d %d\n", i, sales[0].year, countPerMonth[i]);
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

    // Подсчет количества проданных автомобилей за каждый месяц
    countSales(input, output);

    // Закрытие файлов
    fclose(input);
    fclose(output);

    return 0;
}
