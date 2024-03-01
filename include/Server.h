#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include <future>
#include <algorithm>
#include <numeric>
#include "TransmissionTable.h"
#include "Funcs.h"

/**
 * @brief A class representing a server.
 *
 * This class provides functionality to manage server properties
 * and manipulate packets stored in the transmission table.
 */
class Server {
private:
    std::string serverName; /**< The name of the server. */
    std::string serverAddress; /**< The IP address of the server. */
    TransmissionTable transmissionTable; /**< The transmission table for storing packets. */

public:
    /**
     * @brief Default constructor.
     */
    Server() = default;

    /**
     * @brief Constructs a server with the specified name and IP address.
     *
     * @param name The name of the server.
     * @param address The IP address of the server.
     */
    Server(const std::string& name, const std::string& address);

    /**
     * @brief Gets the name of the server.
     *
     * @return The name of the server.
     */
    std::string getServerName() const;

    /**
     * @brief Gets the IP address of the server.
     *
     * @return The IP address of the server.
     */
    std::string getServerAddress() const;

    /**
     * @brief Sets the name of the server.
     *
     * @param newServerName The new name of the server.
     */
    void setName(const std::string& newServerName);

    /**
     * @brief Sets the IP address of the server.
     *
     * @param newServerAddress The new IP address of the server.
     * @throw std::invalid_argument If the IP address format is invalid.
     */
    void setIPAddress(const std::string& newServerAddress);

    /**
     * @brief Adds a packet to the transmission table.
     *
     * @param packet The packet to be added.
     */
    bool addPacketToTransmissionTable(const std::shared_ptr<Packet>& packet);

    /**
     * @brief Finds a packet in the transmission table based on priority.
     *
     * The packet type is checked in the order: HyperText, File, Mail.
     *
     * @param ip The receiver IP address.
     * @return A shared pointer to the found packet, or nullptr if not found.
     */
    std::shared_ptr<Packet> findByPriority(const std::string& ip) const;

    /**
     * @brief Erases a packet from the transmission table based on priority.
     *
     * The packet type is checked in the order: HyperText, File, Mail.
     *
     * @param ip The receiver IP address.
     * @return true if the erasure was successful, false otherwise.
     */
    bool eraseByPriority(const std::string& ip);

    /**
     * @brief Displays sender information from the transmission table.
     *
     * @param os The output stream.
     * @return The modified output stream.
     */
    std::ostream& showSendersInfo(std::ostream& os) const;

    /**
     * @brief Calculates the percentage of packets of the specified type in the transmission table.
     *
     * @param type The packet type.
     * @return The percentage of packets of the specified type.
     */
    float calculatePacketTypePercentage(const std::string& type) const;

    /**
     * @brief Calculates the percentage of packets of the specified type in the transmission table using multiple threads.
     *
     * @param type The packet type.
     * @return The percentage of packets of the specified type.
     */
    float calculatePacketTypePercentageMT(const std::string& type) const;

    /**
     * @brief Overloaded stream insertion operator to output the server details.
     *
     * This operator outputs the server's name followed by a dash and its address,
     * and then outputs the transmission table using another overloaded operator.
     *
     * @param os The output stream.
     * @param server The server object to output.
     * @return The modified output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Server& server);

};

#endif // SERVER_H

