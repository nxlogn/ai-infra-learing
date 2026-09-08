#include <iostream>

using namespace std;

class person {
  private:
    int m_x{};
    int m_y{};

  public:
    person(int x, int y) : m_x{x}, m_y{y} { cout << m_x << " " << m_y<<endl; }
    void print() const {
        cout<<m_y<<" "<<m_x;
    }
};

int main() {
    person p1{1, 2};
    p1.print();
    return 0;
}