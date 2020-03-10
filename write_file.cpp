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