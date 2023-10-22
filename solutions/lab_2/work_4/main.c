#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

bool isConvexPolygon(int n, ...) {
    va_list points;
    va_start(points, n);
    double x1 = va_arg(points, double);
    double y1 = va_arg(points, double);
    double x2 = va_arg(points, double);
    double y2 = va_arg(points, double);
    double prevAreaSign = 0;

    for(int i = 2; i <= n; i++) {
        double x3 = va_arg(points, double);
        double y3 = va_arg(points, double);

        double areaSign = x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2);
        if(i == 2) prevAreaSign = areaSign;

        if(areaSign * prevAreaSign < 0) {
            va_end(points);
            return false;
        }

        x1 = x2; y1 = y2;
        x2 = x3; y2 = y3;
    }

    va_end(points);
    return true;
}

double polynomialValue(double x, int n, ...) {
    va_list coefficients;
    va_start(coefficients, n);

    double result = 0;
    for(int i = n; i >= 0; i--) {
        double coeff = va_arg(coefficients, double);
        double value = 1;
        for(int j = 0; j < i; j++) value *= x;
        result += coeff * value;
    }

    va_end(coefficients);
    return result;
}

int main() {
    // Тест для первой функции
    printf("Is Convex: %d\n", isConvexPolygon(4, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0)); // Должно быть 1 (выпуклый квадрат)

    // Тест для второй функции
    printf("Polynomial Value: %lf\n", polynomialValue(2, 2, 1.0, -3.0, 2.0)); // Должно быть 2 (многочлен x^2 - 3x + 2 в точке x=2)

    return 0;
}