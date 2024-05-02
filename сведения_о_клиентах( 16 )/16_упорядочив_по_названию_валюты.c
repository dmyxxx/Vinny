#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 200
#define MAX_CURRENCY_LENGTH 100

// Структура для хранения информации о сделке
typedef struct {
    char currency[MAX_CURRENCY_LENGTH];
    int rate;
    int amount;
} Transaction;

// Функция для сравнения строк (валют) для сортировки
int compare(const void *a, const void *b) {
    const Transaction *transactionA = (const Transaction *)a;
    const Transaction *transactionB = (const Transaction *)b;
    return strcmp(transactionA->currency, transactionB->currency);
}

// Функция для подсчета суммы в рублях по каждой валюте
void calculateAmountsInRubles(FILE *input, FILE *output) {
    Transaction transactions[100];
    int numTransactions = 0;

    // Считываем данные из входного файла
    while (fscanf(input, "%s %s %d %d", transactions[numTransactions].currency, transactions[numTransactions].currency, &transactions[numTransactions].rate, &transactions[numTransactions].amount) != EOF) {
        numTransactions++;
    }

    // Создаем хэш-таблицу для подсчета суммы в рублях по каждой валюте
    int currencyAmounts[100] = {0}; // Массив для хранения суммы в рублях по каждой валюте
    char uniqueCurrencies[100][MAX_CURRENCY_LENGTH]; // Массив для хранения уникальных валют
    int numUniqueCurrencies = 0;

    // Проходим по всем сделкам и суммируем сумму в рублях по каждой валюте
    for (int i = 0; i < numTransactions; i++) {
        int isNewCurrency = 1;
        for (int j = 0; j < numUniqueCurrencies; j++) {
            if (strcmp(transactions[i].currency, uniqueCurrencies[j]) == 0) {
                currencyAmounts[j] += transactions[i].rate * transactions[i].amount;
                isNewCurrency = 0;
                break;
            }
        }
        if (isNewCurrency) {
            strcpy(uniqueCurrencies[numUniqueCurrencies], transactions[i].currency);
            currencyAmounts[numUniqueCurrencies] = transactions[i].rate * transactions[i].amount;
            numUniqueCurrencies++;
        }
    }

    // Сортируем список по названию валюты
    for (int i = 0; i < numUniqueCurrencies - 1; i++) {
        for (int j = i + 1; j < numUniqueCurrencies; j++) {
            if (strcmp(uniqueCurrencies[i], uniqueCurrencies[j]) > 0) {
                int tempAmount = currencyAmounts[i];
                currencyAmounts[i] = currencyAmounts[j];
                currencyAmounts[j] = tempAmount;

                char tempCurrency[MAX_CURRENCY_LENGTH];
                strcpy(tempCurrency, uniqueCurrencies[i]);
                strcpy(uniqueCurrencies[i], uniqueCurrencies[j]);
                strcpy(uniqueCurrencies[j], tempCurrency);
            }
        }
    }

    // Записываем результаты в выходной файл
    fprintf(output, "Валюта Сумма в рублях\n");
    for (int i = 0; i < numUniqueCurrencies; i++) {
        fprintf(output, "%s %d\n", uniqueCurrencies[i], currencyAmounts[i]);
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

    // Подсчет суммы в рублях по каждой валюте
    calculateAmountsInRubles(input, output);

    // Закрытие файлов
    fclose(input);
    fclose(output);

    return 0;
}
