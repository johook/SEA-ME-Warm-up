#include "car.h"

Car::Car(int id, int speed, QObject *parent)
    : QObject(parent), position(0), speed(speed), id(id) {}

void Car::move() {
    position += speed;
    emit positionChanged(position);
}

int Car::getPosition() const {
    return position;
}

int Car::getid() const
{
    return id;
}
