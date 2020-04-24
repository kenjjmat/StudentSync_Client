/*
** process_data_received.h
**
** StudentSync LAN Synchronization Tool: Client
** Copyright (c) 2020
** Alec T. Musasa (alecmus at live dot com),
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
** Group members: Alec T. Musasa, Kennedy J.J. Maturure
**
*/

#pragma once

#include <string>
#include <liblec/lecnet/tcp.h>

void log(std::string info);

void process_data_received(liblec::lecnet::tcp::client& client,
	const std::string& sync_folder);
