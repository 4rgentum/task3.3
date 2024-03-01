#include "../../include/Packets/Packet.h"

Packet::Packet(const std::string& sender, const std::string& receiver, const std::string& msg)
        : senderAddress(sender), receiverAddress(receiver), message(msg) {}

std::string Packet::getSenderAddress() const {
    return senderAddress;
}

std::string Packet::getReceiverAddress() const {
    return receiverAddress;
}

const MessageDescriptor& Packet::getMessageDescriptor() const {
    return message;
}

const std::string Packet::getMessage() const {
    return message.getMessage();
}

void Packet::setSenderAddress(const std::string& newSenderAddress) {
    senderAddress = newSenderAddress;
}

void Packet::setReceiverAddress(const std::string& newReceiverAddress) {
    receiverAddress = newReceiverAddress;
}

void Packet::setMessage(const std::string& msg) {
    message.changeMessage(msg);
}
