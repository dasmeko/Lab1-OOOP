#include "Matrix.h"
#include "Figures.h"

bool f1(int n) {
    return n > 30;
}

int main() {
    Matrix<int> m(4, 5);
    m.setValue(0, 1, -4);
    m.setValue(0, 3, -56);
    m.setValue(1, 2, 45);
    m.setValue(2, 0, 3);
    m.setValue(3, 4, 12);

    cout << "m\n";
    m.display();

    cout << "Value at (0, 3): " << m.getValue(0, 3) << endl;
    cout << "First value > 30: " << m.findFirstValueByCriteria(&f1) << '\n';
    auto p = m.findValue(45);
    cout << "Indeces of 45: " << p.first << ' ' << p.second << endl;

    Matrix<int> m1 = m * 2;
    cout << "m*2\n";
    m1.display();

    vector<int> v = vector<int>{1, 2, 3, 4, 5};
    vector<int> v1 = m * v;
    cout << "m * (1 2 3 4 5): (";
    for (auto x : v1) {
        cout << x << ' ';
    }
    cout << ")" << endl;

    Matrix<int> a(2, 2), b(2, 2);
    a.setValue(0, 1, -4);
    a.setValue(1, 1, 3);
    b.setValue(1, 0, -43);
    b.setValue(1, 1, 12);

    cout << "A\n";
    a.display();
    cout << "B\n";
    b.display();

    Matrix<int> c = a + b;
    cout << "A+B\n";
    c.display();

    Matrix<int> d = a - b;
    cout << "A-B\n";
    d.display();

    Matrix<int> e = a * b;
    cout << "A*B\n";
    e.display();

    /*Line l1 = Line(1, -1, 0), l2 = Line(1, 0, -3);
    Circle c1 = Circle(0, 0, 1), c2 = Circle(2, 0, 1);
    auto points = intersect(l1, c1);
    for (auto p : points) {
        cout << p.first << ' ' << p.second << '\n';
    }

    Line l3 = reflect(l1, l2);
    cout << l3.a << ' ' << l3.b << ' ' << l3.c;*/

    return 0;
}
