#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 100

// Структура для хранения информации о стеллаже
typedef struct {
    int rack;
    int cell;
    int weight;
} RackInfo;

// Функция для сравнения стеллажей по массе груза (для сортировки)
int compare(const void *a, const void *b) {
    const RackInfo *rackA = (const RackInfo *)a;
    const RackInfo *rackB = (const RackInfo *)b;
    return rackB->weight - rackA->weight; // сортировка по убыванию массы груза
}

// Функция для формирования списка стеллажей с массой загрузки
void listRacksByWeight(FILE *input, FILE *output) {
    RackInfo racks[100] = {0}; // Инициализация массива для хранения информации о стеллажах
    int rack_count = 0;

    // Считываем данные из входного файла
    while (fscanf(input, "%d %d %d", &racks[rack_count].rack, &racks[rack_count].cell, &racks[rack_count].weight) == 3) {
        rack_count++;
    }

    // Сортируем стеллажи по массе груза
    qsort(racks, rack_count, sizeof(RackInfo), compare);

    // Записываем результаты в выходной файл
    fprintf(output, "Название груза Количество стеллажей\nСтеллаж Масса\n");
    for (int i = 0; i < rack_count; i++) {
        if (i == 0 || racks[i].rack != racks[i - 1].rack) {
            fprintf(output, "%d %d\n", racks[i].rack, racks[i].weight);
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

    // Формирование списка стеллажей с массой загрузки
    listRacksByWeight(input, output);

    // Закрытие файлов
    fclose(input);
    fclose(output);

    return 0;
}
