#ifndef CARTHREAD_H
#define CARTHREAD_H

#include <QThread>
#include <QMutex>
#include "car.h"
#include "racetrack.h"

class CarThread : public QThread {
    Q_OBJECT

public:
    CarThread(Car *car, RaceTrack *track, QMutex *mutex);

protected:
    void run() override;

private:
    Car *car;
    RaceTrack *raceTrack;
    QMutex *mutex;
};

#endif // CARTHREAD_H
