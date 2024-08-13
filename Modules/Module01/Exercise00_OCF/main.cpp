#include <iostream>
#include <string>

using namespace std;

class Car {
private:
    string name;
    int speed;

public:
    // Default constructor
    Car() : name(""), speed(0) {
        cout << "Basic Constructor." << endl;
    }

    // Parameterized constructor
    Car(const string& name, int speed) : name(name), speed(speed) {
        cout << "Parameterized Constructor called." << endl;
    }

    // Copy constructor 처음 정의할 때
    // 복사 생성자에서 Car(Car other): 을 사용하면 값에의한 전달이 되기때문에
    //Car car2 = car1; 에서 car1객체를 복사해서 other를 생성한다.
    // 그런데 복사해서 생성하기 위해 또 복사생성자를 선언하는 무한루프가 발생함
    // 따라서 복사생성자는 참조에의한 전달을 해야함 &로
    Car(const Car& other) : name(other.name), speed(other.speed) {
        cout << "Copy Constructor called." << endl;
    }

    // Copy assignment operator 연산자 오버로딩 형식 -> [클래스이름] [operator][연산자]
    // Reference https://blog.hexabrain.net/177 
    Car& operator=(const Car& other) {
        cout << "Copy Assignment Operator called." << endl;
        if (this == &other) { //this는 현재 객체 가르치는 포인터, 따라서 복사할 객체의 주소를 가져온다 &other를 통해
            return *this; // Handle self-assignment
        }// 안해도 되지만 자기자신한테 할당하면 불필요한 작업을 하게됨 ex) car1 = car1

        name = other.name;
        speed = other.speed;
        return *this;
    }



    // Destructor
    ~Car() {
        cout << "Destructor called for: " << name << endl;
    }

    // Function to display car details
    void display() const {
        cout << "Car Name: " << name << ", Speed: " << speed << "\n" << endl;
    }
};

int main() {
    // Create a car using the default constructor
    Car car1;
    car1.display();

    // Create a car using the parameterized constructor
    Car car2("Ferrari", 200);
    car2.display();

    // Use the copy constructor
    Car car3 = car2;
    car3.display();

    // Use the copy assignment operator
    car1 = car3;
    car1.display();

    return 0;
}
