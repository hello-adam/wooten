#pragma once

#include "sessionprotocol.h"
#include "mixer.h"
#include "config.h"
#include "connection.h"

#include <Bela.h>
#include <libraries/Gui/Gui.h>
#include <mutex>
#include <atomic>
#include <vector>
#include <list>
#include <memory>

class WootBase;

class Session {
public:
    Session();

    int setup(WootBase *wootBase);

    void start(std::string sessId = "");
    void stop();
    void processFrame(BelaContext *context, Mixer &mixer);
    void writeToGuiBuffer();

    bool isActive() const;
    std::string sessionId() const;

    static void manageSession(void*);
    static void rxUdp(void*);
private:
    void manageSessionImpl();
    void rxUdpImpl();

    std::mutex m_connMutex;
    std::list<std::unique_ptr<Connection>> m_connections;
    std::vector<unsigned int> m_guiBuffIds;

    std::string m_sessId;
    int m_rxSock;
    std::atomic<bool> m_udpActive;
    std::atomic<bool> m_managerActive;
    std::atomic<bool> m_terminate;

    AuxiliaryTask m_manageSessionTask;
    AuxiliaryTask m_rxUdpTask;

    JoinedData m_myJoinedData;

    WootBase *m_wootBase;
};