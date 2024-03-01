#include "../../include/Packets/MailPacket.h"

MailPacket::MailPacket(const std::string& sender, const std::string& receiver, const std::string& user, const std::string& msg)
        : Packet(sender, receiver, msg) {
    if (user.size() > 20) {
        throw std::invalid_argument("Username should not exceed 20 characters");
    } else {
        username = user;
    }
}

MailPacket::MailPacket(const MailPacket& other)
        : Packet(other), username(other.username) {}

MailPacket::MailPacket(MailPacket&& other) noexcept
        : Packet(std::move(other)), username(std::move(other.username)) {}

MailPacket& MailPacket::operator=(const MailPacket& other) {
    if (this != &other) {
        Packet::operator=(other);
        username = other.username;
    }
    return *this;
}

MailPacket& MailPacket::operator=(MailPacket&& other) noexcept {
    if (this != &other) {
        Packet::operator=(std::move(other));
        username = std::move(other.username);
    }
    return *this;
}

std::string MailPacket::getType() const {
    return "M";
}

std::string MailPacket::info() const {
    return "Mail Packet: Sender Address - " + getSenderAddress() + ", Receiver Address - " + getReceiverAddress() + ", Username - " + username + ", Message - " + message.getMessage();
}

FilePacket MailPacket::toFilePacket() const {
    Data::CodeType codeType = Data::CodeType::Undefined;
    Data::InfoType infoType = Data::InfoType::Undefined;
    FilePacket filePacket(getSenderAddress(), getReceiverAddress(), codeType, infoType, getMessage());
    return filePacket;
}

std::string MailPacket::getUsername() const {
    return username;
}

void MailPacket::setUsername(const std::string& newUser) {
    if (newUser.size() > 20) {
        throw std::invalid_argument("Username should not exceed 20 characters");
    }
    username = newUser;
}

std::string MailPacket::getMessage() const {
    return message.getMessage();
}

void MailPacket::setMessage(const std::string& newMsg) {
    message.changeMessage(newMsg);
}
