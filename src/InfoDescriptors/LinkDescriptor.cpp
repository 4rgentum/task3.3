#include "../../include/InfoDescriptors/LinkDescriptor.h"

LinkDescriptor::LinkDescriptor() : protocol(ProtocolType::Undefined), serverName("") {}

LinkDescriptor::LinkDescriptor(ProtocolType type, const std::string& server)
        : protocol(type), serverName(server) {}

LinkDescriptor::LinkDescriptor(const LinkDescriptor& other)
        : protocol(other.protocol), serverName(other.serverName) {}

LinkDescriptor::LinkDescriptor(LinkDescriptor&& other) noexcept
        : protocol(std::move(other.protocol)), serverName(std::move(other.serverName)) {}

LinkDescriptor& LinkDescriptor::operator=(const LinkDescriptor& other) {
    if (this != &other) {
        protocol = other.protocol;
        serverName = other.serverName;
    }
    return *this;
}

LinkDescriptor& LinkDescriptor::operator=(LinkDescriptor&& other) noexcept {
    if (this != &other) {
        protocol = std::move(other.protocol);
        serverName = std::move(other.serverName);
    }
    return *this;
}

LinkDescriptor::ProtocolType LinkDescriptor::getProtocol() const {
    return protocol;
}

std::string LinkDescriptor::getServerName() const {
    return serverName;
}
