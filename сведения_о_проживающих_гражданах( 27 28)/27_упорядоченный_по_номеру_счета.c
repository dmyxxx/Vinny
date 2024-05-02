#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

// Структура для хранения информации о проживающем
typedef struct {
    char lastname[MAX_LINE_LENGTH];
    char street[MAX_LINE_LENGTH];
    int house;
    int flat;
    char account[MAX_LINE_LENGTH];
} ResidentInfo;

// Функция для сравнения проживающих по номеру лицевого счета (для сортировки)
int compare(const void *a, const void *b) {
    const ResidentInfo *residentA = (const ResidentInfo *)a;
    const ResidentInfo *residentB = (const ResidentInfo *)b;
    return strcmp(residentA->account, residentB->account);
}

// Функция для формирования списка лицевых счетов
void generateAccountsList(FILE *input, FILE *output) {
    ResidentInfo residents[100] = {0}; // Инициализация массива для хранения информации о проживающих
    int num_residents = 0;

    // Считываем данные из входного файла
    while (fscanf(input, "%s %s %d %d %s", residents[num_residents].lastname, residents[num_residents].street,
                  &residents[num_residents].house, &residents[num_residents].flat, residents[num_residents].account) == 5) {
        num_residents++;
    }

    // Сортируем список по номеру лицевого счета
    qsort(residents, num_residents, sizeof(ResidentInfo), compare);

    // Записываем результаты в выходной файл
    fprintf(output, "Структура выходного файла out.txt\n");
    for (int i = 0; i < num_residents; ++i) {
        fprintf(output, "%s %s, ул. %s, %d, кв. %d\n", residents[i].account, residents[i].lastname, residents[i].street,
                residents[i].house, residents[i].flat);
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

    // Формирование списка лицевых счетов
    generateAccountsList(input, output);

    // Закрытие файлов
    fclose(input);
    fclose(output);

    return 0;
}
