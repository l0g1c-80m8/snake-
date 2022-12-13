//
// Created by Rutvik Patel on 12/12/22.
//

#include <fstream>
#include <sstream>
#include "config.h"

const std::string Config::config_file_name = "../game-config.txt";

std::shared_ptr<Config> Config::Instance() {
    if (!_instance) {
        _instance.reset(new Config());
    }
    return _instance;
}

Config::Config() {
    auto config = Config::ReadConfig();
    _obstacles = std::get<0>(config);
    _slowdowns = std::get<1>(config);
    _speedups = std::get<2>(config);
    _food_points = std::get<3>(config);
}

std::tuple<int, int, int, int> Config::ReadConfig() {
    std::ifstream in_stream(Config::config_file_name);
    std::string line, value;
    int conf1 = 0;
    int conf2 = 0;
    int conf3 = 0;
    int conf4 = 0;

    if (in_stream.is_open()) {
        if (std::getline(in_stream, line)) {
            std::istringstream basicInputStringStream(line);
            basicInputStringStream >> value;
            conf1 = stoi(value);
        }
        if (std::getline(in_stream, line)) {
            std::istringstream basicInputStringStream(line);
            basicInputStringStream >> value;
            conf2 = stoi(value);
        }
        if (std::getline(in_stream, line)) {
            std::istringstream basicInputStringStream(line);
            basicInputStringStream >> value;
            conf3 = stoi(value);
        }
        if (std::getline(in_stream, line)) {
            std::istringstream basicInputStringStream(line);
            basicInputStringStream >> value;
            conf4 = stoi(value);
        }
    }
    return {conf1, conf2, conf3, conf4};
}

int Config::getObstacles() const { return _obstacles; }
int Config::getSlowdowns() const { return _slowdowns; }
int Config::getSpeedups() const { return _speedups; }
int Config::getFoodPoints() const { return _food_points; }
