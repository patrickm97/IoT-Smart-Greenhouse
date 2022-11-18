#ifndef RUNNER_HPP
#define RUNNER_HPP

#include <iostream>
#include <vector>
#include "isensor.hpp"
#include "configmqtt.hpp"

class Runner {
    private:
        vector<ISensor*> sensors;
        ConfigMqtt &config;

    public:
        Runner(ConfigMqtt &config) : config(config) {
        }

        void addSensor(ISensor* sensor){
            sensors.push_back(sensor);
        }

        void loop() {
            for (int i = 0; i < sensors.size(); i++) {
                if (millis() - sensors[i]->lastPublish > sensors[i]->publishInterval) {
                    long valorSensor = sensors[i]->readValue();
                    config.publish(sensors[i]->sensorId, String(valorSensor));
                    sensors[i]->lastPublish = millis();
                }
            }
        }

        void setInterval() {
            cout << "runner set interval";
        }
};

#endif