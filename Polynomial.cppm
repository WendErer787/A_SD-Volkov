#include <complex>;
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

     bool are_equal(const T& a, const T& b) const {
        if constexpr(std::is_integral_v<T>) {
            return a == b;
        } else{
            return std::abs(a-b) < static_cast<RealTypeT<T>>(epsilon);
        }
    }

    Polynomial() { }

    explicit Polynomial(std::size_t max_degree) : _coeffs(new T(max_degree + 1)), _capasity(max_degree + 1) {}

    Polynomial(const T* coeffs, std::size_t size) {
        if(size == 0){
            _coeffs = new T[1]();
            _capasity = 1;
        } else {
            if(coeffs == nullptr){
                throw Std::invalid_argument("Coefficient array is null");
            }
            _coeffs = new T[size];
            _capasity = size;
            for (int i = 0; i < size; ++i){
                _coeffs[i] = coeffs[i];
            }
        }
    }

    ~Polynomial() { delete[] coeffs; }


    Polynomial(const Polynomial& other) //копирование
        : m_coeffs(new T[other.m_capacity]), m_capacity(other.m_capacity) {
        for (size_t i = 0; i < m_capacity; ++i) {
            m_coeffs[i] = other.m_coeffs[i];
        }
    }

     Polynomial& operator=(const Polynomial& other) {
        if (this != &other) {
            T* new_coeffs = new T[other.m_capacity];
            for (size_t i = 0; i < other.m_capacity; ++i) {
                new_coeffs[i] = other.m_coeffs[i];
            }
            delete[] m_coeffs;
            m_coeffs = new_coeffs;
            m_capacity = other.m_capacity;
        }
        return *this;
    }


    Polynomial(Polynomial&& other) noexcept //перемещение
        : m_coeffs(other.m_coeffs), m_capacity(other.m_capacity) {
        other.m_coeffs = nullptr;
        other.m_capacity = 0;
    }

    Polynomial& operator=(Polynomial&& other) noexcept {
        if (this != &other) {
            delete[] m_coeffs;
            m_coeffs = other.m_coeffs;
            m_capacity = other.m_capacity;
            other.m_coeffs = nullptr;
            other.m_capacity = 0;
        }
        return *this;
    }


    T operator[](size_t power) const {
        if (power >= m_capacity) {
            return T(0);
        }
        return m_coeffs[power];
    }


   Polynomial operator+ () {

   }
   Polynomial operator- () {

   }
   Polynomial operator[] () {

   }
   Polynomial operator* () {
    
   }

   
    Polynomial(std::size_t max_degree): coeffs(new  T[max_degree+1]()), capasity(max_degree+1) {}

    void shrink_to_fit() {

    } 

    static T cast_size(std::size_t value) {
        if constexpr(std::is_same_v<T, std::complex<float>>) {
            return std::complex<float>(static_cast<float>(value), 0.0f);
        }else if constexpr(std::is_same_v<T, std::complex<double>(value)) {
            return std::complex<double>(static_cast<double>(value), 0.0f);
        }else{
            return static_cast<T>(value);
        }
    }

};