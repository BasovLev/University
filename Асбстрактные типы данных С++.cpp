#include <iostream>
#include <cmath>

class Complex {
    double re, im, mod, arg;  // Хранение часла в декартовых и полярных координатах     - 1
public:
    Complex(double re_val, double im_val) {
        re = re_val; im = im_val;
        mod = sqrt(re*re + im*im);
        arg = atan2(im, re);
        
    }
    Complex(double val) // Реализация конструктора преобразования
        { re = val; im = 0.0;}
    Complex() 
        { re = 0.0; im = 0.0;}  // Реализация конструктора умолчания
    double get_re() const { return re; }   
    double get_im() const { return im; }  // Методы извлечения действительной и мнимой части   - 2
    double modulo() const { return mod; }
    double argument() const { return arg; }  // Методы вычисления модуля и аргумента           - 3
    Complex spr() const { return Complex(re, -im); } // Методы вычисления сопряженного числа  - 4
    Complex operator~() const {
        return Complex(re, -im);             // Перегрузка одноместной операции (~□)         - 5
    }
    
    const Complex& operator=(const Complex& c) {
        re = c.re; im = c.im;
        return *this;                   // Перегрузка операции присваивания              - 6
    }
    const Complex& operator=(double val) {
        re = val;
        im = 0.0;
        return *this;
    }
    Complex operator-() const {
        return Complex(-re, -im);
    }                              // Перегрузка операции изменение знака (-□)      - 7
    
    const Complex& operator+=(const Complex& c) {
        re += c.re; im += c.im;
        return *this;
    }
    const Complex& operator-=(const Complex& c) {
        re -= c.re; im -= c.im;
        return *this;
    }
    const Complex& operator*=(const Complex& c) {
        re = (re*c.re - im*c.im); im = (re*c.im + im*c.re);
        return *this;
    }
     const Complex& operator/=(const Complex& c) {             // Перегрузка двухместных арифметических операций с присваиванием  - 8
        re = (re*c.re + im*c.im)/(c.re*c.re + c.im*c.im); im = (-re*c.im + im*c.re)/(c.re*c.re + c.im*c.im);
        return *this;
    }
    // Перегрузка операторов для сложения с числом типа double  - 9
    const Complex& operator+=(double val) {
        re += val;
        return *this;
    }
    const Complex& operator-=(double val) {
        re -= val;
        return *this;
    }
    const Complex& operator*=(double val) {
        re *= val;
        im *= val;
        return *this;
    }
    const Complex& operator/=(double val) {
        if (val == 0) {
            std::cerr << "Error: Division by zero!" << std::endl;
            return *this;
        }
        re /= val;
        im /= val;
        return *this;
    }
    
    Complex sqrtC() const {
        double sqrt_mod = std::sqrt(mod);
        for (int i = 0; i < 2; ++i) {
            // Вычисляем углы для двух квадратных корней
            double alpha = (arg + 2 * M_PI * i) / 2;
            double re_part = sqrt_mod * std::cos(alpha);
            double im_part = sqrt_mod * std::sin(alpha);
            return Complex(re_part, im_part);
            std::cout << "Root " << (i + 1) << ": " << re_part << " + " << im_part << "i" << std::endl;  // Метод, соответствующий операции извлечения корня из комплексного числа - 13
        }
    }
    
    Complex powC (double n) const {
        double new_mod = std::pow(mod, n);
        double new_arg = arg * n;
        double new_re = new_mod * std::cos(new_arg);
        double new_im = new_mod * std::sin(new_arg);
        return Complex(new_re, new_im);           // Метод, соответствующий операции возведения в степень комплексного числа - 14
    }
    
    Complex operator^(double n) const {
        double new_mod = std::pow(mod, n);
        double new_arg = arg * n;
        double new_re = new_mod * std::cos(new_arg);
        double new_im = new_mod * std::sin(new_arg); 
        
        return Complex(new_re, new_im);           // Перегрузка операции, обозначаемая символом «^»  - 15
    }
    
     // Перегрузка оператора вывода для комплексных чисел
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c.re << " + " << c.im << "i";
        return os;
    }

    // Перегрузка оператора ввода для комплексных чисел
    friend std::istream& operator>>(std::istream& is, Complex& c) {
        char sign, i;
        is >> c.re >> sign >> c.im >> i;
        if (sign == '-') c.im = -c.im;
        c.mod = sqrt(c.re * c.re + c.im * c.im);
        c.arg = atan2(c.im, c.re);
        return is;
    }
    
};


// Перегрузка двухместных арифметических операций для типа Complex и double   - 10,11
Complex operator+(const Complex& a, const Complex& b) {
    return Complex(a.get_re() + b.get_re(), a.get_im() + b.get_im());
}

Complex operator-(const Complex& a, const Complex& b) {
    return Complex(a.get_re() - b.get_re(), a.get_im() - b.get_im());
}

Complex operator*(const Complex& a, const Complex& b) {
    return Complex(a.get_re() * b.get_re() - a.get_im() * b.get_im(), a.get_re() * b.get_im() + a.get_im() * b.get_re());
}

Complex operator/(const Complex& a, const Complex& b) {
    if (b.get_re() == 0 && b.get_im() == 0) {
        std::cerr << "Error: Division by zero!" << std::endl;    // Попытка деления комплексного числа на нулевое число приводит к сообщению об ошибке   - 12
        return Complex(0, 0);
    }
    double denom = b.get_re() * b.get_re() + b.get_im() * b.get_im();
    return Complex((a.get_re() * b.get_re() + a.get_im() * b.get_im()) / denom, (a.get_im() * b.get_re() - a.get_re() * b.get_im()) / denom);
}


Complex operator+(const Complex& a, double b) {
    return Complex(a.get_re() + b, a.get_im());
}

Complex operator+(double a, const Complex& b) {
    return Complex(a + b.get_re(), b.get_im());
}

Complex operator-(const Complex& a, double b) {
    return Complex(a.get_re() - b, a.get_im());
}

Complex operator-(double a, const Complex& b) {
    return Complex(a - b.get_re(), -b.get_im());
}

Complex operator*(const Complex& a, double b) {
    return Complex(a.get_re() * b, a.get_im() * b);
}

Complex operator*(double a, const Complex& b) {
    return Complex(a * b.get_re(), a * b.get_im());
}

Complex operator/(const Complex& a, double b) {
    if (b == 0) {
        std::cerr << "Error: Division by zero!" << std::endl;     // Попытка деления комплексного числа на нулевое число приводит к сообщению об ошибке   - 12
        return Complex(0, 0);
    }
    return Complex(a.get_re() / b, a.get_im() / b);
}

Complex operator/(double a, const Complex& b) {
    if (b.get_re() == 0 && b.get_im() == 0) {
        std::cerr << "Error: Division by zero!" << std::endl;
        return Complex(0, 0);
    }
    double denom = b.get_re() * b.get_re() + b.get_im() * b.get_im();
    return Complex(a * b.get_re() / denom, -a * b.get_im() / denom);
}



int main ()
{
    
    double a, b;
    std::cin >> a;
    std::cin >> b;                        
    double n = 3.0;              
    Complex C(a, b);              //  Комплексное число можно представлять в виде a+i*b,   - 16
    std::cout <<  C << std::endl;
    return 0;                      //  Ввод-вывод на экран комплексного числа происходит по типу работы cin и cout  - 17

}
 