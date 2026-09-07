#include <iostream>

using namespace std;

int main() {
    int x{5};
    int& ref{x};
    cout<<static_cast<bool>(ref == x);
    return 0;
}