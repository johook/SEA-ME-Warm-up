#ifndef CAR_H
#define CAR_H

#include <QObject>

class Car : public QObject {
    Q_OBJECT
public:
    Car(int id, int speed, QObject *parent = nullptr);

    int getPosition() const;
    void move();
    int getid()const;

signals:
    void positionChanged(int newPosition);

private:
    int position;
    int speed;
    int id;
};

#endif // CAR_H
