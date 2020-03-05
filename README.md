# StudentSync_Client
StudentSync LAN Synchronization Tool: Client

The StudentSync application is made up of
1. A server (https://github.com/alecmus/StudentSync_Server)
2. A client (https://github.com/alecmus/StudentSync_Client)

The application is a tool for automatically synchronizing Student generated academic
material over a LAN.

How it works
============

1.  Server sends UDP multicast datagram containing the IP addresses of all its interfaces
2.  Client listens for datagrams
3.  a. Client receives datagram and extracts server IPs
    b. Client selects IP address within the same range
4.  Client requests connection to server over a TCP/IP connection
5.  Server accepts client connection and sends acknowledgement to client
6.  Client sends file-list to server
7.  Server consolidates file-list from all connected clients
8.  Server creates a table listing client addresses and corresponding missing file lists
9.  Client requests missing files
10. Server sends missing files to respective clients, updating missing file table
11. Client is notified of added files

Platform
========
Microsoft Windows family of operating systems (Win 8, 8.1, 10, or later)

System Requirements
===================
10MB free disk space minimum
64MB ram minimum
Network Card (Ethernet, WiFi etc.)
