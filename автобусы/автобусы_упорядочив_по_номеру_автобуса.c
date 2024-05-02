#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUS_NUMBER_LENGTH 10

// Структура для хранения информации о движении автобусов
typedef struct {
    char number[MAX_BUS_NUMBER_LENGTH];
    char station[50];
    int passengers;
} BusInfo;

// Функция для подсчета общего количества пассажиров, перевезенного каждым автобусом
void countPassengers(FILE *input, FILE *output) {
    BusInfo buses[100];
    int numBuses = 0;

    // Считываем данные из входного файла
    while (fscanf(input, "%s %s %d", buses[numBuses].number, buses[numBuses].station, &buses[numBuses].passengers) != EOF) {
        numBuses++;
    }

    // Сортируем данные по номеру автобуса
    for (int i = 0; i < numBuses - 1; i++) {
        for (int j = i + 1; j < numBuses; j++) {
            if (strcmp(buses[i].number, buses[j].number) > 0) {
                BusInfo temp = buses[i];
                buses[i] = buses[j];
                buses[j] = temp;
            }
        }
    }

    // Считаем общее количество пассажиров для каждого автобуса
    int totalPassengers = 0;
    char currentBus[MAX_BUS_NUMBER_LENGTH];
    strcpy(currentBus, buses[0].number);
    for (int i = 0; i < numBuses; i++) {
        if (strcmp(buses[i].number, currentBus) == 0) {
            totalPassengers += buses[i].passengers;
        } else {
            fprintf(output, "%s %d\n", currentBus, totalPassengers);
            totalPassengers = buses[i].passengers;
            strcpy(currentBus, buses[i].number);
        }
    }
    fprintf(output, "%s %d\n", currentBus, totalPassengers); // Записываем данные для последнего автобуса
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

    // Подсчет общего количества пассажиров для каждого автобуса
    countPassengers(input, output);

    // Закрытие файлов
    fclose(input);
    fclose(output);

    return 0;
}
