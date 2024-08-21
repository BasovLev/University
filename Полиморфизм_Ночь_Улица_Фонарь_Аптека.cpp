#include <iostream>
#include <cmath>

class GeomFigure {
protected:
    double x, y; 
    int color;   

public:
    GeomFigure(double ax, double ay, int acolor) : x(ax), y(ay), color(acolor) {}
    virtual ~GeomFigure() {}
    virtual void Show() = 0;  // показать объект, чисто виртуальный метод
    virtual void Hide() = 0;  // убрать объект, чисто виртуальный метод
    virtual double Perimeter() = 0; // Периметр фигуры
    virtual double Area() = 0; // Площадь фигуры
    virtual bool ContainsPoint(double px, double py) = 0; // Принадлежит ли точка внутренней области фигуры

    void Move(double nx, double ny) {
        Hide();
        std::cout << "Move (" << nx << ", " << ny << ").\n";
        x = nx;
        y = ny;
        Show();
    }
};
// Класс для точки
class Point : public GeomFigure {
public:
    Point(double x, double y, int color) : GeomFigure(x, y, color) {}
    virtual ~Point() {}
    virtual void Show() {
        std::cout << "Point at (" << x << ", " << y << ") with color " << color << " shown.\n";   // я могу поместить объект на сцену только так, с использованием сообщения
    }
    virtual void Hide() {
        std::cout << "Point at (" << x << ", " << y << ") with color " << color << " hidden.\n";
    }
    virtual double Perimeter() { return 0; }
    virtual double Area() { return 0; }
    virtual bool ContainsPoint(double px, double py) {
        return x == px && y == py;
    }
};

// Класс для окружности
class Circle : public GeomFigure {
    double radius;  // радиус окружности
public:
    Circle(double x, double y, double rad, int color) : GeomFigure(x, y, color), radius(rad) {}
    virtual ~Circle() {} //Виртуальный деструктор, помним
    virtual void Show() {
        std::cout << "Circle at (" << x << ", " << y << ") with radius " << radius << " and color " << color << " shown.\n";
    }
    virtual void Hide() {
        std::cout << "Circle at (" << x << ", " << y << ") with radius " << radius << " and color " << color << " hidden.\n";
    }
    virtual double Perimeter() { return 2 * M_PI * radius; }
    virtual double Area() { return M_PI * radius * radius; }
    virtual bool ContainsPoint(double px, double py) {
        return (pow(px - x, 2) + pow(py - y, 2)) <= pow(radius, 2);
    }
};

// Класс для эллипса
class Ellipse : public GeomFigure {
    double major_axis, minor_axis;  // оси эллипса

public:
    Ellipse(double x, double y, double major, double minor, int color) : GeomFigure(x, y, color), major_axis(major), minor_axis(minor) {}
    virtual ~Ellipse() {}
    virtual void Show() {
        std::cout << "Ellipse at (" << x << ", " << y << ") with major axis " << major_axis << " and minor axis " << minor_axis << " and color " << color << " shown.\n";
    }
    virtual void Hide() {
        std::cout << "Ellipse at (" << x << ", " << y << ") with major axis " << major_axis << " and minor axis " << minor_axis << " and color " << color << " hidden.\n";
    }
    virtual double Perimeter() {
        // Формула из интернета, т.к. точной формулы периметра эллипса нет
        return M_PI * sqrt(2 * (major_axis * major_axis + minor_axis * minor_axis));
    }
    virtual double Area() { return M_PI * major_axis * minor_axis; }
    virtual bool ContainsPoint(double px, double py) { return (pow(px - x, 2) / pow(major_axis, 2)) + (pow(py - y, 2) / pow(minor_axis, 2)) <= 1; }
};

// Класс для отрезка прямой
class LineSegment : public GeomFigure {
    double x2, y2; 

public:
    LineSegment(double x1, double y1, double x2, double y2, int color) : GeomFigure(x1, y1, color), x2(x2), y2(y2) {}
    virtual ~LineSegment() {}
    virtual void Show() {
        std::cout << "Line segment from (" << x << ", " << y << ") to (" << x2 << ", " << y2 << ") with color " << color << " shown.\n";
    }
    virtual void Hide() {
        std::cout << "Line segment from (" << x << ", " << y << ") to (" << x2 << ", " << y2 << ") with color " << color << " hidden.\n";
    }
    virtual double Perimeter() { return sqrt(pow(x2 - x, 2) + pow(y2 - y, 2)); }
    virtual double Area() { return 0; }

    virtual bool ContainsPoint(double px, double py) {
        return false;    // Т.к. у отрезка нет площади
    }
};

// Класс для ломаной
class Polyline : public GeomFigure {
protected:
    struct Vertex {
        double dx, dy;
        Vertex* next;
    };
    Vertex* first;
public:
    Polyline(double x, double y, int color) : GeomFigure(x, y, color), first(nullptr) {}
    virtual ~Polyline() {
        while (first) {
            Vertex* temp = first;
            first = first->next;
            delete temp;
        }
    }
    void AddVertex(double adx, double ady) {
        Vertex* temp = new Vertex;
        temp->dx = adx;
        temp->dy = ady;
        temp->next = first;
        first = temp;
    }

    virtual void Show() {
        std::cout << "Polyline:\n";
        Vertex* c = first;
        while (c) {
            std::cout << "  (" << x + c->dx << ", " << y + c->dy << ")\n";
            c = c->next;
        }
        std::cout << "and color " << color << " shown.\n";
    }

    virtual void Hide() {
        std::cout << "Polyline hidden.\n";
    }

    virtual double Perimeter() {
        double length = 0;
        Vertex* c = first;
        Vertex* next = first ? first->next : nullptr;
        while (next) {
            length += sqrt(pow(next->dx - c->dx, 2) + pow(next->dy - c->dy, 2));
            c = next;
            next = next->next;
        }
        return length;
    }
    virtual double Area() { return 0; }
    virtual bool ContainsPoint(double px, double py) {
        return false; // Т.к. ломаная не имеет внутренней области
    }
};

// Класс для квадрата
class Square : public Polyline {
public:
    Square(double x, double y, int color, double a) : Polyline(x, y, color) {
        AddVertex(0, 0);
        AddVertex(a, 0);
        AddVertex(a, a);
        AddVertex(0, a);
        AddVertex(0, 0);
    }

    virtual double Area() {
        Vertex* current = first;
        if (current && current->next && current->next->next) {
            double side_length = sqrt(pow(current->next->dx - current->dx, 2) + pow(current->next->dy - current->dy, 2));
            return side_length * side_length;
        }
        return 0;
    }

    virtual bool ContainsPoint(double px, double py) {
        Vertex* current = first;
        if (current && current->next && current->next->next) {
            double x0 = x + current->dx;
            double y0 = y + current->dy;
            double x1 = x + current->next->dx;
            double y1 = y + current->next->dy;
            double x2 = x + current->next->next->dx;
            double y2 = y + current->next->next->dy;

            return (px >= x0 && px <= x1 && py >= y0 && py <= y2);
        }
        return false;
    }
};

// Класс для треугольника
class Triangle : public Polyline {
public:
    Triangle(double x, double y, int color, double a, double b, double c) : Polyline(x, y, color) {
        AddVertex(0, 0);
        AddVertex(a, 0);
        AddVertex(b, c);
        AddVertex(0, 0);
    }

    virtual double Area() {
        Vertex* v1 = first;
        Vertex* v2 = first ? first->next : nullptr;
        Vertex* v3 = v2 ? v2->next : nullptr;

        if (v1 && v2 && v3) {
            double x1 = x + v1->dx, y1 = y + v1->dy;
            double x2 = x + v2->dx, y2 = y + v2->dy;
            double x3 = x + v3->dx, y3 = y + v3->dy;
            return fabs((x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2)) / 2.0);
        }
        return 0;
    }

    virtual bool ContainsPoint(double px, double py) {
        Vertex* v1 = first;
        Vertex* v2 = first ? first->next : nullptr;
        Vertex* v3 = v2 ? v2->next : nullptr;

        if (v1 && v2 && v3) {
            double x1 = x + v1->dx, y1 = y + v1->dy;
            double x2 = x + v2->dx, y2 = y + v2->dy;
            double x3 = x + v3->dx, y3 = y + v3->dy;

            double A = Area();

            double A1 = fabs((px*(y2 - y3) + x2*(y3 - py) + x3*(py - y2)) / 2.0);
            double A2 = fabs((x1*(py - y3) + px*(y3 - y1) + x3*(y1 - py)) / 2.0);
            double A3 = fabs((x1*(y2 - py) + x2*(py - y1) + px*(y1 - y2)) / 2.0);

            return (A == A1 + A2 + A3);
        }
        return false;
    }
};

// Класс для прямоугольника
class Rectangle : public Polyline {
public:
    Rectangle(double x, double y, int color, double width, double height) : Polyline(x, y, color) {
        AddVertex(0, 0);
        AddVertex(width, 0);
        AddVertex(width, height);
        AddVertex(0, height);
        AddVertex(0, 0);
    }

    virtual double Area() {
        Vertex* v1 = first;
        Vertex* v2 = first ? first->next : nullptr;

        if (v1 && v2) {
            double width = sqrt(pow(v2->dx - v1->dx, 2) + pow(v2->dy - v1->dy, 2));
            double height = sqrt(pow(v2->next->dx - v2->dx, 2) + pow(v2->next->dy - v2->dy, 2));
            return width * height;
        }
        return 0;
    }

    virtual bool ContainsPoint(double px, double py) {
        Vertex* v1 = first;
        Vertex* v2 = first ? first->next : nullptr;
        Vertex* v3 = v2 ? v2->next : nullptr;

        if (v1 && v2 && v3) {
            double x1 = x + v1->dx;
            double y1 = y + v1->dy;
            double x3 = x + v3->dx;
            double y3 = y + v3->dy;

            return (px >= x1 && px <= x3 && py >= y1 && py <= y3);
        }
        return false;
    }
};

// Класс для ромба
class Rhomb : public Polyline {
public:
    Rhomb(double x, double y, int color, double diag1, double diag2) : Polyline(x, y, color) {
        AddVertex(0, 0);
        AddVertex(diag1 / 2, diag2 / 2);
        AddVertex(0, diag2);
        AddVertex(-diag1 / 2, diag2 / 2);
        AddVertex(0, 0);
    }

    virtual double Area() {
        return (first->next->dx * first->next->dy) / 2;
    }

    virtual bool ContainsPoint(double px, double py) {
        double dx1 = first->next->dx;
        double dy1 = first->next->dy;
        double dx2 = first->next->next->dx;
        double dy2 = first->next->next->dy;

        double x1 = x + dx1;
        double y1 = y + dy1;
        double x2 = x + dx2;
        double y2 = y + dy2;

        double crossProduct = (px - x1) * (y2 - y1) - (py - y1) * (x2 - x1);
        if (crossProduct < 0) return false;

        crossProduct = (px - x2) * (y1 - y2) - (py - y2) * (x1 - x2);
        return crossProduct >= 0;
    }
};

int main() {
    Point point(1, 2, 0xFF0000);
    Circle circle(0, 0, 5, 0x00FF00);
    Ellipse ellipse(0, 0, 5, 3, 0x0000FF);
    LineSegment line(0, 0, 3, 4, 0xFFFF00);
    Polyline polyline(0, 0, 0xFF00FF);
    polyline.AddVertex(0, 0);
    polyline.AddVertex(3, 4);
    polyline.AddVertex(6, 8);
    Square square(0, 0, 0x00FFFF, 4);
    Triangle triangle(0, 0, 0xFF0000, 3, 4, 5);
    Rectangle rectangle(0, 0, 0x00FF00, 3, 4);
    Rhomb rhomb(0, 0, 0x0000FF, 4, 6);
    GeomFigure* figures[] = { &point, &circle, &ellipse, &line, &polyline, &square, &triangle, &rectangle, &rhomb };

    for (GeomFigure* figure : figures) {
        figure->Show();
        figure->Move(3, 9);
        std::cout << "Perimeter: " << figure->Perimeter() << "\n";
        std::cout << "Area: " << figure->Area() << "\n";
        std::cout << "Contains point: " << (figure->ContainsPoint(5, 5) ? "Yes" : "No") << "\n";
        figure->Hide();                       // Проверка для всех фигур
    }

    return 0;
}
