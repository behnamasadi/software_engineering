// Facade — present a small, task-oriented API in front of several
// independent subsystems. The client calls `leaveHome()` / `returnHome()` and
// the facade orchestrates the alarm, AC, and TV. The subsystems stay simple
// and reusable; the facade just wires them together for one common workflow.

#include <iostream>

class Alarm {
public:
    void turnOn()  { std::cout << "  alarm ON (house secured)\n"; }
    void turnOff() { std::cout << "  alarm OFF\n"; }
};

class AirConditioner {
public:
    void turnOn()  { std::cout << "  AC ON\n"; }
    void turnOff() { std::cout << "  AC OFF\n"; }
};

class Television {
public:
    void turnOn()  { std::cout << "  TV ON\n"; }
    void turnOff() { std::cout << "  TV OFF\n"; }
};

class SmartHome {
public:
    void leaveHome() {
        std::cout << "Leaving home...\n";
        ac_.turnOff();
        tv_.turnOff();
        alarm_.turnOn();
    }

    void returnHome() {
        std::cout << "Coming home...\n";
        alarm_.turnOff();
        ac_.turnOn();
        tv_.turnOn();
    }

private:
    Alarm alarm_;
    AirConditioner ac_;
    Television tv_;
};

int main() {
    SmartHome home;
    home.leaveHome();
    home.returnHome();
}
