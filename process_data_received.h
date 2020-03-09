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

#pragma once

#include <string>
#include <liblec/lecnet/tcp.h>

void log(std::string info);

void process_data_received(liblec::lecnet::tcp::client& client,
	const std::string& sync_folder);