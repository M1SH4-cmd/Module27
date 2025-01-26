#include <iostream>
#include <cassert>

class TrainCar {


    int passangersMax = 0;
    int passengers = 0;
    class Train* train = nullptr;

public:
    TrainCar(class Train* train, int passangersMax) : passangersMax(passangersMax), train(train)
    {
        assert(train!= nullptr);
        assert(passangersMax >= 0);
    }

    void loadPassengers(int value) {
        passengers += value;
        if (passengers > passangersMax) passengers = passangersMax;
    }

    int getPassengers() {
        return passengers;
    }

    int getNumber();


};

class Train {
private:
    int count = 0;
    TrainCar** trainCars = nullptr;

public:
    TrainCar* getCarAt(int index){
        if (this == nullptr) return nullptr;
        if (index < 0) return nullptr;
        if (index >= count) return nullptr;
        return trainCars[index];
    }

    int getCount() {
        return count;
    }

    Train(int count, int passengersMax) {
        assert(count >= 0);
        this->count = count;
        this->trainCars = new TrainCar*[count];
        for (int i = 0; i < count; ++i) {
            trainCars[i] = new TrainCar(this, passengersMax);
        }
    }

};

int TrainCar::getNumber() {
    for (int i = 0; i < train->getCount(); ++i) {
        TrainCar* car = train->getCarAt(i);
        if (car == this) return i;
    }
    assert(false);
}

int main() {

    Train* train = new Train(10, 30);
    for (int i = 0; i < train->getCount(); ++i) {
        int passengers = 0;
        std::cin >> passengers;
        train->getCarAt(i)->loadPassengers(passengers);
    }

    return 0;
}