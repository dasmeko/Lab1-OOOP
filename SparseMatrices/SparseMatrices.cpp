#include "Matrix.h"

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

    m.display();
    //cout << m.getValue(0, 2) << endl;
    cout << m.findFirstValueByCriteria(&f1) << '\n';
    auto p = m.findValue(-45);
    cout << p.first << ' ' << p.second;

    //m.convert();
    //m.display();

    return 0;
}
