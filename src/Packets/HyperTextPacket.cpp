#include "../../include/Packets/HyperTextPacket.h"

HyperTextPacket::HyperTextPacket(const std::string& sender, const std::string& receiver, Data::CodeType code, Data::InfoType info, const std::string& msg)
        : Packet(sender, receiver, msg), data(code, info), numLinks(0) {}

HyperTextPacket::HyperTextPacket(const HyperTextPacket& other)
        : Packet(other), data(other.data), numLinks(other.numLinks), links(other.links) {}

HyperTextPacket::HyperTextPacket(HyperTextPacket&& other) noexcept
        : Packet(std::move(other)), data(std::move(other.data)), numLinks(other.numLinks), links(std::move(other.links)) {}

HyperTextPacket& HyperTextPacket::operator=(const HyperTextPacket& other) {
    if (this != &other) {
        Packet::operator=(other);
        data = other.data;
        numLinks = other.numLinks;
        links = other.links;
    }
    return *this;
}

HyperTextPacket& HyperTextPacket::operator=(HyperTextPacket&& other) noexcept {
    if (this != &other) {
        Packet::operator=(std::move(other));
        data = std::move(other.data);
        numLinks = other.numLinks;
        links = std::move(other.links);
    }
    return *this;
}

std::string HyperTextPacket::getType() const {
    return "HT";
}

std::string HyperTextPacket::info() const {
    std::string result = "HyperText Packet: Sender Address - " + getSenderAddress() + ", Receiver Address - " + getReceiverAddress() + ", Code Type - " + getCodeTypeString(data.getCodeType()) + ", Info Type - " + getInfoTypeString(data.getInfoType()) + ", Message - " + message.getMessage() + ", Number of Links - " + std::to_string(numLinks) + "\nLinks:\n";
    for (const auto& link : links) {
        result += "\t- Protocol: " + getProtocolTypeString(link.getProtocol()) + ", Server Name: " + link.getServerName() + "\n";
    }
    return result;
}

Data::CodeType HyperTextPacket::getCodeType() const {
    return data.getCodeType();
}

Data::InfoType HyperTextPacket::getInfoType() const {
    return data.getInfoType();
}

void HyperTextPacket::setCodeType(Data::CodeType codeType) {
    data.setCodeType(codeType);
}

void HyperTextPacket::setInfoType(Data::InfoType infoType) {
    data.setInfoType(infoType);
}

std::string HyperTextPacket::getMessage() const {
    return message.getMessage();
}

void HyperTextPacket::setMessage(const std::string& msg) {
    message.changeMessage(msg);
}

int HyperTextPacket::getNumLinks() const {
    return numLinks;
}

const std::vector<LinkDescriptor>& HyperTextPacket::getLinks() const {
    return links;
}

void HyperTextPacket::setLinks(const std::vector<LinkDescriptor>& lnks) {
    links = lnks;
    numLinks = lnks.size();
}

void HyperTextPacket::addLink(const LinkDescriptor& link) {
    links.push_back(link);
    numLinks++;
}

LinkDescriptor& HyperTextPacket::operator[](size_t index) {
    if (index >= links.size()) {
        throw std::out_of_range("Index out of range");
    }
    return links[index];
}

const LinkDescriptor& HyperTextPacket::operator[](size_t index) const {
    if (index >= links.size()) {
        throw std::out_of_range("Index out of range");
    }
    return links[index];
}

std::string HyperTextPacket::getCodeTypeString(Data::CodeType codeType) const {
    switch (codeType) {
        case Data::CodeType::ASCII:
            return "ASCII";
        case Data::CodeType::BIN:
            return "BIN";
        default:
            return "Undefined";
    }
}

std::string HyperTextPacket::getInfoTypeString(Data::InfoType infoType) const {
    switch (infoType) {
        case Data::InfoType::Control:
            return "Control";
        case Data::InfoType::Data:
            return "Data";
        default:
            return "Undefined";
    }
}

std::string HyperTextPacket::getProtocolTypeString(LinkDescriptor::ProtocolType protocolType) const {
    switch (protocolType) {
        case LinkDescriptor::ProtocolType::FTP:
            return "FTP";
        case LinkDescriptor::ProtocolType::HTTP:
            return "HTTP";
        default:
            return "Undefined";
    }
}
