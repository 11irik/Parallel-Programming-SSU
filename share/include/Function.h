#ifndef FUNCTION_H
#define FUNCTION_H

double calcRow(double x);

void calcRowWrap(double &i);

double calcTwiceRow(double x, double y, int n);

struct Point {
    double x;
    double y;
    double f;

    Point(double _x, double _y, double _f) {
        x = _x;
        y = _y;
        f = _f;
    }
};

#endif