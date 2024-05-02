#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

// Структура для хранения информации о статье затрат
typedef struct {
    int code;
    int total_cost;
} CostArticle;

// Функция для сравнения статей затрат (для сортировки)
int compare(const void *a, const void *b) {
    const CostArticle *articleA = (const CostArticle *)a;
    const CostArticle *articleB = (const CostArticle *)b;
    return articleA->code - articleB->code;
}

// Функция для формирования списка суммарной себестоимости по каждой статье затрат
void listTotalCostByArticle(FILE *input, FILE *output) {
    CostArticle cost_articles[100] = {0}; // Инициализация массива для хранения суммарной себестоимости
    int num_articles = 0;

    // Считываем данные из входного файла
    int code;
    char item[MAX_LINE_LENGTH];
    int cost_per_unit, plan, total_cost;
    while (fscanf(input, "%d %s %d %d", &code, item, &cost_per_unit, &plan) == 4) {
        // Проверяем, существует ли уже информация о данной статье затрат
        int exists = 0;
        for (int i = 0; i < num_articles; ++i) {
            if (cost_articles[i].code == code) {
                exists = 1;
                break;
            }
        }

        // Если статья затрат уже есть в списке, увеличиваем суммарную себестоимость
        if (exists) {
            for (int i = 0; i < num_articles; ++i) {
                if (cost_articles[i].code == code) {
                    total_cost = cost_per_unit * plan;
                    cost_articles[i].total_cost += total_cost;
                    break;
                }
            }
        } else { // Если статьи затрат нет в списке, добавляем ее
            total_cost = cost_per_unit * plan;
            cost_articles[num_articles].code = code;
            cost_articles[num_articles].total_cost = total_cost;
            num_articles++;
        }
    }

    // Сортируем список по номеру статьи затрат
    qsort(cost_articles, num_articles, sizeof(CostArticle), compare);

    // Записываем результаты в выходной файл
    fprintf(output, "Шифр статьи затрат Себестоимость (условных единиц)\n");
    for (int i = 0; i < num_articles; ++i) {
        fprintf(output, "%d %d\n", cost_articles[i].code, cost_articles[i].total_cost);
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

    // Формирование списка суммарной себестоимости по каждой статье затрат
    listTotalCostByArticle(input, output);

    // Закрытие файлов
    fclose(input);
    fclose(output);

    return 0;
}
