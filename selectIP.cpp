/*
** selectIP.cpp
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

#include "selectIP.h"

#include <string>
#include <sstream>

#include <vector>
#include <algorithm>

#include <stdio.h>

template<typename T>
bool sortAndCompare(std::vector<T>& v1, std::vector<T>& v2)
{
	std::sort(v1.begin(), v1.end());
	std::sort(v2.begin(), v2.end());
	return v1 == v2;
}

struct ip
{
	int i;
	int j;
	int k;
	int l;
};

ip convertIP(std::string sIP)
{
	ip m_ip;

	if (false)
	{
		char dot;
		std::istringstream s(sIP);
		s >> m_ip.i >> dot >> m_ip.j >> dot >> m_ip.k >> dot >> m_ip.l >> dot;
	}
	else
	{
		sscanf_s(sIP.c_str(), "%d.%d.%d.%d", &m_ip.i, &m_ip.j, &m_ip.k, &m_ip.l);
	}

	return m_ip;
} // convertIP

std::string convertIP(ip m_ip)
{
	std::stringstream s;
	s << m_ip.i << "." << m_ip.j << "." << m_ip.k << "." << m_ip.l;
	return s.str();
} // convertIP

std::string selectIP(
	std::vector<std::string> vServerIPs,
	std::vector<std::string> vClientIPs
)
{
	std::string sIP;

	try
	{
		// erase all occurences of "127.0.0.1" from the IP lists
		vServerIPs.erase(std::remove(vServerIPs.begin(), vServerIPs.end(), "127.0.0.1"), vServerIPs.end());
		vClientIPs.erase(std::remove(vClientIPs.begin(), vClientIPs.end(), "127.0.0.1"), vClientIPs.end());

		do
		{
			if (sortAndCompare(vServerIPs, vClientIPs))
			{
				sIP = "127.0.0.1";
				break;
			}

			std::vector<ip> vServ, vCli;

			// convert server IPs
			for (auto it : vServerIPs)
				vServ.push_back(convertIP(it));

			// convert client IPs
			for (auto it : vClientIPs)
				vCli.push_back(convertIP(it));

			struct similarityCount
			{
				ip m_iserverip;
				int iCount;
			};

			std::vector<similarityCount> vStructs;

			// loop through the client IPs and find which one is most similar to the server IPs
			for (auto it : vCli)
			{
				for (auto m_it : vServ)
				{
					int iCount = 0;

					if (it.i == m_it.i)
					{
						iCount++;

						if (it.j == m_it.j)
						{
							iCount++;

							if (it.k == m_it.k)
							{
								iCount++;

								if (it.l == m_it.l)
									iCount++;
							}
						}
					}

					similarityCount m;
					m.iCount = iCount;
					m.m_iserverip = m_it;

					vStructs.push_back(m);
				}
			}

			// loop through and select one with greatest count
			if (vStructs.empty())
			{
				// this shouldn't happen
				sIP.clear();
				break;
			}

			sIP = convertIP(vStructs[0].m_iserverip);
			int iHighestCount = vStructs[0].iCount;

			for (auto it : vStructs)
			{
				if (it.iCount > iHighestCount)
				{
					sIP = convertIP(it.m_iserverip);
					iHighestCount = it.iCount;
				}
			}
		} while (false);
	}
	catch (const std::exception&)
	{
		// this shouldn't happen
	}

	return sIP;
} // selectIP
