#include "../include/TransmissionTable.h"

bool TransmissionTable::insert(const std::shared_ptr<Packet>& packet) {
    std::stringstream ss;
    ss << packet->getReceiverAddress() << packet->getType();
    return packets.insert(std::make_pair(ss.str(), packet)).second;
}

std::shared_ptr<Packet> TransmissionTable::find(const std::string& ip, const std::string& type) const {
    auto it = packets.find(ip + type);
    if (it != packets.end())
        return it->second;
    return nullptr;
}

bool TransmissionTable::erase(const std::string& ip, const std::string& type) {
    return packets.erase(ip + type);
}

bool TransmissionTable::empty() const {
    return packets.empty();
}

std::size_t TransmissionTable::size() const {
    return packets.size();
}

bool TransmissionTable::contains(const std::string& ip, const std::string& type) const {
    return packets.contains(ip + type);
}

std::shared_ptr<Packet>& TransmissionTable::operator[](std::pair<const std::string&, const std::string&> key_and_value) {
    return packets[key_and_value.first + key_and_value.second];
}

const std::shared_ptr<Packet>& TransmissionTable::operator[](std::pair<const std::string&, const std::string&> key_and_value) const {
    auto it = packets.find(key_and_value.first + key_and_value.second);
    if (it != packets.end()) {
        return it->second;
    } else {
        throw std::out_of_range("Key not found in TransmissionTable");
    }
}

std::ostream& operator<<(std::ostream& os, const TransmissionTable& table) {
    for (const auto& it : table.packets) {
        auto ptr = it.second;
        os << ptr -> info() << std::endl;
    }
    return os;
}

Unordered_map<std::string, std::shared_ptr<Packet>>::iterator TransmissionTable::begin() {
    return packets.begin();
}

Unordered_map<std::string, std::shared_ptr<Packet>>::const_iterator TransmissionTable::begin() const {
    return packets.begin();
}

Unordered_map<std::string, std::shared_ptr<Packet>>::iterator TransmissionTable::end() {
    return packets.end();
}

Unordered_map<std::string, std::shared_ptr<Packet>>::const_iterator TransmissionTable::end() const {
    return packets.end();
}
