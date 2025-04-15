#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// Структура для представления точки на плоскости
struct Point {
    double x, y;
};

// Функция для вычисления расстояния между двумя точками
double distance(Point a, Point b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

// Функция для вычисления угла между двумя векторами (в радианах)
double angle(Point a, Point b, Point c) {
    double ab_x = b.x - a.x;
    double ab_y = b.y - a.y;
    double cb_x = b.x - c.x;
    double cb_y = b.y - c.y;

    double dot_product = ab_x * cb_x + ab_y * cb_y;
    double magnitude_ab = sqrt(ab_x * ab_x + ab_y * ab_y);
    double magnitude_cb = sqrt(cb_x * cb_x + cb_y * cb_y);

    return acos(dot_product / (magnitude_ab * magnitude_cb));
}

// Функция для определения, параллельны ли две прямые, заданные двумя точками на каждой прямой
bool areParallel(Point a, Point b, Point c, Point d) {
    return abs((b.y - a.y) * (d.x - c.x) - (d.y - c.y) * (b.x - a.x)) < 1e-6; // Используем небольшую погрешность
}

// Функция для определения, перпендикулярны ли две прямые, заданные двумя точками на каждой прямой
bool arePerpendicular(Point a, Point b, Point c, Point d) {
    return abs((b.x - a.x) * (d.x - c.x) + (b.y - a.y) * (d.y - c.y)) < 1e-6; // Используем небольшую погрешность
}

// Функция для определения вида четырехугольника
string determineQuadrangleType(vector<Point> vertices) {
    if (vertices.size() != 4) {
        return "Не является четырехугольником";
    }

    // Сортируем вершины по часовой стрелке (важно для дальнейших проверок)
    // (код сортировки может быть сложным, опустим его для краткости)
    // Предполагаем, что вершины уже отсортированы по часовой стрелке!

    // Вычисляем длины сторон
    double side1 = distance(vertices[0], vertices[1]);
    double side2 = distance(vertices[1], vertices[2]);
    double side3 = distance(vertices[2], vertices[3]);
    double side4 = distance(vertices[3], vertices[0]);

    // Вычисляем диагонали
    double diagonal1 = distance(vertices[0], vertices[2]);
    double diagonal2 = distance(vertices[1], vertices[3]);

    // Проверяем на параллельность сторон
    bool oppositeSidesParallel1 = areParallel(vertices[0], vertices[1], vertices[2], vertices[3]);
    bool oppositeSidesParallel2 = areParallel(vertices[1], vertices[2], vertices[3], vertices[0]);

    // Проверяем на перпендикулярность сторон
    bool hasRightAngle = arePerpendicular(vertices[0], vertices[1], vertices[1], vertices[2]) ||
        arePerpendicular(vertices[1], vertices[2], vertices[2], vertices[3]) ||
        arePerpendicular(vertices[2], vertices[3], vertices[3], vertices[0]) ||
        arePerpendicular(vertices[3], vertices[0], vertices[0], vertices[1]);


    if (oppositeSidesParallel1 && oppositeSidesParallel2) { // Параллелограмм, ромб, прямоугольник, квадрат
        if (side1 == side2 && side2 == side3 && side3 == side4) { // Ромб или квадрат
            if (hasRightAngle) {
                return "Квадрат";
            }
            else {
                return "Ромб";
            }
        }
        else { // Параллелограмм или прямоугольник
            if (hasRightAngle) {
                return "Прямоугольник";
            }
            else {
                return "Параллелограмм";
            }
        }
    }
    else if (oppositeSidesParallel1 || oppositeSidesParallel2) { // Трапеция
        bool isIsoscelesTrapezoid = false;
        bool isRightTrapezoid = false;
        if (oppositeSidesParallel1) { // vertices[0]-vertices[1] || vertices[2]-vertices[3]
            isIsoscelesTrapezoid = abs(side2 - side4) < 1e-6 && (diagonal1 == diagonal2);
            isRightTrapezoid = arePerpendicular(vertices[0], vertices[1], vertices[1], vertices[2]) ||
                arePerpendicular(vertices[2], vertices[3], vertices[1], vertices[2]);
        }
        else { // vertices[1]-vertices[2] || vertices[3]-vertices[0]
            isIsoscelesTrapezoid = abs(side1 - side3) < 1e-6 && (diagonal1 == diagonal2);
            isRightTrapezoid = arePerpendicular(vertices[1], vertices[2], vertices[0], vertices[1]) ||
                arePerpendicular(vertices[3], vertices[0], vertices[0], vertices[1]);
        }

        if (isIsoscelesTrapezoid) return "Равнобедренная трапеция";
        if (isRightTrapezoid) return "Прямоугольная трапеция";
        return "Трапеция общего вида";
    }
    else {
        return "Четырехугольник общего вида";
    }
}

int main() {
    vector<Point> vertices(4);

    cout << "Введите координаты вершин четырехугольника (x y):" << endl;
    for (int i = 0; i < 4; ++i) {
        cout << "Вершина " << i + 1 << ": ";
        cin >> vertices[i].x >> vertices[i].y;
    }

    string quadrangleType = determineQuadrangleType(vertices);
    cout << "Тип четырехугольника: " << quadrangleType << endl;

    return 0;
}
