//
// Created by Rutvik Patel on 12/12/22.
//

#ifndef SDL2TEST_CONFIG_H
#define SDL2TEST_CONFIG_H

#include "string"
#include "tuple"

class Config {
public:
    [[nodiscard]] int getObstacles() const;
    [[nodiscard]] int getSlowdowns() const;
    [[nodiscard]] int getSpeedups() const;
    static std::shared_ptr<Config> Instance();
private:
    Config();
    int _obstacles;
    int _slowdowns;
    int _speedups;

    static const std::string config_file_name;
    static std::shared_ptr<Config> _instance;

    static std::tuple<int, int, int> ReadConfig();
//    void WriteConfig();
};

#endif //SDL2TEST_CONFIG_H
