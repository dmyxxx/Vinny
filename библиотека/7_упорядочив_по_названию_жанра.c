#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 200
#define MAX_GENRE_LENGTH 50

// Структура для хранения информации о книге
typedef struct {
    int code;
    char title[MAX_LINE_LENGTH];
    char author[MAX_LINE_LENGTH];
    char genre[MAX_GENRE_LENGTH];
    int year;
} Book;

// Функция для подсчета количества книг каждого жанра
void countBooksByGenre(FILE *input, FILE *output) {
    Book books[100];
    int numBooks = 0;

    // Считываем данные из входного файла
    while (fscanf(input, "%d %[^\n] %[^\n] %[^\n] %d", &books[numBooks].code, books[numBooks].title, books[numBooks].author, books[numBooks].genre, &books[numBooks].year) != EOF) {
        numBooks++;
    }

    // Подсчитываем количество книг каждого жанра
    int countPerGenre[100] = {0}; // Массив для хранения количества книг каждого жанра
    char uniqueGenres[100][MAX_GENRE_LENGTH]; // Массив для хранения уникальных жанров
    int numUniqueGenres = 0;

    // Проходим по всем книгам и суммируем количество книг для каждого жанра
    for (int i = 0; i < numBooks; i++) {
        int isNewGenre = 1;
        for (int j = 0; j < numUniqueGenres; j++) {
            if (strcmp(books[i].genre, uniqueGenres[j]) == 0) {
                countPerGenre[j]++;
                isNewGenre = 0;
                break;
            }
        }
        if (isNewGenre) {
            strcpy(uniqueGenres[numUniqueGenres], books[i].genre);
            countPerGenre[numUniqueGenres] = 1;
            numUniqueGenres++;
        }
    }

    // Сортируем результаты по названию жанра
    for (int i = 0; i < numUniqueGenres - 1; i++) {
        for (int j = i + 1; j < numUniqueGenres; j++) {
            if (strcmp(uniqueGenres[i], uniqueGenres[j]) > 0) {
                int tempCount = countPerGenre[i];
                countPerGenre[i] = countPerGenre[j];
                countPerGenre[j] = tempCount;
                char tempGenre[MAX_GENRE_LENGTH];
                strcpy(tempGenre, uniqueGenres[i]);
                strcpy(uniqueGenres[i], uniqueGenres[j]);
                strcpy(uniqueGenres[j], tempGenre);
            }
        }
    }

    // Записываем результаты в выходной файл
    fprintf(output, "Жанр Количество\n");
    for (int i = 0; i < numUniqueGenres; i++) {
        fprintf(output, "%s %d\n", uniqueGenres[i], countPerGenre[i]);
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

    // Подсчет количества книг каждого жанра
    countBooksByGenre(input, output);

    // Закрытие файлов
    fclose(input);
    fclose(output);

    return 0;
}
