#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 200

// Структура для хранения информации о событии
typedef struct {
    char date[6];
    char event[MAX_LINE_LENGTH];
    char start_time[6];
    int duration;
    int priority;
} Event;

// Функция для подсчета затрат времени по каждому приоритету
void calculateTimeByPriority(FILE *input, FILE *output) {
    int time_by_priority[10] = {0}; // Инициализация массива для хранения времени по приоритетам

    // Считываем данные из входного файла и подсчитываем затраты времени для каждого приоритета
    Event event;
    while (fscanf(input, "%5s %99[^\n] %5s %d %d", event.date, event.event, event.start_time, &event.duration, &event.priority) == 5) {
        time_by_priority[event.priority] += event.duration; // Увеличиваем время для текущего приоритета
    }

    // Записываем результаты в выходной файл
    fprintf(output, "Приоритет\n");
    fprintf(output, "Время\n");
    for (int i = 1; i < 10; i++) {
        if (time_by_priority[i] != 0) { // Проверяем, что время для текущего приоритета не равно нулю
            fprintf(output, "%d\n", i);
            fprintf(output, "%d\n", time_by_priority[i]);
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

    // Подсчет затрат времени по каждому приоритету
    calculateTimeByPriority(input, output);

    // Закрытие файлов
    fclose(input);
    fclose(output);

    return 0;
}
