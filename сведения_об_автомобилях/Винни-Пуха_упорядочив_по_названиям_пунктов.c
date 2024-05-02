#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 200
#define MAX_NAME_LENGTH 100

// Структура для хранения информации о рейсе
typedef struct {
    char destination[MAX_NAME_LENGTH];
    int count;
} Trip;

// Функция для сравнения строк (пунктов назначения) для сортировки
int compare(const void *a, const void *b) {
    const Trip *tripA = (const Trip *)a;
    const Trip *tripB = (const Trip *)b;
    return strcmp(tripA->destination, tripB->destination);
}

// Функция для подсчета количества рейсов для каждого пункта назначения
void countTrips(FILE *input, FILE *output) {
    Trip trips[100];
    int numTrips = 0;

    // Инициализируем хэш-таблицу
    for (int i = 0; i < 100; i++) {
        strcpy(trips[i].destination, "");
        trips[i].count = 0;
    }

    // Считываем данные из входного файла и увеличиваем счетчик рейсов для каждого пункта назначения
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, input) != NULL) {
        char *destination = strtok(line, "\n");
        int found = 0;
        for (int i = 0; i < numTrips; i++) {
            if (strcmp(trips[i].destination, destination) == 0) {
                trips[i].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(trips[numTrips].destination, destination);
            trips[numTrips].count++;
            numTrips++;
        }
    }

    // Сортируем список рейсов по пунктам назначения
    qsort(trips, numTrips, sizeof(Trip), compare);

    // Записываем результаты в выходной файл
    fprintf(output, "Пункт назначения Количество рейсов\n");
    for (int i = 0; i < numTrips; i++) {
        fprintf(output, "%s %d\n", trips[i].destination, trips[i].count);
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

    // Подсчет количества рейсов для каждого пункта назначения
    countTrips(input, output);

    // Закрытие файлов
    fclose(input);
    fclose(output);

    return 0;
}
