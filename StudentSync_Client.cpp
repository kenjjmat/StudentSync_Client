/*
** StudentSync_Client.cpp
**
** StudentSync LAN Synchronization Tool: Client
** Copyright (c) 2020
** Alec Musasa (alecmus at live dot com),
** Kennedy J.J. Maturure (kenjjmat at outlook dot com)
** 
** Released under the Creative Commons Attribution Non-Commercial
** 2.0 Generic license (CC BY-NC 2.0).
** 
** See accompanying file CC-BY-NC-2.0.txt or copy at
** https://github.com/alecmus/StudentSync_Server/blob/master/CC-BY-NC-2.0.txt
**
*************************************************************************
** Project Details:
**
** National University of Science and Technology
** SCS2206 Computing in Society Group Project
**
** Group members: Alec Musasa, Kennedy J.J. Maturure
**
*/

// STL includes
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <thread>
#include <chrono>
#include <filesystem>

// liblec network library
#include <liblec/lecnet/udp.h>  // for UDP broadcasting
#include <liblec/lecnet/tcp.h>
#include <liblec/cui.h>

// select IP algorithm
#include "selectIP.h"

// sync folder location
#include "get_sync_folder.h"

// process data received
#include "process_data_received.h"

int main() {
    std::cout << "\n**********************************************\n";
    printf("\x1B[32m%s\033[0m", "StudentSync Client version 1.0.0.0\n");
    std::cout << "**********************************************\n\n";

    // create StudentSync folder if it doesn't exist
    const std::string sync_folder = get_sync_folder();
    std::filesystem::path path(sync_folder);
    
    if (!std::filesystem::exists(path))
        std::filesystem::create_directory(path);

    while (true) {
        // listen for datagrams
        log("Listening for datagram ...");

        // create broadcast receiver object
        liblec::lecnet::udp::broadcast::receiver receiver(30003, "0.0.0.0");

        std::string error, ips_serialized;

        while (true) {
            const long long cycle = 1500;   // 1.5 seconds

            // run the receiver
            if (receiver.run(cycle, error)) {
                // loop while running
                while (receiver.running())
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));

                // no longer running ... check if a datagram was received
                if (receiver.get(ips_serialized, error)) {
                    std::cout << liblec::cui::date_gen::time_stamp() + " ";
                    printf("\x1B[33m%s\033[0m", "Datagram received!\n");
                    break;
                }
            }
            else
                std::cout << "Error: " << error << std::endl;
        }

        // stop the receiver
        receiver.stop();

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

        std::string s = liblec::cui::date_gen::time_stamp() + " Server IP list: ";
        for (auto ip : ips)
            s += (ip + "; ");
        std::cout << s << std::endl;

        // get client IP list
        std::vector<std::string> ips_client;
        liblec::lecnet::tcp::get_host_ips(ips_client);

        s = liblec::cui::date_gen::time_stamp() + " Client IP list: ";
        for (auto ip : ips_client)
            s += (ip + "; ");
        std::cout << s << std::endl;

        std::string selected_ip = selectIP(ips, ips_client);

        std::cout << liblec::cui::date_gen::time_stamp();

        s = " Selected IP: " + selected_ip + "\n";

        printf("\x1B[95m%s\033[0m", s.c_str());

        // configure tcp/ip client parameters
        liblec::lecnet::tcp::client::client_params params;
        params.address = selected_ip;
        params.port = 55553;
        params.magic_number = 16;
        params.use_ssl = false;

        // create tcp/ip client object
        liblec::lecnet::tcp::client client;

        if (client.connect(params, error)) {
            while (client.connecting())
                std::this_thread::sleep_for(std::chrono::milliseconds(1));

            if (client.connected(error)) {
                while (client.running()) {
                    process_data_received(client, sync_folder);
                    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
                }

                std::cout << liblec::cui::date_gen::time_stamp() + " ";
                printf("\x1B[31m%s\033[0m", "Connection lost!\n");
            }
            else
                log(error);
        }
        else
            log(error);
    }

    return 0;
}
