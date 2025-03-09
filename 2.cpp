#include <iostream>
#include <array>
#include <vector>
#include <cmath>

class Point {
private:
  int x;
  int y;
public:
  double something = 0;
  // Конструкторы
  Point(): x{0}, y{0} { std::cout << "Point: Конструктор по умолчанию\n"; } // Конструктор по умолчанию
  Point(std::pair<int, int> points): x{points.first}, y{points.second} { std::cout << "Point: Конструктор с параметрами: x = " << x << " y = " << y << "\n"; } // Конструктор с параметрами
  Point(int givedX, int givedY): x{givedX}, y{givedY} { std::cout << "Point: Конструктор с параметрами: x = " << x << " y = " << y << "\n"; } // Конструктор с параметрами
  Point(const Point& p): x{p.x}, y{p.y} { std::cout << "Point: Копирующий конструктор: x = " << x << " y = " << y << "\n"; } // Копирующий конструктор
  Point(Point&&); // Перемещающий конструктор

  ~Point() { // Деструктор
    std::cout << "Point: Вызов деструктора с параметрами: x = " << x << " y = " << y << "\n";
  }

  const std::pair<int, int> getCoords() const; // Геттер
  void setCoords(const std::pair<int, int>); // Сеттер
};

// Реализация перемещающего конструктора
Point::Point(Point&& p) { 
  x = std::move(p.x);
  y = std::move(p.y);
  std::cout << "Point: Перемещающий конструктор: x = " << x << " y = " << y << "\n";
}

// Реализация геттера
const std::pair<int, int> Point::getCoords() const {
  return std::make_pair(x, y);
}

// Реализация сеттера
void Point::setCoords(const std::pair<int, int> givedCoords) {
  x = givedCoords.first;
  y = givedCoords.second;
}

class Rectangle {
protected:
  std::array<Point, 4> vertexes;
public:
  // Конструктор по умолчанию
  Rectangle() { std::cout << "Rectangle: Конструктор по умолчанию\n"; } 

  // Конструктор с параметрами
  Rectangle(std::array<std::pair<int, int>, 4>& points) { 
    for (size_t i = 0; i < 4; ++i) vertexes[i].setCoords(points[i]);
    std::cout << "Rectangle: Конструктор с параметрами\n" << *this;
  }

  // Конструктор с параметрами (array of points)
  Rectangle(std::array<Point, 4>& points) { 
    for (size_t i = 0; i < 4; ++i) vertexes[i].setCoords(points[i].getCoords());
    std::cout << "Rectangle: Конструктор с параметрами (array of points)\n" << *this;
  }

  // Копирующий конструктор
  Rectangle(const Rectangle& p) {
    for (size_t i = 0; i < 4; ++i) vertexes[i].setCoords(p.vertexes[i].getCoords());
    std::cout << "Rectangle: Копирующий конструктор с параметрами:\n" << *this;
  }

  // Деструктор
  ~Rectangle() {
    std::cout << "Rectangle: Вызов деструктора с параметрами:\n";
    std::cout << *this;
  }

  friend std::ostream& operator<<(std::ostream&, const Rectangle&);

  virtual double area() {
    const std::pair<int, int> p1 = vertexes[0].getCoords();
    const std::pair<int, int> p2 = vertexes[1].getCoords();
    const std::pair<int, int> p3 = vertexes[2].getCoords();
    return sqrt(abs(p2.first - p1.first) + abs(p2.second - p1.second)) * sqrt(abs(p3.first - p1.first) + abs(p3.second - p1.second));
  }

  virtual void shapeName() {
    std::cout << "Its Rectangle\n";
  }

  const std::array<Point, 4> getVertex() const {
    return vertexes;
  }
};

std::ostream& operator<<(std::ostream& os, const Rectangle& p) {
  for (size_t i = 0; i < 4; ++i) os << i << "): x = " << p.vertexes[i].getCoords().first << " y = " << p.vertexes[i].getCoords().second << '\n'; 
  return os;
}

class Center {
private:
  Point coords;
public:
  Center() = default;
  Center(int givedX, int givedY): coords{givedX, givedY} { }
  Center(const Center* c): coords{c->coords} { }
};

class Square: public Rectangle {
protected:
  Center* c;
private:
  double sideSize() {
    const std::pair<int, int> p1 = vertexes[0].getCoords();
    const std::pair<int, int> p2 = vertexes[1].getCoords();
    return sqrt(abs(p2.first - p1.first) + abs(p2.second - p1.second));
  }
public:
  // Конструктор по умолчанию
  Square(): c {new Center()} { std::cout << "Square: Конструктор по умолчанию\n"; } 

  // Конструктор с параметрами
  Square(std::array<std::pair<int, int>, 4>& points): c {new Center((points[0].first + points[1].first) / 2, (points[0].second + points[1].second) / 2)} { 
    for (size_t i = 0; i < 4; ++i) vertexes[i].setCoords(points[i]);
    std::cout << "Square: Конструктор с параметрами\n" << *this;
  }

  // Конструктор с параметрами (array of points)
  Square(std::array<Point, 4>& points): c {new Center((points[0].getCoords().first + points[1].getCoords().first) / 2, (points[0].getCoords().second + points[1].getCoords().second) / 2)} { 
    for (size_t i = 0; i < 4; ++i) vertexes[i].setCoords(points[i].getCoords());
    std::cout << "Square: Конструктор с параметрами (array of points)\n" << *this;
  }

  // Копирующий конструктор
  Square(const Square& p): c {new Center(p.c)} {
    for (size_t i = 0; i < 4; ++i) vertexes[i].setCoords(p.vertexes[i].getCoords());
    std::cout << "Square: Копирующий конструктор с параметрами:\n" << *this;
  }
  
  // Копирующий от базового класса конструктор 
  Square(const Rectangle& p): c {new Center()} {
    const std::array<Point, 4> v = p.getVertex();
    for (size_t i = 0; i < 4; ++i) vertexes[i].setCoords(v[i].getCoords());
    std::cout << "Square: Копирующий от базового класса конструктор с параметрами:\n" << *this;
  }

  // Деструктор
  ~Square() {
    delete c;
    std::cout << "Square: Вызов деструктора с параметрами:";
    std::cout << *this;
  }

  double area() override {
    return pow(sideSize(), 2);
  }

  void shapeName() override {
    std::cout << "Its Square\n";
  }
};

int main() {
  // Test Point
  std::cout << "TEST POINTS\n\n";
  Point p1;
  Point p2{std::make_pair(4, 7)};
  Point* p3 = new Point(6, 9);
  Point* p4 = new Point(8, 91);
  Point p5 = *p3;
  delete p3;
  std::cout << p5.getCoords().first << ' ' << p5.getCoords().first << '\n';
  Point p6 = std::move(*p4);
  delete p4;
  p6.something = 7.;
  p6.setCoords({3, 6});
  std::cout << p6.getCoords().first << ' ' << p6.getCoords().first << '\n';

  // Test Rectangle
  std::cout << "\nTEST RECTANGLES\n\n";
  Rectangle r1;
  Rectangle* r2 = new Rectangle(r1);
  delete r2;
  
  std::array<std::pair<int, int>, 4> arr {{{1,3}, {5,7}, {6,7}, {1,3}}};
  Rectangle r3(arr);

  std::cout << "Вывод:\n" << r3;

  r3.shapeName();
  std::cout << "With area: " << r3.area() << '\n';

  Rectangle* r4 = new Rectangle(arr);
  Rectangle* r5 = new Rectangle(*r4);
  delete r5;

  std::array<std::pair<int, int>, 4> arr2 {{{34,37}, {8,1}, {0,6}, {5,50}}};
  Rectangle r6 = arr2;
  std::array<Point, 4> arr3 {{p2, p5, p6, p2}};
  Rectangle r7 = arr3;

  // Test Square
  std::cout << "\nTEST SQUARES\n\n";
  Square s1;
  Square s2 {arr};
  Square& s3 = s2;
  Square* s4;
  s4 = new Square(s2);
  delete s4;
  Square* s5 = new Square(arr);
  s5->shapeName();
  std::cout << "With area: " << s5->area() << '\n';
  delete s5;

  p1.setCoords(std::make_pair(1, 12));
  p2.setCoords(std::make_pair(2, 23));
  p5.setCoords(std::make_pair(3, 34));
  p6.setCoords(std::make_pair(4, 45));
  std::array<Point, 4> arr4 {{p1, p2, p5, p6}};
  Square* s6 = new Square(arr4);

  std::array<Rectangle*, 5> rectangles {&r3, &r7, &r6, &s2, s6};
  for (auto& r: rectangles) {
    r->shapeName();
    std::cout << "With area: " << r->area() << '\n';
  }

  delete r4;
  delete s6;
  
  return 0;
}