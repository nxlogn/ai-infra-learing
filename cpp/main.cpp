#include <bits/stdc++.h>

using namespace std;

// struct Complex {
//     double re, im;

//     friend ostream& operator<<(ostream& os, const Complex& c) {
//         os << c.re << "+" << c.im << "i";
//         return os; // 返回流引用
//     }
// };

// Complex operator+(double x, const Complex& c) {
//     return {x + c.re, x + c.im};
// }

// int main() {
//     Complex a{1, 2};
//     Complex b{2, 3};

//     Complex c = 5 + b;

//     cout<<c;

// }

struct Myarr {
    int data[10]{};

    int &operator[](size_t i) { return data[i]; }
    int operator[](size_t i) const { return data[i]; }
};
int main() {
    Myarr a;
    int x = a[5];
    cout << x;
}
