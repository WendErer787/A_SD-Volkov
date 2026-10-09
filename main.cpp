#include "Polynomial.cppm"

#include <complex>
#include <iostream>
#include <random>

main () {
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

    
 
    return 0;
}