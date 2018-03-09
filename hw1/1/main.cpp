#include <iostream>
#include <assert.h>
#include <fstream>
using namespace std;

/*
1_2. Вычислить площадь выпуклого n-угольника, заданного координатами своих вершин. Вначале вводится количество вершин,
затем последовательно целочисленные координаты всех вершин в порядке обхода против часовой стрелки.
n < 1000, координаты < 10000.
Указание. Для вычисления площади n-угольника можно посчитать сумму ориентированных площадей трапеций под каждой стороной
многоугольника.
*/

class point{
public:
    point():x(0), y(0) {}
    friend std::ostream& operator << (std::ostream& os, point const& obj){
        return os << obj.x << ' ' << obj.y;
    }
    friend std::istream& operator >> (std::istream& is, point& obj){
        is >> obj.x >> obj.y;
        return is;
    }
    int x;
    int y;
};

class polygon{
public:
    polygon() : mas(nullptr), size_(0){}
    polygon(int n){
        mas = new point[n];
        size_ = n;
    }
    ~polygon() { delete [] mas;}

    point& operator [](int i){
        assert(i >=0 && i < size_);
        return mas[i];
    }
    point operator [](int i) const {
        assert(i >=0 && i < size_);
        return mas[i];
    }
    int size() const {
        return size_;
    }
    void printPoly(){
        for (int i = 0; i < size_; ++i)
            cout << mas[i] << endl;
    }
    double area(){
        double s = 0;
        for (int i=0; i < size_; ++i){
            point p1 = mas[i];
            point p2 = (i==size_-1) ? mas[0] : mas[i+1];
            s = s + (p1.y+p2.y)*(p1.x-p2.x);
        }
        return (s >= 0) ? (s/2) : -(s/2);
    }
private:
    point* mas;
    int size_;
};

void readPolygon(polygon& poly, istream& is = cin){
    for(int i = 0; i < poly.size(); ++i){
        is >> poly[i];
    }
}


int main() {
    int n = 0;
    cin >> n;
    polygon poly(n);
    readPolygon(poly);
    cout << "area = " << poly.area()<< endl;
    return 0;
}