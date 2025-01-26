#include <iostream>
#include <cmath>

struct Point {
    int x;
    int y;
};

enum Colour {
    RED,
    GREEN,
    BLUE,
    NONE
};

class Shape
{
public:
    Point center;
    Colour colour;
};

class Circle : public Shape
{

public:
    Circle(Point p, Colour c, double radius){
        this->center = p;
        this->radius = radius;
        this->colour = c;
    }

public:

    double radius;

    double square() {
        return 3.141 * (radius * radius);
    }

    double squareOfBoundSquare() {
        return 4 * (radius * radius) + 1;
    }

};

class Square : public Shape
{
public:

    Square(){} // В производных классах возникла проблема с отсутствием дефолтного класса
    // IDE предложила какое то странное решение, в итоге я решил просто перегрузить конструктор и вроде как это работает
    // P.S. Я стараюсь избегать костылей, но тут никак без них :)


    Square(Point p, Colour c, double length) : Shape() {
        this->center = p;
        this->colour = c;
        this->length = length;
    }

    double square() {
        return length * width;
    }

    double squareOfBoundSquare() {
        return length * width + 1;
    }

public:
    double length;
    double width = length;

};

class PerfectTriangle : public Square
{
public:
    PerfectTriangle(Point p, Colour c, double length){
        this->center = p;
        this->colour = c;
        this->length = length;
    }

    double square() {
        return (pow(length, 2) * pow(3, (1.0/2.0))) / 4;
    }
};

class Rectangle : public Square
{
public:
    Rectangle(Point p, Colour c, double length, double width) {
        this->center = p;
        this->colour = c;
        this->length = length;
        this->width = width;
    }
};

int main() {

    std::cout << "Type exit to exit" << std::endl;
    std::cout << "List of commands:\ncircle\nsquare\ntriangle\nrectangle" << std::endl;

    while(true) {
        std::string command;
        std::cin >> command;

        if(command == "exit") {
            break;
        } else if(command == "circle") {
            Point p;
            double radius;
            std::cout << "Type in cordinates of circle centre: (x y)" << std::endl;
            std::cin >> p.x >> p.y;
            std::cout << "Type in the radius of the circle:" << std::endl;
            std::cin >> radius;
            Circle* c = new Circle(p, RED, radius);
            std::cout << "Square of the circle: " << c->square() << std::endl;
            std::cout << "Square of the bound square: " << c->squareOfBoundSquare() << std::endl;
        } else if(command == "square") {
            Point p;
            double length;
            std::cout << "Type in cordinates of square centre: (x y)" << std::endl;
            std::cin >> p.x >> p.y;
            std::cout << "Type in the length of the square:" << std::endl;
            std::cin >> length;
            Square* s = new Square(p, RED, length);
            std::cout << "Square of the square: " << s->square() << std::endl;
            std::cout << "Square of the bound square: " << s->squareOfBoundSquare() << std::endl;
        } else if(command == "triangle") {
            Point p;
            double length;
            std::cout << "Type in cordinates of triangle centre: (x y)" << std::endl;
            std::cin >> p.x >> p.y;
            std::cout << "Type in the length of the triangle:" << std::endl;
            std::cin >> length;
            PerfectTriangle* t = new PerfectTriangle(p, RED, length);
            std::cout << "Square of the triangle: " << t->square() << std::endl;
            std::cout << "Square of the bound square: " << t->squareOfBoundSquare() << std::endl;
        } else if(command == "rectangle") {
            Point p;
            double length, width;
            std::cout << "Type in cordinates of rectangle centre: (x y)" << std::endl;
            std::cin >> p.x >> p.y;
            std::cout << "Type in the length of the rectangle:" << std::endl;
            std::cin >> length;
            std::cout << "Type in the width of the rectangle:" << std::endl;
            std::cin >> width;
            Rectangle* r = new Rectangle(p, RED, length, width);
            std::cout << "Square of the rectangle: " << r->square() << std::endl;
            std::cout << "Square of the bound square: " << r->squareOfBoundSquare() << std::endl;
        } else {
            std::cout << "Unknown command" << std::endl;
        }
    }
    return 0;
}