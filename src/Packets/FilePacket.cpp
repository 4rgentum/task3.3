#include "../../include/Packets/FilePacket.h"

FilePacket::FilePacket(const std::string& sender, const std::string& receiver, Data::CodeType code, Data::InfoType info, const std::string& msg)
        : Packet(sender, receiver, msg), data(code, info) {}

FilePacket::FilePacket(const FilePacket& other)
        : Packet(other), data(other.data) {}

FilePacket::FilePacket(FilePacket&& other) noexcept
        : Packet(std::move(other)), data(std::move(other.data)) {}

FilePacket& FilePacket::operator=(const FilePacket& other) {
    if (this != &other) {
        Packet::operator=(other);
        data = other.data;
    }
    return *this;
}

FilePacket& FilePacket::operator=(FilePacket&& other) noexcept {
    if (this != &other) {
        Packet::operator=(std::move(other));
        data = std::move(other.data);
    }
    return *this;
}

std::string FilePacket::getType() const {
    return "F";
}

std::string FilePacket::info() const {
    return "File Packet: Sender Address - " + getSenderAddress() + ", Receiver Address - " + getReceiverAddress() + ", Code Type - " + getCodeTypeString(data.getCodeType()) + ", Info Type - " + getInfoTypeString(data.getInfoType()) + ", Message - " + message.getMessage();
}

HyperTextPacket FilePacket::toHyperTextPacket() const {
    Data::CodeType codeType = getCodeType();
    Data::InfoType infoType = getInfoType();
    HyperTextPacket hyperTextPacket(getSenderAddress(), getReceiverAddress(), codeType, infoType, message.getMessage());
    return hyperTextPacket;
}

Data::CodeType FilePacket::getCodeType() const {
    return data.getCodeType();
}

Data::InfoType FilePacket::getInfoType() const {
    return data.getInfoType();
}

void FilePacket::setCodeType(Data::CodeType codeType) {
    data.setCodeType(codeType);
}

void FilePacket::setInfoType(Data::InfoType infoType) {
    data.setInfoType(infoType);
}

std::string FilePacket::getMessage() const {
    return message.getMessage();
}

void FilePacket::setMessage(const std::string& msg) {
    message.changeMessage(msg);
}

std::string FilePacket::getCodeTypeString(Data::CodeType codeType) const {
    switch (codeType) {
        case Data::CodeType::ASCII:
            return "ASCII";
        case Data::CodeType::BIN:
            return "BIN";
        default:
            return "Undefined";
    }
}

std::string FilePacket::getInfoTypeString(Data::InfoType infoType) const {
    switch (infoType) {
        case Data::InfoType::Control:
            return "Control";
        case Data::InfoType::Data:
            return "Data";
        default:
            return "Undefined";
    }
}
