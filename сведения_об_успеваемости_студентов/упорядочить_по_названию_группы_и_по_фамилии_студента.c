#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Структура для хранения информации об успеваемости студентов
typedef struct {
    char student[50];
    char group[5];
    char discipline[50];
    int grades[10];
    int numGrades;
} StudentRecord;

// Структура для хранения информации о любимой дисциплине студента
typedef struct {
    char student[50];
    char group[5];
    char discipline[50];
    float averageGrade;
} FavoriteDiscipline;

// Функция для сравнения студентов (для сортировки)
int compareStudents(const void *a, const void *b) {
    const FavoriteDiscipline *pa = (const FavoriteDiscipline *)a;
    const FavoriteDiscipline *pb = (const FavoriteDiscipline *)b;
    int cmp = strcmp(pa->group, pb->group);
    if (cmp == 0) {
        return strcmp(pa->student, pb->student);
    }
    return cmp;
}

// Функция для определения любимой дисциплины студента и среднего балла
void determineFavoriteDiscipline(StudentRecord *records, int numRecords, FILE *output) {
    // Создаем массив для хранения информации о любимой дисциплине каждого студента
    FavoriteDiscipline favorites[100];
    int numFavorites = 0;

    // Проходим по всем записям об успеваемости студентов
    for (int i = 0; i < numRecords; i++) {
        // Вычисляем средний балл студента по текущей дисциплине
        float sum = 0;
        for (int j = 0; j < records[i].numGrades; j++) {
            sum += records[i].grades[j];
        }
        float average = sum / records[i].numGrades;

        // Ищем максимальный балл среди всех дисциплин студента
        float maxGrade = 0;
        char favoriteDiscipline[50] = "";
        for (int j = 0; j < numRecords; j++) {
            if (strcmp(records[i].student, records[j].student) == 0) {
                float disciplineSum = 0;
                for (int k = 0; k < records[j].numGrades; k++) {
                    disciplineSum += records[j].grades[k];
                }
                float disciplineAverage = disciplineSum / records[j].numGrades;
                if (disciplineAverage > maxGrade) {
                    maxGrade = disciplineAverage;
                    strcpy(favoriteDiscipline, records[j].discipline);
                }
            }
        }

        // Добавляем информацию о любимой дисциплине в массив favorites
        strcpy(favorites[numFavorites].student, records[i].student);
        strcpy(favorites[numFavorites].group, records[i].group);
        strcpy(favorites[numFavorites].discipline, favoriteDiscipline);
        favorites[numFavorites].averageGrade = average;
        numFavorites++;
    }

    // Сортируем список по группе и фамилии студента
    qsort(favorites, numFavorites, sizeof(FavoriteDiscipline), compareStudents);

    // Записываем результаты в выходной файл
    fprintf(output, "Структура выходного файла out.txt\n");
    for (int i = 0; i < numFavorites; i++) {
        fprintf(output, "%s %s %s\n", favorites[i].group, favorites[i].student, favorites[i].discipline);
    }
}

int main() {
    FILE *input, *output;

    // Открываем входной файл
    input = fopen("in.txt", "r");
    if (input == NULL) {
        printf("Cannot open input file.\n");
        return 1;
    }

    // Открываем выходной файл
    output = fopen("out.txt", "w");
    if (output == NULL) {
        printf("Cannot open output file.\n");
        fclose(input);
        return 1;
    }

    // Читаем данные из входного файла
    StudentRecord records[100];
    int numRecords = 0;
    while (fscanf(input, "%[^;]; %[^;]; %[^;]; %d %d %d %d %d %d %d %d",
                  records[numRecords].student, records[numRecords].group,
                  records[numRecords].discipline, &records[numRecords].grades[0],
                  &records[numRecords].grades[1], &records[numRecords].grades[2],
                  &records[numRecords].grades[3], &records[numRecords].grades[4],
                  &records[numRecords].grades[5], &records[numRecords].grades[6],
                  &records[numRecords].numGrades) == 11) {
        numRecords++;
    }

    // Определяем любимые дисциплины студентов и средние баллы
    determineFavoriteDiscipline(records, numRecords, output);

    // Закрываем файлы
    fclose(input);
    fclose(output);

    return 0;
}
