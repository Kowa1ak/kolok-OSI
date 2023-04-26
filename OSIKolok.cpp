
#include <iostream>
#include <list>
#include <gtest/gtest.h>

using namespace std;

class Observer {
public:
    virtual void update(float temperature, float humidity) = 0;
};

class WeatherStation {
public:
    static WeatherStation& getInstance() {
        static WeatherStation instance;
        return instance;
    }
    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }
    void removeObserver(Observer* observer) {
        observers.remove(observer);
    }
    void notifyObservers() {
        for (Observer* observer : observers) {
            observer->update(temperature, humidity);
        }
    }
    void setMeasurements(float temperature, float humidity) {
        this->temperature = temperature;
        this->humidity = humidity;
        notifyObservers();
    }
private:
    WeatherStation() {}
    list<Observer*> observers;
    float temperature;
    float humidity;
};

class DisplayScreen : public Observer {
public:
    void update(float temperature, float humidity) {
        cout << "DisplayScreen: Temperature is " << temperature << " and humidity is " << humidity << endl;
    }
};

class MobileApp : public Observer {
public:
    void update(float temperature, float humidity) {
        cout << "MobileApp: Temperature is " << temperature << " and humidity is " << humidity << endl;
    }
};

TEST(WeatherStationTest, Singleton) {
    WeatherStation& station1 = WeatherStation::getInstance();
    WeatherStation& station2 = WeatherStation::getInstance();
    ASSERT_EQ(&station1, &station2);
}

TEST(WeatherStationTest, NotifyObservers) {
    WeatherStation& station = WeatherStation::getInstance();
    DisplayScreen screen;
    MobileApp app;
    station.addObserver(&screen);
    station.addObserver(&app);
    station.setMeasurements(25.0f, 60.0f);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
