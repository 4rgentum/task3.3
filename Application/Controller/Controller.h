#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../Visual/Visual.h"
#include "../../include/Server.h"
#include "../../include/Funcs.h"
#include <iostream>
#include <string>

/**
 * @brief A class representing the controller for managing server operations.
 *
 * This class encapsulates the functionality to interact with the server,
 * including adding and selecting packets, displaying information, and calculating percentages.
 */
class Controller {
private:
    Visual visual; /**< The visual interface for displaying information. */
    Server server; /**< The server to be managed by the controller. */

public:
    /**
     * @brief Constructs a controller with the specified server name and address.
     *
     * @param name The name of the server.
     * @param address The IP address of the server.
     */
    Controller(const std::string& name, const std::string& address);

    /**
     * @brief Runs the main loop of the controller.
     *
     * This method displays the menu and processes user input until the user chooses to exit.
     */
    void run();

private:
    /**
     * @brief Gets the user's choice from the menu.
     *
     * @return The user's choice.
     */
    int getChoice();

    /**
     * @brief Adds a packet to the transmission table.
     */
    void addPacket();

    /**
     * @brief Selects a packet from the transmission table based on the receiver's IP address.
     */
    void selectPacket();

    /**
     * @brief Displays information about senders in the transmission table.
     */
    void showSendersInfo();

    /**
     * @brief Calculates the percentage of packets of a specific type in the transmission table.
     */
    void calculatePacketTypePercentage();

    /**
     * @brief Removes a packet from the transmission table based on priority.
     */
    void removePacket();

    /**
     * @brief Displays all packets in the transmission table.
     */
    void displayAllPackets();

    /**
     * @brief Gets the code type for a packet.
     *
     * @return The code type.
     */
    Data::CodeType getCodeType() const;

    /**
     * @brief Gets the information type for a packet.
     *
     * @return The information type.
     */
    Data::InfoType getInfoType() const;
};

#endif //CONTROLLER_H
