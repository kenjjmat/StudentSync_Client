# StudentSync_Client
StudentSync LAN Synchronization Tool: Client

<p>
  <img alt="Lines of code" src="https://img.shields.io/tokei/lines/github/kenjjmat/StudentSync_Client">
</p>

#### Release Info
<p>
  <img alt="GitHub release (latest by date)" src="https://img.shields.io/github/v/release/kenjjmat/StudentSync_Client">
  <img alt="GitHub Release Date" src="https://img.shields.io/github/release-date/kenjjmat/StudentSync_Client">
</p>

### About the Project
This project was done as a group project in partial fulfilment of the requirements for the course SCS2206 at [NUST](https://nust.ac.zw) in the year 2020, Computer Science Department. StudentSync is a tool for automatically synchronizing Student generated academic material over a LAN.

The StudentSync application is made up of two components:
1. A server application (https://github.com/alecmus/StudentSync_Server)
2. A client application (https://github.com/kenjjmat/StudentSync_Client)

### Dependencies
This app was built using the [lecnet network library](https://github.com/alecmus/lecnet), which is part of the [liblec C++ libraries](https://github.com/alecmus/liblec).

### How it Works
1.  Server sends UDP multicast datagram containing the IP addresses of all its interfaces
2.  Client listens for datagrams
3.  Client receives datagram and:
    1. Extracts server IPs
    2. Selects IP address within the same range
4.  Client requests connection to server over a TCP/IP connection
5.  Server accepts client connection and sends acknowledgement to client
6.  Client sends file-list to server
7.  Server consolidates file-list from all connected clients
8.  Server creates a table listing client addresses and corresponding missing file lists
9.  Client requests missing files
10. Server sends missing files to respective clients, updating missing file table
11. Client is notified of added files

### Platform
Microsoft Windows family of operating systems (Win 8, 8.1, 10, or later)

### System Requirements
 * 10MB free disk space minimum
 * 64MB ram minimum
 * Network Card (Ethernet, WiFi etc.)
