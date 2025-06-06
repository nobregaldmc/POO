#include <iostream>
#include <sstream>
#include <vector>
#include <memory>
#include <cmath>
#include <iomanip>
using namespace std;

template <typename CONTAINER, typename FUNC>
auto map_join(const CONTAINER& c, FUNC f, const string& sep = ", ") {
    stringstream ss;
    for (auto it = c.begin(); it != c.end(); ++it) {
        ss << (it != c.begin() ? sep : "");
        ss << f(*it);
    }
    return ss.str();
}

class Point2D{
    private:

    public:
        double x;
        double y;

        Point2D(double x = 0, double y = 0): x(x), y(y){

        }

        Point2D(string serial){
            stringstream ss(serial);
            char c;
            ss >> c >> x >> c >> y >> c;
        }

        string toString()const{
            ostringstream oss;
            oss << fixed << setprecision(2) << "(" << x << ", " << y << ")";
            return oss.str();

        }
};

class Calc{
    private:

    public:
        static double distance(const Point2D& p1, const Point2D& p2){
            return hypot(p1.x - p2.x, p1.y - p2.y);
        }

};

class Shape{
    private:
        string name;

    public:
        Shape(string name): name(name){

        }

        virtual ~Shape() = default;

        virtual string getName() const {
            return name;
        }

        virtual bool inside(Point2D p) = 0;
        virtual double getArea() = 0;
        virtual double getPerimeter() = 0;
        virtual string toString()const {
            return name;
        }
};

ostream& operator<<(ostream& os, const Shape& shape){
    return os << shape.toString();
}

class Circle : public Shape{
    private:
        Point2D center;
        double radius;
    public:
        Circle(Point2D center, double radius = 0) : Shape("Circ"), center(center), radius(radius){

        }

        bool inside(Point2D p) override{
            return Calc::distance(center, p) <= radius;
        }

        double getArea() override{
            return M_PI * radius *  radius;
        }

        double getPerimeter() override{
            return 2 * M_PI *  radius;
        }

        string toString()const override{
            stringstream ss;
            ss << fixed << setprecision(2) << getName() << ": C=" << center.toString() << ", R=" << radius;
            return ss.str();
        }
};

class Rectangle : public Shape{
    private:
        Point2D p1, p2;
    public:
        Rectangle(Point2D p1, Point2D p2) : Shape("Rect"), p1(p1), p2(p2){

        }

        bool inside(Point2D p) override{
            return (p1.x <= p.x && p.x <= p2.x && p1.y <= p.y && p.y <= p2.y);
        }

        double getArea()override{
            return abs(p2.x - p1.x) * abs(p2.y - p1.y);
        }

        double getPerimeter()override{
            return 2*(abs(p2.x - p1.x) + abs(p2.y - p1.y));
        }

        string toString() const override{
            stringstream ss;
            ss << getName() << ": P1=" << p1.toString() << " P2=" << p2.toString();
            return ss.str();
        }
};

int main() {
    vector<shared_ptr<Shape>> shapes;
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end")  { 
            break;                                  
        }
        else if (cmd == "show") { 
            cout << map_join(shapes, [](const auto& shape){
                return shape->toString();
            }, "\n") << endl;
        }
        else if (cmd == "circle") { 
            // Crie um novo circulo e adicione ao vetor
            double x{}, y{}, radius{};
            ss >> x >> y >> radius;
            shapes.push_back(make_shared<Circle>(Point2D(x,y), radius));
        }
        else if (cmd == "rect") {
            // Crie um retangulo e insira no vetor
            double x1{}, y1{}, x2{}, y2{};
            ss >> x1 >> y1 >> x2 >> y2;
            shapes.push_back(make_shared<Rectangle>(Point2D(x1, y1), Point2D(x2, y2)));
        }
        else if (cmd == "info") {
            // Imprima as informações de área e perímetro de todas as formas
            cout << map_join(shapes, [](const auto& shape){
                stringstream ss;
                ss << shape->getName() << ": A=" << fixed << setprecision(2) << shape->getArea() << " P=" << shape->getPerimeter();
                return ss.str();
            }, "\n") << endl;
        }
        else {
            cout << "fail: comando inválido" << '\n';
        }
    }
}
