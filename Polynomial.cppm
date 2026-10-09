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

    bool are_equal(const T& a, const T& b) const { //сравнялка коэффициентов
        if constexpr(std::is_integral_v<T>) {
            return a == b;
        } else{
            return std::abs(a-b) < static_cast<RealTypeT<T>>(epsilon);
        }
    }

    std::size_t get_degree() const { //потск индекса старшего ненулевого члена
        if(_capacity == 0) {
            return 0;
        }
        for(std::size_t i = _capasity; i > 0; --i){
            if(!are_equal(_coeffs[i - 1], T(0))){
                return i - 1;
            }
        }
        return 0;
    }

    void shrink_to_fit() {
        if(_capasity == 0){
            delete[] _coeffs;
            _coeffs = new T[1];
            _capasity = 1;
            return;
        }
        std::size_t new_capasity = get_degree + 1;
        if (new_capasity == _capacity) { return; }

        T* new_coeffs = new T[new_capasity];
        for (std::size_t i = 0; i < new_capasity; ++i){
            new_coeffs[i] = _coeffs[i];
        }

        delete[] _coeffs;
        _coeffs = new_coeffs;
        _capacity = new_capasity;
    } 

        
    static T cast_size(std::size_t value) { //Т для сайз_т
        return T(static_cast<RealTypeT<T>>(value));
    }

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
        shrink_to_fit;
    }

    ~Polynomial() { delete[] _coeffs; }


    Polynomial(const Polynomial& other) //копирование
        : m_coeffs(new T[other._capacity]), m_capacity(other._capacity) {
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
        std::size_t result_degree = max_capacity == 0 ? 0 : max_capasity - 1;

        Polynomial result(result_degree);
        for(std::size_t i = 0; i < max_capasity; ++i){
            result.set(i, ((*this)[i] + other[i]));
        }
        result.shrink_to_fit();
        return result;
   }
   Polynomial operator- (const Polynomial& other) {
        std::size_t max_capacity = std::max(_capacity, other._capacity);
        std::size_t result_degree = max_capacity == 0 ? 0 : max_capasity - 1;

        Polynomial result(result_degree);
        for(std::size_t i = 0; i < max_capasity; ++i){
            result.set(i, ((*this)[i] - other[i]));
        }
        result.shrink_to_fit();
        return result;
   }
   
   Polynomial operator* (const T& scalar) {
        Polynomial result(*this);
        for(std::size_t i = 0; i < result._capacity; ++i){
            result._coeffs[i] = result._coeffs[i] * scalar;
        }
        result.shrink_to_fit();
        return result;
   }

   bool operator!=(const Polynomial& other) const {
        return !(*this = other);
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
};