/*
** StudentSync LAN Synchronization Tool: Client
**
** This code may not be copied, modified or distributed without the
** express written permission of the author(s). Any violation shall
** be prosecuted to the maximum extent possible under law.
**
*************************************************************************
** Project Details:
**
** National University of Science and Technology
** SCS2206 Computing in Society Group Project
**
** Group members: Alec T. Musasa, Kennedy J.J. Maturure
**
*/

// STL includes
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <thread>
#include <chrono>

// liblec network library
#include <liblec/lecnet/udp.h>  // for UDP Multicasting
#include <liblec/lecnet/tcp.h>
#include <liblec/lecui.h>

// select IP algorithm
#include "selectIP.h"

void log(std::string info) {
    info = liblec::lecui::date::time_stamp() + " " + (info + "\n");
    std::cout << info;
}

int main() {
    std::cout << "\n**********************************************\n";
    printf("\x1B[32m%s\033[0m", "StudentSync Client version 1.0.0.0\n");
    std::cout << "**********************************************\n\n";

    while (true) {
        // listen for datagrams
        log("Listen for datagram ...");

        // create multicast receiver object
        liblec::lecnet::udp::multicast::receiver rc(30003, "239.255.0.3", "0.0.0.0");

        std::string error, ips_serialized;

        while (true) {
            const long long cycle = 1500;   // 1.5 seconds

            // run the receiver
            if (rc.run(cycle, error)) {
                // loop while running
                while (rc.running())
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));

                // no longer running ... check if a datagram was received
                if (rc.get(ips_serialized, error)) {
                    std::cout << liblec::lecui::date::time_stamp() + " ";
                    printf("\x1B[33m%s\033[0m", "Datagram received!\n");
                    break;
                }
            }
            else
                std::cout << "Error: " << error << std::endl;
        }

        // stop the receiver
        rc.stop();

        // deserialize ip list
        std::vector<std::string> ips;

        while (true) {
            auto idx = ips_serialized.find("#");

            if (idx != std::string::npos) {
                auto ip = ips_serialized.substr(0, idx);
                ips.push_back(ip);
                ips_serialized.erase(0, idx + 1);
            }
            else
                break;
        }

        std::string s = liblec::lecui::date::time_stamp() + " Server IP list: ";
        for (auto ip : ips)
            s += (ip + "; ");
        std::cout << s << std::endl;

        // get client IP list
        std::vector<std::string> ips_client;
        liblec::lecnet::tcp::get_host_ips(ips_client);

        s = liblec::lecui::date::time_stamp() + " Client IP list: ";
        for (auto ip : ips_client)
            s += (ip + "; ");
        std::cout << s << std::endl;

        std::string selected_ip = selectIP(ips, ips_client);

        std::cout << liblec::lecui::date::time_stamp();

        s = " Selected IP: " + selected_ip;

        printf("\x1B[95m%s\033[0m", s.c_str());

        // loop forever
        while (1)
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    return 0;
}
