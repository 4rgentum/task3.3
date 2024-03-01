#include "Controller.h"

Controller::Controller(const std::string& name, const std::string& address) : server(name, address) {}

void Controller::run() {
    int choice;
    do {
        visual.displayMenu();
        choice = getChoice();
        switch (choice) {
            case 1:
                addPacket();
                break;
            case 2:
                selectPacket();
                break;
            case 3:
                showSendersInfo();
                break;
            case 4:
                calculatePacketTypePercentage();
                break;
            case 5:
                removePacket();
                break;
            case 6:
                displayAllPackets();
                break;
            case 7:
                visual.displayExitMessage();
                break;
            default:
                visual.displayInvalidChoiceMessage();
                break;
        }
    } while (choice != 7);
}

int Controller::getChoice() {
    return getNum<int>(1, 7);
}

void Controller::addPacket() {
    visual.displayPacketTypeMenu();
    int choice = getNum<int>(1, 3);

    std::string sender = server.getServerAddress();
    std::string receiver;
    visual.displayIpAddressPrompt();
    do {
        receiver = readLine();
        if (!validation(receiver)) {
            visual.displayInvalidIpAddressMessage();
            visual.displayIpAddressPrompt();
        }
    } while (!validation(receiver));

    std::string message;
    bool success;
    switch (choice) {
        case 1: {
            visual.displayCodeTypeMenu();
            Data::CodeType code = getCodeType();
            visual.displayInfoTypeMenu();
            Data::InfoType info = getInfoType();
            visual.displayMessagePrompt();
            message = readLine();
            std::shared_ptr<Packet> packet = std::make_shared<HyperTextPacket>(sender, receiver, code, info, message);
            success = server.addPacketToTransmissionTable(packet);
            break;
        }
        case 2: {
            visual.displayCodeTypeMenu();
            Data::CodeType code = getCodeType();
            visual.displayInfoTypeMenu();
            Data::InfoType info = getInfoType();
            visual.displayMessagePrompt();
            message = readLine();
            std::shared_ptr<Packet> packet = std::make_shared<FilePacket>(sender, receiver, code, info, message);
            success = server.addPacketToTransmissionTable(packet);
            break;
        }
        case 3: {
            visual.displayUsernamePrompt();
            std::string username = readLine();
            visual.displayMessagePrompt();
            message = readLine();
            std::shared_ptr<Packet> packet = std::make_shared<MailPacket>(sender, receiver, username, message);
            success = server.addPacketToTransmissionTable(packet);
            break;
        }
        default:
            break;
    }

    if (success) visual.displayPacketAddedMessage();
    else visual.displayPacketUnAddedMessage();
}

void Controller::selectPacket() {
    visual.displayIpAddressPrompt();
    std::string ip;

    do {
        ip = readLine();
        if (!validation(ip)) {
            visual.displayInvalidIpAddressMessage();
        }
    } while (!validation(ip));

    std::shared_ptr<Packet> selectedPacket = server.findByPriority(ip);
    if (selectedPacket != nullptr) {
        visual.getOutputStream() << selectedPacket -> info();
    } else {
        visual.getOutputStream() << "No packet found for IP address " << ip << "." << std::endl;
    }
}

void Controller::showSendersInfo() {
    visual.displaySendersInfoHeader();
    server.showSendersInfo(visual.getOutputStream());
}

void Controller::calculatePacketTypePercentage() {
    visual.displayPacketTypeMenu();
    int choice = getNum<int>(1, 3);

    std::string packetType;
    switch (choice) {
        case 1:
            packetType = "HT";
            break;
        case 2:
            packetType = "F";
            break;
        case 3:
            packetType = "M";
            break;
        default:
            visual.displayInvalidChoiceMessage();
            packetType = "HT";
            break;
    }

    visual.displayThreadModeMenu();
    choice = getNum<int>(1, 2);

    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();

    float percentage;
    if (choice == 1) {
        percentage = server.calculatePacketTypePercentage(packetType);
    } else {
        percentage = server.calculatePacketTypePercentageMT(packetType);
    }

    std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end_time - start_time;

    visual.resultPercent(packetType, percentage);

    visual.getOutputStream() << "Time taken: " << elapsed_seconds.count() << " seconds" << std::endl;
}

void Controller::removePacket() {
    visual.displayIpAddressPrompt();
    std::string ip;

    do {
        ip = readLine();
        if (!validation(ip)) {
            visual.displayInvalidIpAddressMessage();
        }
    } while (!validation(ip));

    bool removed = server.eraseByPriority(ip);
    if (removed) {
        visual.displayPacketRemovedMessage(ip);
    } else {
        visual.getOutputStream() << "No packet found for IP address " << ip << " or removal failed." << std::endl;
    }
}

void Controller::displayAllPackets() {
    visual.displayAllPacketsHeader();
    visual.getOutputStream() << server;
}

Data::CodeType Controller::getCodeType() const {
    int choice = getNum(1, 2);
    switch (choice) {
        case 1:
            return Data::CodeType::ASCII;
        case 2:
            return Data::CodeType::BIN;
        default:
            return Data::CodeType::Undefined;
    }
}

Data::InfoType Controller::getInfoType() const {
    int choice = getNum(1, 2);
    switch (choice) {
        case 1:
            return Data::InfoType::Control;
        case 2:
            return Data::InfoType::Data;
        default:
            return Data::InfoType::Undefined;
    }
}
