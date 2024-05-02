#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

// Структура для хранения информации о грузе
typedef struct {
    char rack_number[MAX_LINE_LENGTH];
    char date[MAX_LINE_LENGTH];
    char cargo_name[MAX_LINE_LENGTH];
} Cargo;

// Структура для хранения информации о количестве стеллажей
typedef struct {
    char cargo_name[MAX_LINE_LENGTH];
    int rack_count;
} CargoRackCount;

// Функция для сравнения строк (наименования груза) для сортировки
int compare(const void *a, const void *b) {
    const CargoRackCount *cargoA = (const CargoRackCount *)a;
    const CargoRackCount *cargoB = (const CargoRackCount *)b;
    return strcmp(cargoA->cargo_name, cargoB->cargo_name);
}

// Функция для формирования списка наименований груза с указанием числа использованных стеллажей
void listCargoRackCount(FILE *input, FILE *output) {
    CargoRackCount cargo_rack_count[100] = {0}; // Инициализация массива для хранения количества стеллажей
    int num_cargoes = 0;

    // Считываем данные из входного файла
    Cargo cargo;
    while (fscanf(input, "%s %s %s", cargo.rack_number, cargo.date, cargo.cargo_name) == 3) {
        // Проверяем, существует ли уже информация о данном грузе
        int exists = 0;
        for (int i = 0; i < num_cargoes; ++i) {
            if (strcmp(cargo_rack_count[i].cargo_name, cargo.cargo_name) == 0) {
                exists = 1;
                break;
            }
        }

        // Если груз уже есть в списке, увеличиваем количество стеллажей
        if (exists) {
            for (int i = 0; i < num_cargoes; ++i) {
                if (strcmp(cargo_rack_count[i].cargo_name, cargo.cargo_name) == 0) {
                    cargo_rack_count[i].rack_count++;
                    break;
                }
            }
        } else { // Если груза нет в списке, добавляем его
            strcpy(cargo_rack_count[num_cargoes].cargo_name, cargo.cargo_name);
            cargo_rack_count[num_cargoes].rack_count = 1;
            num_cargoes++;
        }
    }

    // Сортируем список по наименованию груза
    qsort(cargo_rack_count, num_cargoes, sizeof(CargoRackCount), compare);

    // Записываем результаты в выходной файл
    fprintf(output, "Название груза Количество стеллажей\n");
    for (int i = 0; i < num_cargoes; ++i) {
        fprintf(output, "%s %d\n", cargo_rack_count[i].cargo_name, cargo_rack_count[i].rack_count);
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

    // Формирование списка наименований груза с указанием числа использованных стеллажей
    listCargoRackCount(input, output);

    // Закрытие файлов
    fclose(input);
    fclose(output);

    return 0;
}
