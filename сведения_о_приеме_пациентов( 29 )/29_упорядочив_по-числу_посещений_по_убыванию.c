#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Структура для хранения информации о приеме пациентов
typedef struct {
    char doctor[50];
    char patient[50];
    char date[11];
    char time[6];
    char diagnosis[3];
} Appointment;

// Структура для хранения информации о пациенте и числе его посещений
typedef struct {
    char patient[50];
    int visits;
} PatientVisits;

// Функция для сравнения пациентов по числу посещений (для сортировки)
int compare(const void *a, const void *b) {
    const PatientVisits *pa = (const PatientVisits *)a;
    const PatientVisits *pb = (const PatientVisits *)b;
    return pb->visits - pa->visits;
}

// Функция для формирования списка пациентов, побывавших у врача более одного раза
void generatePatientVisits(Appointment *appointments, int numAppointments, FILE *output) {
    // Создаем массив для хранения информации о пациентах и их посещениях
    PatientVisits patients[100] = {0};
    int numPatients = 0;

    // Проходим по всем приемам пациентов и считаем количество посещений каждого пациента
    for (int i = 0; i < numAppointments; i++) {
        int found = 0;
        // Проверяем, есть ли уже информация о данном пациенте в массиве
        for (int j = 0; j < numPatients; j++) {
            if (strcmp(patients[j].patient, appointments[i].patient) == 0) {
                patients[j].visits++;
                found = 1;
                break;
            }
        }
        // Если информация о пациенте не найдена, добавляем его в массив
        if (!found) {
            strcpy(patients[numPatients].patient, appointments[i].patient);
            patients[numPatients].visits = 1;
            numPatients++;
        }
    }

    // Сортируем список пациентов по числу посещений
    qsort(patients, numPatients, sizeof(PatientVisits), compare);

    // Записываем результаты в выходной файл
    fprintf(output, "Структура выходного файла out.txt\n");
    for (int i = 0; i < numPatients; i++) {
        if (patients[i].visits > 1) {
            fprintf(output, "%s %d\n", patients[i].patient, patients[i].visits);
        }
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
    Appointment appointments[100];
    int numAppointments = 0;
    while (fscanf(input, "%s %s %s %s %s %s", appointments[numAppointments].doctor,
                  appointments[numAppointments].patient, appointments[numAppointments].date,
                  appointments[numAppointments].time, appointments[numAppointments].diagnosis) == 5) {
        numAppointments++;
    }

    // Формируем список пациентов, побывавших у врача более одного раза
    generatePatientVisits(appointments, numAppointments, output);

    // Закрываем файлы
    fclose(input);
    fclose(output);

    return 0;
}
