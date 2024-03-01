#include "Visual.h"

Visual::Visual(std::ostream& os) : outputStream(os) {}

std::ostream& Visual::getOutputStream() const {
    return outputStream;
}

void Visual::displayMenu() const {
    outputStream << "===== Server Menu =====" << std::endl;
    outputStream << "1. Add a new packet to the transmission table." << std::endl;
    outputStream << "2. Select a packet from the transmission table by receiver IP address with priority." << std::endl;
    outputStream << "3. Show information about all senders in the transmission table." << std::endl;
    outputStream << "4. Calculate the percentage of incoming packets of each type." << std::endl;
    outputStream << "5. Remove a packet from the transmission table by priority." << std::endl;
    outputStream << "6. Display all packets in the transmission table." << std::endl;
    outputStream << "7. Exit." << std::endl;
}

void Visual::displayIpAddressPrompt() const {
    outputStream << "Enter the receiver IP address: ";
}

void Visual::displayPacketTypeMenu() const {
    outputStream << "Select packet type:" << std::endl;
    outputStream << "1. HyperText" << std::endl;
    outputStream << "2. File" << std::endl;
    outputStream << "3. Mail" << std::endl;
}

void Visual::displayInvalidChoiceMessage() const {
    outputStream << "Invalid choice! Defaulting to HyperText." << std::endl;
}

void Visual::displayExitMessage() const {
    outputStream << "Exiting the server program." << std::endl;
}

void Visual::displayPacketAddedMessage() const {
    outputStream << "New packet added to the transmission table." << std::endl;
}

void Visual::displayPacketUnAddedMessage() const {
    outputStream << "New packet cannot be added to the transmission table." << std::endl;
}

void Visual::displayPacketSelectedMessage(const std::string& ip) const {
    outputStream << "Packet selected for IP address " << ip << "." << std::endl;
}

void Visual::displaySendersInfoHeader() const {
    outputStream << "===== Senders Information =====" << std::endl;
}

void Visual::displayPercentageCalculationHeader() const {
    outputStream << "===== Packet Type Percentage =====" << std::endl;
}

void Visual::displayInvalidIpAddressMessage() const {
    outputStream << "Invalid IP address format. Please try again." << std::endl;
}

void Visual::displayPacketRemovedMessage(const std::string& ip) const {
    outputStream << "Packet removed from the transmission table for IP address " << ip << "." << std::endl;
}

void Visual::displayAllPacketsHeader() const {
    outputStream << "===== All Packets in Transmission Table =====" << std::endl;
}

void Visual::displayCodeTypeMenu() const {
    outputStream << "Select code type:" << std::endl;
    outputStream << "1. ASCII" << std::endl;
    outputStream << "2. BIN" << std::endl;
}

void Visual::displayInfoTypeMenu() const {
    outputStream << "Select information type:" << std::endl;
    outputStream << "1. Control" << std::endl;
    outputStream << "2. Data" << std::endl;
}

void Visual::displayMessagePrompt() const {
    outputStream << "Enter the message: ";
}

void Visual::displayUsernamePrompt() const {
    outputStream << "Enter username: ";
}

void Visual::displayThreadModeMenu() const {
    outputStream << "===== Thread Mode Menu =====" << std::endl;
    outputStream << "Select thread mode:" << std::endl;
    outputStream << "1. Single-threaded" << std::endl;
    outputStream << "2. Multi-threaded" << std::endl;
    outputStream << "Enter your choice: ";
}

void Visual::resultPercent(const std::string& type, float percent) const {
    outputStream << "The percentage of " << type << " packets is: " << percent << "%" << std::endl;
    outputStream << "(HT - Hypertext, F - File, M - Mail)" << std::endl;
}
