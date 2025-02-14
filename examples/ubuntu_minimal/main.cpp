/// This software is distributed under the terms of the MIT License.
/// Copyright (c) 2022 Dmitry Ponomarev.
/// Author: Dmitry Ponomarev <ponomarevda96@gmail.com>

#include <iostream>
#include "cyphalNode/cyphal.hpp"
#include <chrono>
#include <thread>

uint32_t platformSpecificGetTimeMs() {
    static auto time_start = std::chrono::steady_clock::now();
    auto time_now = std::chrono::steady_clock::now();
    auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time_now - time_start).count();
    return elapsed_time_ms;
}

int main (int argc, char *argv[]) {
    cyphal::Cyphal cyphal;
    int init_res = cyphal.init(42);
    if (init_res < 0) {
        std::cout << "Error: ";
        switch (init_res) {
            case -cyphal::CYPHAL_TRANSPORT_INIT_ERROR:
                std::cout << "CYPHAL_TRANSPORT_INIT_ERROR";
                break;
            case -cyphal::CYPHAL_HEAP_INIT_ERROR:
                std::cout << "CYPHAL_HEAP_INIT_ERROR";
                break;
            case -cyphal::CYPHAL_SUB_APPLICATION_INIT_ERROR:
                std::cout << "CYPHAL_SUB_APPLICATION_INIT_ERROR";
                break;
            default:
                break;
        }
        std::cout << " (" << init_res << ")" << std::endl;
        return init_res;
    }

    std::cout << "Node with id=" << cyphal.getNodeId() << " has been started." << std::endl;
    while(true) {
        cyphal.process();
    }
}
