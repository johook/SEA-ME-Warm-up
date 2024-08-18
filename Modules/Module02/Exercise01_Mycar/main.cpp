#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Part 추상 클래스 정의
class Part {
public:
    virtual void print() = 0; // 순수 가상 함수
    virtual ~Part() = default; // 가상 소멸자
};

// PowertrainParts 클래스 정의
class PowertrainParts {
public:
    virtual void print() = 0; // 순수 가상 함수
    virtual ~PowertrainParts() = default; // 가상 소멸자
};

// Engine 클래스 정의
class Engine : public PowertrainParts {
public:
    void print() override {
        cout << "Engine Part" << endl;
    }
};

// Clutch 클래스 정의
class Clutch : public PowertrainParts {
public:
    void print() override {
        cout << "Clutch Part" << endl;
    }
};

// Transmission 클래스 정의
class Transmission : public PowertrainParts {
public:
    void print() override {
        cout << "Transmission Part" << endl;
    }
};

// Gear 클래스 정의
class Gear : public PowertrainParts {
public:
    void print() override {
        cout << "Gear Part" << endl;
    }
};

// Wheel 클래스 정의
class Wheel : public PowertrainParts {
public:
    void print() override {
        cout << "Wheel Part" << endl;
    }
};

// Motor 클래스 정의 (EV용)
class Motor : public PowertrainParts {
public:
    void print() override {
        cout << "Motor Part" << endl;
    }
};

// Reducer 클래스 정의 (EV용)
class Reducer : public PowertrainParts {
public:
    void print() override {
        cout << "Reducer Part" << endl;
    }
};

// Battery 클래스 정의 (EV용)
class Battery : public PowertrainParts {
public:
    void print() override {
        cout << "Battery Part" << endl;
    }
};

// Car 클래스 정의
class Car {
public:
    Car() {
        powertrain_parts_.emplace_back(new Engine());
        powertrain_parts_.emplace_back(new Clutch());
        powertrain_parts_.emplace_back(new Transmission());
        powertrain_parts_.emplace_back(new Gear());
        for (int i = 0; i < 4; ++i) {
            powertrain_parts_.emplace_back(new Wheel());
        }
    }

    void printParts() {
        for (auto& part : powertrain_parts_) {
            part->print();
        }
    }
    
    ~Car() {
        for (auto part : powertrain_parts_) {
            delete part; // 동적으로 할당된 메모리를 해제
        }
    }
    
private:
    vector<PowertrainParts*> powertrain_parts_;
};

// EV 클래스 정의
class EV {
public:
    EV() {
        powertrain_parts_.emplace_back(new Motor());
        powertrain_parts_.emplace_back(new Reducer());
        powertrain_parts_.emplace_back(new Battery());
        for (int i = 0; i < 4; ++i) {
            powertrain_parts_.emplace_back(new Wheel());
        }
    }
    
    void printParts() {
        for (auto& part : powertrain_parts_) {
            part->print();
        }
    }
    
    ~EV() {
        for (auto part : powertrain_parts_) {
            delete part; // 동적으로 할당된 메모리를 해제
        }
    }
    
private:
    vector<PowertrainParts*> powertrain_parts_;
};

int main() {
    cout << "Car Parts:" << endl;
    Car myCar;
    myCar.printParts();
    
    cout << endl;

    cout << "EV Parts:" << endl;
    EV myEV;
    myEV.printParts();
    
    return 0;
}
