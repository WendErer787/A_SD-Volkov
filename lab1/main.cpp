#include "Polynomial.hpp"

#include <complex>
#include <iostream>
#include <random>

int main () {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(-10.0, 10.0);

    Polynomial<double> a(3);
    for (std::size_t i = 0; i <= 3; ++i){
        a.set(i, dist(gen));
    }

    double raw[] = {1.0, 2.0, 3.0};
    Polynomial<double> b(raw, 3);

    std::cout << "A = " << a << '\n';
    std::cout << "B = " << b << '\n';

    std::cout << "A[2] = " << a[2] << '\n';

    std::cout << "(A + B) = " << (a + b) << '\n';
    std::cout << "(A - B) = " << (a - b) << '\n';

    std::cout << "A * 2= " << a * 2.0 << '\n';
    std::cout << "2 * A= " << 2.0 * a << '\n';

    std::cout << "(A == B) = " << (a == b) << '\n';
    std::cout << "(A != B) = " << (a != b) << '\n';

    std::cout << "A(1.5) = " << a.evaluate(1.5) << '\n';

    a.expand(6);
    std::cout << "A[5] = " << a[5] << '\n';
    a.shrink_to_fit();
    std::cout << "A after shrink = " << a << '\n';

    std::cout << "A' = " << compute_derivative(a) << '\n';

    std::complex<double> c[] = {{1.0, 2.0}, {0.0, 0.0}, {3.0, -1.0}};
    Polynomial<std::complex<double>> p(c, 3);

    std::cout << "P = " << p << '\n';
    std::cout << "P' = " << compute_derivative(p) << '\n';


    return 0;
}