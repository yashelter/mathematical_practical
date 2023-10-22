#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

bool isConvexPolygon(int n, ...) {
    double eps = 1e-8;
    va_list points;
    va_start(points, n);
    if (n < 3) { return false; }

    double x_, y_;
    double x1 = va_arg(points, double);
    double y1 = va_arg(points, double);

    x_ = x1; y_=y1;
    double x2, y2;
    double pref_square = 0;
    double first_no_zero = 0;
    for(int i = 1; i <= n; i++) 
    {

        x2 = va_arg(points, double);
        y2 = va_arg(points, double);
        double areaSign = x1 * y2 - x2 * y1;

        if (i == 1) pref_square = areaSign;
        if (first_no_zero == 0 && areaSign != 0 ) { first_no_zero = areaSign;}

        // printf("area %.20f\n", areaSign);
        if (first_no_zero * areaSign < 0 && first_no_zero * (areaSign + eps) > 0) {areaSign += eps;}
        if (pref_square * areaSign < 0 && pref_square * (areaSign + eps) > 0) {areaSign += eps;}

        if(areaSign * pref_square < 0 || first_no_zero * areaSign < 0) 
        {
            va_end(points);
            return false;
        }

        x1 = x2; y1 = y2;
    }
    double areaSign = x1 * y_ - x_ * y1;

    if(areaSign * pref_square < 0) 
    {
        va_end(points);
        return false;
    }
    
    va_end(points);
    return true;
}

double polynomialValue(double x, int n, ...) {
    va_list coefficients;
    va_start(coefficients, n);

    double result = 0;
    for(int i = 0; i < n; i++) 
    {
        result *= x;

        double coeff = va_arg(coefficients, double);
        result += coeff;
    }

    va_end(coefficients);
    return result;
}

int main() 
{

    printf("Is Convex: %d\n", isConvexPolygon(4, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0, 1)); // Должно быть 1 (выпуклый квадрат)

    printf("Polynomial Value: %lf\n", polynomialValue(2, 1, 2.0, -3, 2)); // 2 ( x^2 - 3x + 2 в точке x=2)

    return 0;
}