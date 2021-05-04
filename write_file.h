/*
** write_file.h
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

#pragma once

#include <string>

bool write_file(const std::string& data,
	const std::string& full_path,
	std::string& error);
