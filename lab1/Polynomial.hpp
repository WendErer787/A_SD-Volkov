#include <complex>
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <type_traits>

template <typename T>
struct RealType{
    using Type = T;
};

template <typename T>
using RealTypeT = typename RealType<T>::Type;

template <typename T>
struct RealType<std::complex<T>>{
    using Type = T;
};

template <typename T>
class Polynomial{
    private:

    T* _coeffs;
    std::size_t _capacity;

    static constexpr double epsilon = 1e-6;

    public:

    static bool are_equal(const T& a, const T& b){
        if constexpr(std::is_integral_v<T>) {
            return a == b;
        } else{
            return std::abs(a-b) < static_cast<RealTypeT<T>>(epsilon);
        }
    }

    std::size_t get_degree() const {
        if(_capacity == 0) {
            return 0;
        }
        for(std::size_t i = _capacity; i > 0; --i){
            if(!are_equal(_coeffs[i - 1], T(0))){
                return i - 1;
            }
        }
        return 0;
    }

    void shrink_to_fit() {
        if(_capacity == 0){
            delete[] _coeffs;
            _coeffs = new T[1];
            _capacity = 1;
            return;
        }
        std::size_t new_capacity = get_degree() + 1;
        if (new_capacity == _capacity) { return; }

        T* new_coeffs = new T[new_capacity];
        for (std::size_t i = 0; i < new_capacity; ++i){
            new_coeffs[i] = _coeffs[i];
        }

        delete[] _coeffs;
        _coeffs = new_coeffs;
        _capacity = new_capacity;
    } 

        
    static T cast_size(std::size_t value) { //из сайз_т в Т
        return T(static_cast<RealTypeT<T>>(value));
    }

    explicit Polynomial(std::size_t max_degree) : _coeffs(new T[max_degree + 1]()), _capacity(max_degree + 1) {}

    Polynomial(const T* coeffs, std::size_t size) {
        if(size == 0){
            _coeffs = new T[1]();
            _capacity = 1;
        } else {
            if(coeffs == nullptr){
                throw std::invalid_argument("Coefficient array is null");
            }
            _coeffs = new T[size];
            _capacity = size;
            for (std::size_t i = 0; i < size; ++i){
                _coeffs[i] = coeffs[i];
            }
        }
        shrink_to_fit();
    }


    ~Polynomial() { delete[] _coeffs; }


    Polynomial(const Polynomial& other) //копирование
        : _coeffs(new T[other._capacity]), _capacity(other._capacity) {
        for (size_t i = 0; i < _capacity; ++i) {
            _coeffs[i] = other._coeffs[i];
        }
    }

    Polynomial& operator=(const Polynomial& other) {
        if (this != &other) {
            T* new_coeffs = new T[other._capacity];
            for (size_t i = 0; i < other._capacity; ++i) {
                new_coeffs[i] = other._coeffs[i];
            }
            delete[] _coeffs;
            _coeffs = new_coeffs;
            _capacity = other._capacity;
        }
        return *this;
    }


    Polynomial(Polynomial&& other) noexcept //перемещение
        : _coeffs(other._coeffs), _capacity(other._capacity) {
        other._coeffs = nullptr;
        other._capacity = 0;
    }

    Polynomial& operator=(Polynomial&& other) noexcept {
        if (this != &other) {
            delete[] _coeffs;
            _coeffs = other._coeffs;
            _capacity = other._capacity;
            other._coeffs = nullptr;
            other._capacity = 0;
        }
        return *this;
    }


    T operator[](std::size_t power) const {
        if (power >= _capacity) {
            return T(0);
        }
        return _coeffs[power];
    }


   Polynomial operator+ (const Polynomial& other) const {
        std::size_t max_capacity = std::max(_capacity, other._capacity);
        std::size_t result_degree = max_capacity == 0 ? 0 : max_capacity - 1;

        Polynomial result(result_degree);
        for(std::size_t i = 0; i < max_capacity; ++i){
            result.set(i, ((*this)[i] + other[i]));
        }
        result.shrink_to_fit();
        return result;
   }
   Polynomial operator- (const Polynomial& other) const {
        std::size_t max_capacity = std::max(_capacity, other._capacity);
        std::size_t result_degree = max_capacity == 0 ? 0 : max_capacity - 1;

        Polynomial result(result_degree);
        for(std::size_t i = 0; i < max_capacity; ++i){
            result.set(i, ((*this)[i] - other[i]));
        }
        result.shrink_to_fit();
        return result;
   }
   
   Polynomial operator* (const T& scalar) const {
        Polynomial result(*this);
        for(std::size_t i = 0; i < result._capacity; ++i){
            result._coeffs[i] = result._coeffs[i] * scalar;
        }
        result.shrink_to_fit();
        return result;
   }

   bool operator!=(const Polynomial& other) const {
        return !(*this == other);
   }

   bool operator==(const Polynomial& other) const {
        std::size_t max_degree = std::max(get_degree(), other.get_degree());
        for(std::size_t i = 0; i <= max_degree; ++i){
            if(!are_equal((*this)[i], other[i])){
                 return false;
            }
        }
        return true;
   }

   friend std::ostream& operator<<(std::ostream& os, const Polynomial<T>& poly){
        if(poly.get_degree() == 0 && are_equal(poly[0], T(0))){
            os << "0";
            return os;
        }
        bool first = true;
        std::size_t degree = poly.get_degree();
        for(std::size_t i = degree + 1; i > 0; --i){
            std::size_t index = i - 1;
            T coeff = poly[index];
            if(are_equal(coeff, T(0))) { continue; }
            if(!first) { os << " + "; }
            os << "(" << coeff << ")*x^" << index;
            first = false;
        }
        return os;
    }

    void expand(std::size_t new_capacity){
        if(new_capacity <= _capacity) { return; }

        T* new_coeffs = new T[new_capacity]();

        for (size_t i = 0; i < _capacity; ++i) {
            new_coeffs[i] = _coeffs[i];
        }
        delete[] _coeffs;
        _coeffs = new_coeffs;
        _capacity = new_capacity;
    }
    void set(std::size_t power, const T& value){
        if(power >= _capacity){
            expand(power + 1);
        }
        _coeffs[power] = value;
    }

    T evaluate(const T& x) const {
        std::size_t deg = get_degree();
        T result = (*this)[deg];
        for (std::size_t i = deg; i > 0; --i) {
            result = result * x + (*this)[i - 1];
        }
        return result;
    }
};

template <typename T>
Polynomial<T> operator*(const T& scalar, const Polynomial<T>& poly){
    return poly * scalar;
}

template <typename T>
Polynomial<T> compute_derivative(const Polynomial<T>& poly){
    std::size_t degree = poly.get_degree();
    if(degree == 0){
        return Polynomial<T>(0);
    }
    Polynomial<T> derivative(degree - 1);
    for(std::size_t i = 1; i <= degree; ++i){
        T multiplier = Polynomial<T>::cast_size(i);
        derivative.set(i - 1, poly[i]*multiplier);
    }
    derivative.shrink_to_fit();
    return derivative;
}