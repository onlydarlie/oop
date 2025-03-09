#include <iostream>
#include <array>

class Point {
private:
  int x;
  int y;
public:
  // Конструкторы 
  Point(): x{0}, y{0} { std::cout << "Point: Конструктор по умолчанию\n"; } // Конструктор по умолчанию
  Point(std::pair<int, int>& points): x{points.first}, y{points.second} { std::cout << "Point: Конструктор с параметрами:\tx = " << x << "\ty = " << y << "\n"; } // Конструктор с параметрами
  Point(int givedX, int givedY): x{givedX}, y{givedY} { std::cout << "Point: Конструктор с параметрами:\tx = " << x << "\ty = " << y << "\n"; } // Конструктор с параметрами
  Point(const Point& p): x{p.x}, y{p.y} { std::cout << "Point: Копирующий конструктор:\tx = " << x << "\ty = " << y << "\n"; } // Копирующий конструктор
  Point(Point&&); // Перемещающий конструктор

  ~Point() { // Деструктор
    std::cout << "Point: Вызов деструктора с параметрами:\tx = " << x << "\ty = " << y << "\n";
  }

  const std::pair<int, int> getCoords() const; // Геттер
  void setCoords(const std::pair<int, int>); // Сеттер
};

// Реализация перемещающего конструктора
Point::Point(Point&& p) { 
  x = std::move(p.x);
  y = std::move(p.y);
  std::cout << "Point: Перемещающий конструктор:\tx = " << x << "\ty = " << y << "\n";
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

  // Копирующий конструктор
  Rectangle(const Rectangle& p) {
    for (size_t i = 0; i < 4; ++i) vertexes[i].setCoords(p.vertexes[i].getCoords());
    std::cout << "Rectangle: Копирующий конструктор с параметрами:\n" << *this;
  }

  // Деструктор
  ~Rectangle() {
    std::cout << "Rectangle: Вызов деструктора с параметрами:";
    std::cout << *this;
  }

  friend std::ostream& operator<<(std::ostream&, const Rectangle&);

  int area() {

  }
};

std::ostream& operator<<(std::ostream& os, const Rectangle& p) {
  for (size_t i = 0; i < 4; ++i) os << i << "): x = " << p.vertexes[i].getCoords().first << "\ty = " << p.vertexes[i].getCoords().second << '\n'; 
  return os;
}

class Square;

int main() {

  return 0;
}