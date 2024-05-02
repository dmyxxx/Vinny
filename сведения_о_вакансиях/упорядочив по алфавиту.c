#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 200

// Структура для хранения информации о вакансии
typedef struct {
    char publication_date[6];
    char vacancy[MAX_LINE_LENGTH];
    int salary;
    char relevance;
} Vacancy;

// Функция для сравнения строк (вакансий) для сортировки
int compare(const void *a, const void *b) {
    const Vacancy *vacancyA = (const Vacancy *)a;
    const Vacancy *vacancyB = (const Vacancy *)b;
    return strcmp(vacancyA->vacancy, vacancyB->vacancy);
}

// Функция для формирования списка актуальных вакансий и упорядочивания их по алфавиту
void listActualVacancies(FILE *input, FILE *output) {
    Vacancy vacancies[100];
    int numVacancies = 0;

    // Считываем данные из входного файла
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, input) != NULL) {
        sscanf(line, "%5s %99[^\n] %d %c", vacancies[numVacancies].publication_date, vacancies[numVacancies].vacancy, &vacancies[numVacancies].salary, &vacancies[numVacancies].relevance);
        if (vacancies[numVacancies].relevance == 'д') { // Проверяем актуальность вакансии
            numVacancies++;
        }
    }

    // Сортируем список актуальных вакансий по алфавиту
    qsort(vacancies, numVacancies, sizeof(Vacancy), compare);

    // Записываем результаты в выходной файл
    fprintf(output, "Вакансия\nОклад\n");
    for (int i = 0; i < numVacancies; i++) {
        fprintf(output, "%s\n%d\n", vacancies[i].vacancy, vacancies[i].salary);
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

    // Формирование списка актуальных вакансий и упорядочивание их по алфавиту
    listActualVacancies(input, output);

    // Закрытие файлов
    fclose(input);
    fclose(output);

    return 0;
}
