#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

// Структура для хранения информации о проживающих и услугах
typedef struct {
    char account[MAX_LINE_LENGTH];
    char lastname[MAX_LINE_LENGTH];
    char street[MAX_LINE_LENGTH];
    int house;
    int flat;
    char service[MAX_LINE_LENGTH];
    int price;
    int quantity;
} PaymentRequest;

// Функция для сравнения требований на оплату по адресу (для сортировки)
int compare(const void *a, const void *b) {
    const PaymentRequest *reqA = (const PaymentRequest *)a;
    const PaymentRequest *reqB = (const PaymentRequest *)b;
    int streetComparison = strcmp(reqA->street, reqB->street);
    if (streetComparison != 0) return streetComparison;
    return reqA->house - reqB->house;
}

// Функция для формирования требований на оплату
void generatePaymentRequests(FILE *input, FILE *output) {
    PaymentRequest requests[100] = {0}; // Инициализация массива для хранения требований на оплату
    int num_requests = 0;

    // Считываем данные из входного файла
    while (fscanf(input, "%s %s %s %d %d %s %d %d", requests[num_requests].account, requests[num_requests].lastname,
                  requests[num_requests].street, &requests[num_requests].house, &requests[num_requests].flat,
                  requests[num_requests].service, &requests[num_requests].price, &requests[num_requests].quantity) == 8) {
        num_requests++;
    }

    // Сортируем список требований на оплату по адресу
    qsort(requests, num_requests, sizeof(PaymentRequest), compare);

    // Записываем результаты в выходной файл
    fprintf(output, "Структура выходного файла out.txt\n");
    for (int i = 0; i < num_requests;) {
        // Начинаем запись для нового адреса
        fprintf(output, "%s %s, ул. %s, %d, кв. %d\n", requests[i].account, requests[i].lastname, requests[i].street,
                requests[i].house, requests[i].flat);
        int total = 0;

        // Суммируем стоимость для каждой услуги для данного адреса
        while (i < num_requests && strcmp(requests[i].street, requests[i - 1].street) == 0 &&
               requests[i].house == requests[i - 1].house) {
            int cost = requests[i].price * requests[i].quantity;
            fprintf(output, "%s %d * %d = %d\n", requests[i].service, requests[i].price, requests[i].quantity, cost);
            total += cost;
            i++;
        }

        // Записываем общую стоимость для данного адреса
        fprintf(output, "Итого %d\n", total);
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

    // Формирование требований на оплату
    generatePaymentRequests(input, output);

    // Закрытие файлов
    fclose(input);
    fclose(output);

    return 0;
}
