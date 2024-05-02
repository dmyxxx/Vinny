#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 200
#define MAX_NAME_LENGTH 100

// Структура для хранения информации о заезде
typedef struct {
    char date[11];
    char name[MAX_NAME_LENGTH];
    char room[4];
    char category[10];
} Booking;

// Функция для сравнения строк (фамилий) для сортировки
int compare(const void *a, const void *b) {
    const Booking *bookingA = (const Booking *)a;
    const Booking *bookingB = (const Booking *)b;
    return strcmp(bookingA->name, bookingB->name);
}

// Функция для фильтрации заездов по категории "Люкс" и формирования списка заездов
void filterAndSortBookings(FILE *input, FILE *output) {
    Booking bookings[100];
    int numBookings = 0;

    // Считываем данные из входного файла
    while (fscanf(input, "%s %s %s %s", bookings[numBookings].date, bookings[numBookings].name, bookings[numBookings].room, bookings[numBookings].category) != EOF) {
        numBookings++;
    }

    // Фильтруем записи, оставляя только категорию "Люкс"
    Booking luxuryBookings[100];
    int numLuxuryBookings = 0;
    for (int i = 0; i < numBookings; i++) {
        if (strcmp(bookings[i].category, "Люкс") == 0) {
            strcpy(luxuryBookings[numLuxuryBookings].date, bookings[i].date);
            strcpy(luxuryBookings[numLuxuryBookings].name, bookings[i].name);
            strcpy(luxuryBookings[numLuxuryBookings].room, bookings[i].room);
            strcpy(luxuryBookings[numLuxuryBookings].category, bookings[i].category);
            numLuxuryBookings++;
        }
    }

    // Сортируем список заездов по фамилии
    qsort(luxuryBookings, numLuxuryBookings, sizeof(Booking), compare);

    // Записываем отсортированный список заездов в выходной файл
    fprintf(output, "Фамилия Номер\n");
    for (int i = 0; i < numLuxuryBookings; i++) {
        fprintf(output, "%s %s\n", luxuryBookings[i].name, luxuryBookings[i].room);
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

    // Фильтрация заездов по категории "Люкс" и формирование списка заездов
    filterAndSortBookings(input, output);

    // Закрытие файлов
    fclose(input);
    fclose(output);

    return 0;
}
