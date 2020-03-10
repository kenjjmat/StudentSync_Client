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

bool write_file(const std::vector<char>& data,
	const std::string& full_path,
	std::string& error)
{
	try {
		std::ofstream file(full_path, std::ios::binary); // output file stream

		if (file)
		{
			// dump the contents of the vector in the file
			for (auto& inf : data)
				file.write(reinterpret_cast<const char*>(&inf), sizeof(inf));
		}

		file.close();
		return true;
	}
	catch (const std::exception & e) {
		error = e.what();
		return false;
	}
}