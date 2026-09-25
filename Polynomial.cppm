
template <typename T>

class Polynomial{
    private:

    T* coeffs;
    std::size_t capacity;

    static constexpr double epsilon = 1e-6;

    bool are_equal(const T& a, const T& b) const {
        if constexpr(std::is_integral_v<T>) {
            return a==b;
        } else{
            return std::abs(a-b) < epsilon;
        }
    }

    public:

   Polynomial operator+ () {

   }
   Polynomial operator- () {

   }
   Polynomial operator[] () {

   }
   Polynomial operator* () {
    
   }

    Polynomial() { }
    ~Polynomial() { delete[] coeffs; }

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