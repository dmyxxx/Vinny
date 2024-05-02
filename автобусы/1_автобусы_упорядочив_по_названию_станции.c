#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATION_LENGTH 50

// Структура для хранения информации о движении автобусов
typedef struct {
    char number[10];
    char time[10];
    char station[MAX_STATION_LENGTH];
} BusInfo;

// Функция для подсчёта количества рейсов до каждой станции
void countRoutes(FILE *input, FILE *output) {
    char station[MAX_STATION_LENGTH];
    int count = 0;

    fscanf(input, "%s", station); // Считываем первую станцию
    while (!feof(input)) {
        char number[10], time[10];
        fscanf(input, "%s %s", number, time);

        if (strcmp(station, "") == 0) // Пропускаем пустую строку
            break;

        count++;

        char nextStation[MAX_STATION_LENGTH];
        fscanf(input, "%s", nextStation);

        // Если следующая станция отличается от текущей, записываем результат и обновляем текущую станцию
        if (strcmp(station, nextStation) != 0) {
            fprintf(output, "%s %d\n", station, count);
            strcpy(station, nextStation);
            count = 0;
        }
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

    // Подсчёт количества рейсов до каждой станции
    countRoutes(input, output);

    // Закрытие файлов
    fclose(input);
    fclose(output);

    return 0;
}
