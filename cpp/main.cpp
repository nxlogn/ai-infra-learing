#include <iostream>

class Animal {
public:
    void speak() const {
        std::cout<< "动物发出声音\n";
    }
};

class Dog : public Animal {
public:
    void speak() const {
        std::cout<< "汪汪\n";
    }
};

int main() {
    Dog dog;
    Animal& animal = dog;
    dog.speak();
    animal.speak();
}