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
    [[nodiscard]] int getFoodPoints() const;
    static std::shared_ptr<Config> Instance();
private:
    Config();
    int _obstacles;
    int _slowdowns;
    int _speedups;
    int _food_points;

    static const std::string config_file_name;
    inline static std::shared_ptr<Config> _instance;

    static std::tuple<int, int, int, int> ReadConfig();
//    void WriteConfig();
};

#endif //SDL2TEST_CONFIG_H
