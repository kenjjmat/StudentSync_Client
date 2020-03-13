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

#include "get_sync_folder.h"

#include <Windows.h>
#include <shlobj.h>

#pragma comment(lib, "shell32.lib")

std::string get_sync_folder() {
    CHAR my_documents[MAX_PATH];
    HRESULT result = SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents);

    if (result != S_OK)
        return "C:\\StudentSync";
    else {
        std::string path(my_documents);
        return path + "\\StudentSync";
    }
}
