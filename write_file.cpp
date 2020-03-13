/*
** StudentSync LAN Synchronization Tool: Client
** Copyright (c) 2020
** Alec T. Musasa (alecmus at live dot com),
** Kennedy J.J. Maturure (kenjjmat at outlook dot com)
** 
** Released under the Creative Commons Attribution Non-Commercial
** 2.0 Generic license (CC BY-NC 2.0).
** 
** See accompanying file CC-BY-NC-2.0.txt or copy at [here](https://github.com/alecmus/StudentSync_Server/blob/master/CC-BY-NC-2.0.txt).
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

#include "write_file.h"

#include <fstream>

bool write_file(const std::string& data,
	const std::string& full_path,
	std::string& error)
{
	try {
		std::ofstream file;
		file.open(full_path,
			std::ios::out | std::ios::trunc | std::ios::binary);

		if (!file) {
			error = "Error opening destination file";
			return false;
		}

		file.write(data.c_str(), data.length());
		file.close();
		return true;
	}
	catch (const std::exception & e) {
		error = e.what();
		return false;
	}
}
