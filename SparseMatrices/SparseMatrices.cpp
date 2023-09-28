#include "Matrix.h"

int main() {
    Matrix<int> m(4, 6);
    m.setValue(1, 2, 45);
    m.setValue(3, 4, 12);
    m.setValue(0, 3, -56);
    m.setValue(2, 0, 3);
    m.setValue(0, 1, -4);

    m.display();

    m.convert();
    m.display();

    return 0;
}
