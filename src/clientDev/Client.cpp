#include <iostream>
#include <csignal>
#include <bits/sigaction.h>
#include <thread>
#include "Client.h"
#include "../utils/Log.h"
#include "../utils/Config.h"
#include "../utils/ConstantMessages.h"
#include "../utils/BomberStudentExceptions.h"
#include "../utils/Utils.h"

using CM = ConstantMessages;

Client::Client() : gameStarted(false), socketUDP(Config::getProtocol(), true), socketTCP(Config::getProtocol()) {}

void Client::run() {
    auto timeMove = std::chrono::duration<float>(1/Config::getDefaultSpeed());
    SocketAddress multicast = SocketAddress("255.255.255.255", Config::getServerPort());
    SocketAddress server_addr = SocketAddress();
    socketUDP.setTimeout(3,0);
    Log::info("Search server...");
    search_server:
    try {
        do socketUDP.send(ConstantMessages::lookingServers, multicast);
        while (socketUDP.receive(&server_addr)!=ConstantMessages::serverHello);
    } catch (SocketException& e) {
        if (errno==EAGAIN || errno==EWOULDBLOCK) goto search_server;
        throw e;
    }
    Log::info("Server found - "+server_addr.toString());
    socketTCP.connect(server_addr);
    Log::info("connected to the server - "+server_addr.toString());
    const struct sigaction act = {
            {[](int){}},
            {},
            0,
            {}
    };
    sigaction(SIGINT, &act, nullptr);
    signal(SIGPIPE, SIG_IGN);
    std::thread receiver(&Client::handleReceive, this);
    socketTCP.send(CM::getMapList);
    socketTCP.send(CM::getGameList);
    socketTCP.send(CM::postGameCreate+"\n{\"name\":\"game1\",\"mapId\":0}");
    socketTCP.send(CM::postGameStart);
    Log::info("wait for move player");
    std::unique_lock<std::mutex> lock(mutex);
    cv_gameStarted.wait(lock);
    lock.unlock();
    if (!gameStarted) goto quit;
    Log::info("go move player");
    socketTCP.send(CM::postPlayerMove+"\n{\"move\":\"up\"}");
    std::this_thread::sleep_for(timeMove);
    socketTCP.send(CM::postPlayerMove+"\n{\"move\":\"right\"}");
    std::this_thread::sleep_for(timeMove);
    socketTCP.send(CM::postPlayerMove+"\n{\"move\":\"down\"}");
    std::this_thread::sleep_for(timeMove);
    socketTCP.send(CM::postPlayerMove+"\n{\"move\":\"left\"}");
    socketTCP.send(CM::postAttackBomb+"\n{" R"("type":"remote"})");
    socketTCP.send(CM::postAttackRemoteGo);
    socketTCP.send(CM::postAttackBomb+"\n{" R"("type":"classic"})");
    std::this_thread::sleep_for(std::chrono::seconds(1+Config::getDetonationTime()));
quit:
    Log::info("shutdown");
    pthread_kill(receiver.native_handle(), SIGINT);
    receiver.join();
}

void Client::handleReceive() {
    Utils::threadName = "handleReceive";
    Log::info("start");
    std::string msg;
    try {
        for (;;) {
            try {
                std::string msg_received = socketTCP.receive();
                if (msg_received.empty()) {
                    Log::info("communication with server, probably stopped.");
                    break;
                }
                std::istringstream stream(msg_received);
                while (std::getline(stream, msg, Config::getMsgSeparator())) {
                    if (msg == CM::postGameGo) gameStarted=true, cv_gameStarted.notify_one();
                    std::cout << msg << std::endl;
                }
            } catch (SocketException& e) {
                if (errno==EINTR) {
                    Log::info("stop received");
                    break;
                }
                throw e;
            }
        }
    } catch (std::exception& e) {
        Log::error(e.what());
        Log::info("terminated abnormally");
    }
    cv_gameStarted.notify_one();
    Log::info("terminate");
}

Client::~Client() = default;
