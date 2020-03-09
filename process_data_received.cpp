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

#include "process_data_received.h"

#include <liblec/lecui.h>

#include <vector>
#include <filesystem>
#include <iostream>
#include <sstream>

// for serializing vectors
#include <boost/serialization/vector.hpp>

// include headers that implement a archive in simple text format
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

void log(std::string info) {
    info = liblec::lecui::date::time_stamp() + " " + (info + "\n");
    std::cout << info;
}

enum sync_mode { filenames = 1, filelist = 2 };

struct sync_data {
    int mode;
    std::string payload;
};

// template definition to make sync_data serializable
template <class Archive>
void serialize(Archive& ar, sync_data& data, const unsigned int version) {
    ar& data.mode;
    ar& data.payload;
}

// serialize sync_data
bool serialize_sync_data(const sync_data& data,
    std::string& serialized, std::string& error) {
    try {
        std::stringstream ss;
        boost::archive::text_oarchive oa(ss);
        oa& data;
        serialized = ss.str();
        return true;
    }
    catch (const std::exception& e) {
        error = e.what();
        return false;
    }
}

// deserialize a sync_data object
bool deserialize_sync_data(const std::string& serialized,
    sync_data& data, std::string& error) {
    try {
        std::stringstream ss;
        ss << serialized;
        boost::archive::text_iarchive ia(ss);
        ia& data;
        return true;
    }
    catch (const std::exception& e) {
        error = e.what();
        return false;
    }
}

// serialize filename list
bool serialize_filename_list(const std::vector<std::string>& filename_list,
    std::string& serialized, std::string& error) {
    try {
        std::stringstream ss;
        boost::archive::text_oarchive oa(ss);
        oa& filename_list;
        serialized = ss.str();
        return true;
    }
    catch (const std::exception & e) {
        error = e.what();
        return false;
    }
}

// deserialize filename list
bool deserialize_filename_list(const std::string& serialized,
    std::vector<std::string>& filename_list,
    std::string& error) {
    try {
        std::stringstream ss;
        ss << serialized;
        boost::archive::text_iarchive ia(ss);
        ia& filename_list;
        return true;
    }
    catch (const std::exception & e) {
        error = e.what();
        return false;
    }
}

void process_data_received(liblec::lecnet::tcp::client& client,
    const std::string& sync_folder) {
    static sync_mode mode = sync_mode::filenames;

    std::string error;

    sync_data data;
    data.mode = mode;

    switch (mode)
    {
    case sync_mode::filenames: {
        // compile list of files in sync folder
        std::vector<std::string> filename_list;
        for (const auto& entry : std::filesystem::directory_iterator(sync_folder))
            if (entry.is_regular_file())
                filename_list.push_back(entry.path().filename().string());

        // serialize filename_list into a string
        std::string serialized_filename_list;
        if (serialize_filename_list(filename_list, serialized_filename_list, error))
            data.payload = serialized_filename_list;    // make this the payload
        else
            log(error);

        // switch mode for next iteration
        mode = sync_mode::filelist;
    } break;

    case sync_mode::filelist: {


        // switch mode for next iteration
        mode = sync_mode::filenames;
    } break;
    default:
        break;
    }

    // serialized the sync_data
    std::string serialized_sync_data;
    if (serialize_sync_data(data, serialized_sync_data, error)) {
        // send data to server
        std::string received;
        if (client.send_data(serialized_sync_data, received, 5, nullptr, error))
            log("Response: " + received);
        else
            log(error);
    }
    else
        log(error);
}
