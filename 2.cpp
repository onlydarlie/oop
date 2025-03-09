#include <iostream>

class Point {
private:
  int x;
  int y;
public:
  // Конструкторы 
  Point(): x{0}, y{0} { std::cout << "Конструктор по умолчанию\n"; } // Конструктор по умолчанию
  Point(int givedX = 0, int givedY = 0): x{givedX}, y{givedY} { std::cout << "Конструктор с параметрами:\tx = " << x << "\ty = " << y << "\n"; } // Конструктор с параметрами
  Point(const Point& p): x{p.x}, y{p.y} { std::cout << "Копирующий конструктор:\tx = " << x << "\ty = " << y << "\n"; } // Копирующий конструктор
  Point(Point&&); // Перемещающий конструктор

  ~Point() { // Деструктор
    std::cout << "Вызов деструктора класса Point с параметрами:\tx = " << x << "\ty = " << y << "\n";
  }

  const std::pair<int, int> getCoords() const; // Геттер
  void setCoords(std::pair<int, int>&); // Сеттер
};

// Реализация перемещающего конструктора
Point::Point(Point&& p) { 
  x = std::move(p.x);
  y = std::move(p.y);
  std::cout << "Перемещающий конструктор:\tx = " << x << "\ty = " << y << "\n";
}

// Реализация геттера
const std::pair<int, int> Point::getCoords() const {
  return std::make_pair(x, y);
}

// Реализация сеттера
void Point::setCoords(std::pair<int, int>& givedCoords) {
  x = givedCoords.first;
  y = givedCoords.second;
}

class Rectangle;
class Square;

int main() {

  return 0;
}