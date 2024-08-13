#include <iostream>
#include <string>

using namespace std;

// Car 클래스 정의
class Car {
protected: // 해당 class + 상속받은 class에서만 접근가능
    string make;
    string model;
    int year;

public:
    // 기본 생성자
    Car() : make("Unknown"), model("Unknown"), year(0) {
        cout << "Car: 기본 생성자 호출" << endl;
    }

    // 매개변수가 있는 생성자
    Car(const string& make, const string& model, int year)
        : make(make), model(model), year(year) {
        cout << "Car: 매개변수가 있는 생성자 호출" << endl;
    }

    // 소멸자
    ~Car() {
        cout << "Car: 소멸자 호출" << endl;
    }

    // drive 함수
    void drive() {
        cout << "Car: " << make << " " << model << " " << year << " edition 운전 중" << endl;
    }
};

// SportsCar 클래스 정의 (Car 클래스 상속 -> 코드 재사용 가능 + 부모 클래스에서 변경하면 자식클래스에 영향 줄 수 있음)\
   상속에 대한 Reference https ://gdngy.tistory.com/177

class SportsCar : public Car {
private:
    int top_speed;

public:
    // 기본 생성자
    SportsCar() : Car(), top_speed(0) {
        cout << "SportsCar: 기본 생성자 호출" << endl;
    }

    // 매개변수가 있는 생성자
    SportsCar(const string& make, const string& model, int year, int top_speed)
        : Car(make, model, year), top_speed(top_speed) {
        cout << "SportsCar: 매개변수가 있는 생성자 호출" << endl;
    }

    // 소멸자
    ~SportsCar() {
        cout << "SportsCar: 소멸자 호출" << endl;
    }

    // drive 함수 (Car 클래스의 drive 함수 확장)
    void drive() {
        Car::drive(); // 부모 클래스의 drive 함수 호출
        cout << "SportsCar: 최고 속도는 " << top_speed << "km/h 입니다." << endl;
    }
};

// 메인 함수
int main() {
    // Car 객체 생성 및 사용
    Car car1("hyundai", "IONIQ 6", 2022);
    car1.drive();

    cout << endl;

    // SportsCar 객체 생성 및 사용
    SportsCar sportsCar1("Ferrari", "488 Spider", 2022, 330);
    sportsCar1.drive();

    return 0;
}
