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

#include "read_file.h"

#include <fstream>

bool read_file(const std::string& filepath, std::string& filedata, std::string& error) {
	// open the file:
	std::ifstream file(filepath, std::ios::binary);

	if (!file) {
		error = "Error reading file";
		return false;
	}

	try {
		// open the file:
		std::ifstream file(filepath, std::ios::binary);

		if (!file) {
			error = "Error reading file";
			return false;
		}

		// Stop eating new lines in binary mode!!!
		file.unsetf(std::ios::skipws);

		// get its size:
		long fileSize;

		file.seekg(0, std::ios::end);
		fileSize = (long)file.tellg();
		file.seekg(0, std::ios::beg);

		// read data from file
		char* buffer = new char[fileSize];
		file.read(buffer, fileSize);
		file.close();

		std::string s(buffer, fileSize);
		filedata = s;

		delete[]buffer;
		return true;
	}
	catch (const std::exception & e) {
		error = e.what();
		return false;
	}
}
