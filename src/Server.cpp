#include "../include/Server.h"

Server::Server(const std::string& name, const std::string& address)
        : serverName(name), serverAddress(address) {}

std::string Server::getServerName() const {
    return serverName;
}

std::string Server::getServerAddress() const {
    return serverAddress;
}

void Server::setName(const std::string& newServerName) {
    serverName = newServerName;
}

void Server::setIPAddress(const std::string& newServerAddress) {
    if (validation(newServerAddress)) {
        serverAddress = newServerAddress;
    } else {
        throw std::invalid_argument("Error: Invalid IP address format.");
    }
}

bool Server::addPacketToTransmissionTable(const std::shared_ptr<Packet>& packet) {
    return transmissionTable.insert(packet);
}

std::shared_ptr<Packet> Server::findByPriority(const std::string& ip) const {
    std::shared_ptr<Packet> packet = nullptr;
    if ((packet = transmissionTable.find(ip, "HT"))) return packet;
    if ((packet = transmissionTable.find(ip, "F"))) return packet;
    if ((packet = transmissionTable.find(ip, "M"))) return packet;
    return nullptr;
}

bool Server::eraseByPriority(const std::string& ip) {
    if (transmissionTable.erase(ip, "HT")) return true;
    if (transmissionTable.erase(ip, "F")) return true;
    if (transmissionTable.erase(ip, "M")) return true;
    return false;
}

std::ostream& Server::showSendersInfo(std::ostream& os) const {
    for (const auto& entry : transmissionTable) {
        os << "Sender Address: " << entry.second->getSenderAddress() << std::endl;
    }
    return os;
}

float Server::calculatePacketTypePercentage(const std::string& type) const {
    int totalPacketsOfType = 0;
    int totalPackets = transmissionTable.size();

    for (const auto& entry : transmissionTable) {
        if (entry.second->getType() == type) {
            totalPacketsOfType++;
        }
    }

    float percentage = (static_cast<float>(totalPacketsOfType) / totalPackets) * 100.0f;
    return percentage;
}

float Server::calculatePacketTypePercentageMT(const std::string& type) const {
    unsigned int numThreads = std::thread::hardware_concurrency();

    std::size_t totalPackets = transmissionTable.size();
    std::size_t packetsPerThread = totalPackets / numThreads;

    auto countPacketsOfType = [type](Unordered_map<std::string, std::shared_ptr<Packet>>::const_iterator begin, Unordered_map<std::string, std::shared_ptr<Packet>>::const_iterator end) {
        int count = 0;
        for (auto it = begin; it != end; ++it) {
            if(it -> second != nullptr) {
                if (it->second->getType() == type) {
                    count++;
                }
            }
        }
        return count;
    };

    std::vector<std::future<int>> futures;
    auto it = transmissionTable.begin();
    for (unsigned int i = 0; i < numThreads; ++i) {
        auto startIt = it;
        std::advance(it, packetsPerThread);
        auto endIt = (i == numThreads - 1) ? transmissionTable.end() : it;
        futures.emplace_back(std::async(std::launch::async, countPacketsOfType, startIt, endIt));
    }

    int totalCount = std::accumulate(futures.begin(), futures.end(), 0, [](int sum, std::future<int>& f) {
        return sum + f.get();
    });

    float percentage = (static_cast<float>(totalCount) / totalPackets) * 100.0f;
    return percentage;
}

std::ostream& operator<<(std::ostream& os, const Server& server) {
    os << server.getServerName() << " - " << server.getServerAddress() << std::endl;
    os << server.transmissionTable;
    return os;
}

