//
// Created by Zheng on 05/03/2018.
//

#ifndef ZELDA_ZELDA_H
#define ZELDA_ZELDA_H

#include <string>
#include "ZeldaLogger.h"

#define ZELDA_MODE_PLAIN "plain"
#define ZELDA_MODE_TUNNEL "tunnel"
#define ZELDA_MODE_TCP "tcp"

typedef std::string ZeldaMode;

class Zelda {

public:

#pragma mark - Initializers

    Zelda(const std::string &address, int port);

#pragma mark - Address Options

    std::string GetAddress();
    int GetPort();

    std::string GetRemoteAddress();
    void SetRemoteAddress(const std::string &address);
    int GetRemotePort();
    void SetRemotePort(int port);

#pragma mark - Advanced Options

    int GetUseSplice();
    void SetUseSplice(int splice);

    int GetMaxConnection();
    void SetMaxConnection(int count);

#pragma mark - Loggers

    ZeldaLogger GetLogger();
    void SetLogger(ZeldaLogger logger);

#pragma mark - Launch

    int StartProxy(const ZeldaMode &mode);

private:

#pragma mark - Logger

    ZeldaLogger Log;

#pragma mark - Options

    int _use_splice = 0;
    int _max_connection = 20;

#pragma mark - Proxies

    int StartPlainProxy();
    int StartTunnelProxy();
    int StartTCPProxy(int server_sock);

#pragma mark - Socket

    std::string _address;
    int _port = 0;
    std::string GetSocketString();

    std::string _remote_address;
    int _remote_port = 0;
    std::string GetRemoteSocketString();

    int GetServerSock();

    int CreateSocket(const char *bind_addr, int port, int max_connection);

#pragma mark - TCP Client

    void HandleTCPClient(int client_sock, struct sockaddr_in client_addr);
    int CreateTCPConnection(const char *remote_host, int remote_port);
    void ForwardTCPData(int source_sock, int destination_sock);

#pragma mark - Helper

    std::string SocketStringFromSocket(sockaddr_in addr);

    int _connections_processed = 0;
    void AddProcessedConnection();
    void ResetProcessedConnection();

};


#endif //ZELDA_ZELDA_H