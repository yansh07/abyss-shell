#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *expr;

float parseExpression();
float parseTerm();
float parseFactor();

float parseFactor() {
    float num = 0;

    while (*expr == ' ')
        expr++;

    if (isdigit(*expr)) {
        num = strtof(expr, &expr);
    }

    return num;
}

float parseTerm() {
    float result = parseFactor();

    while (1) {

        while (*expr == ' ')
            expr++;

        if (*expr == '*') {
            expr++;
            result *= parseFactor();
        }

        else if (*expr == '/') {
            expr++;

            float divisor = parseFactor();

            if (divisor == 0) {
                printf("Error: divide by zero!\n");
                return 0;
            }

            result /= divisor;
        }

        else if (*expr == '%') {
            expr++;

            int a = (int)result;
            int b = (int)parseFactor();

            if (b == 0) {
                printf("Modulo by zero!\n");
                return 0;
            }

            result = a % b;
        }

        else {
            break;
        }
    }

    return result;
}

float parseExpression() {

    float result = parseTerm();

    while (1) {

        while (*expr == ' ')
            expr++;

        if (*expr == '+') {
            expr++;
            result += parseTerm();
        }

        else if (*expr == '-') {
            expr++;
            result -= parseTerm();
        }

        else {
            break;
        }
    }

    return result;
}

int main() {

    char input[100];

    while (1) {

        printf("\nEnter expression (or q to quit): ");

        fgets(input, sizeof(input), stdin);

        if (input[0] == 'q')
            break;

        expr = input;

        float result = parseExpression();

        printf("Result = %.2f\n", result);
    }

    return 0;
}