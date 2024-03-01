#ifndef TRANSMISSIONTABLE_H
#define TRANSMISSIONTABLE_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>
#include <sstream>
#include "Packets/FilePacket.h"
#include "Packets/MailPacket.h"
#include "../unordered_map/unordered_map.h"

/**
 * @brief A class representing a transmission table for storing packets.
 *
 * This class provides functionality to insert, find, and erase packets
 * based on the receiver IP address and packet type.
 */
class TransmissionTable {
public:
    /**
     * @brief Default constructor.
     */
    TransmissionTable() = default;

    /**
     * @brief Inserts a packet into the transmission table.
     *
     * @param packet The packet to be inserted.
     * @return true if the insertion was successful, false otherwise.
     */
    bool insert(const std::shared_ptr<Packet>& packet);

    /**
     * @brief Finds a packet in the transmission table based on the receiver IP address and packet type.
     *
     * @param ip The receiver IP address.
     * @param type The packet type.
     * @return A shared pointer to the found packet, or nullptr if not found.
     */
    std::shared_ptr<Packet> find(const std::string& ip, const std::string& type) const;

    /**
     * @brief Erases a packet from the transmission table based on the receiver IP address and packet type.
     *
     * @param ip The receiver IP address.
     * @param type The packet type.
     * @return true if the erasure was successful, false otherwise.
     */
    bool erase(const std::string& ip, const std::string& type);

    /**
     * @brief Checks if the transmission table is empty.
     *
     * @return true if the transmission table is empty, false otherwise.
     */
    bool empty() const;

    /**
     * @brief Gets the size of the transmission table.
     *
     * @return The size of the transmission table.
     */
    std::size_t size() const;

    /**
     * @brief Checks if the transmission table contains a packet based on the receiver IP address and packet type.
     *
     * @param ip The receiver IP address.
     * @param type The packet type.
     * @return true if the transmission table contains the packet, false otherwise.
     */
    bool contains(const std::string& ip, const std::string& type) const;

    /**
     * @brief Accesses a packet in the transmission table using the receiver IP address as the key.
     *
     * @param key The receiver IP address.
     * @return A reference to the packet associated with the key.
     */
    std::shared_ptr<Packet>& operator[](std::pair<const std::string&, const std::string&> key_and_value);

    /**
     * @brief Accesses a packet in the transmission table using the receiver IP address as the key.
     *
     * @param key The receiver IP address.
     * @return A const reference to the packet associated with the key.
     */
    const std::shared_ptr<Packet>& operator[](std::pair<const std::string&, const std::string&>key_and_value) const;

    /**
     * @brief Overloaded stream insertion operator to print the contents of the transmission table.
     *
     * @param os The output stream.
     * @param table The transmission table to be printed.
     * @return The modified output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const TransmissionTable& table);

    /**
     * @brief Returns an iterator to the beginning of the transmission table.
     *
     * @return An iterator to the beginning.
     */
    Unordered_map<std::string, std::shared_ptr<Packet>>::iterator begin();

    /**
     * @brief Returns a const iterator to the beginning of the transmission table.
     *
     * @return A const iterator to the beginning.
     */
    Unordered_map<std::string, std::shared_ptr<Packet>>::const_iterator begin() const;

    /**
     * @brief Returns an iterator to the end of the transmission table.
     *
     * @return An iterator to the end.
     */
    Unordered_map<std::string, std::shared_ptr<Packet>>::iterator end();

    /**
     * @brief Returns a const iterator to the end of the transmission table.
     *
     * @return A const iterator to the end.
     */
    Unordered_map<std::string, std::shared_ptr<Packet>>::const_iterator end() const;

private:
    Unordered_map<std::string, std::shared_ptr<Packet>> packets; /**< The underlying unordered map storing packets. */
};

#endif // TRANSMISSIONTABLE_H
