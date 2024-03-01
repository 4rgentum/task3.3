#ifndef PACKET_H
#define PACKET_H

#include <iostream>
#include <string>
#include "../InfoDescriptors/MessageDescriptor.h"

/**
 * @brief The base class representing a network packet.
 */
class Packet {
protected:
    std::string senderAddress; /**< The sender's address. */
    std::string receiverAddress; /**< The receiver's address. */
    MessageDescriptor message; /**< The message descriptor. */

public:
    /**
     * @brief Default constructor for Packet class.
     */
    Packet() = default;

    /**
     * @brief Parameterized constructor for Packet class.
     * @param sender The sender's address.
     * @param receiver The receiver's address.
     * @param msg The message content.
     */
    Packet(const std::string& sender, const std::string& receiver, const std::string& msg);

    /**
     * @brief Virtual destructor for Packet class.
     */
    virtual ~Packet() {}

    /**
     * @brief Get the sender's address.
     * @return The sender's address.
     */
    std::string getSenderAddress() const;

    /**
     * @brief Get the receiver's address.
     * @return The receiver's address.
     */
    std::string getReceiverAddress() const;

    /**
     * @brief Get the message descriptor.
     * @return The message descriptor.
     */
    const MessageDescriptor& getMessageDescriptor() const;

    /**
     * @brief Get the message content.
     * @return The message content.
     */
    const std::string getMessage() const;

    /**
     * @brief Set the sender's address.
     * @param newSenderAddress The new sender's address.
     */
    void setSenderAddress(const std::string& newSenderAddress);

    /**
     * @brief Set the receiver's address.
     * @param newReceiverAddress The new receiver's address.
     */
    void setReceiverAddress(const std::string& newReceiverAddress);

    /**
     * @brief Set the message content.
     * @param msg The new message content.
     */
    void setMessage(const std::string& msg);

    /**
     * @brief Get the type of the packet.
     * @return The type of the packet.
     */
    virtual std::string getType() const = 0;

    /**
     * @brief Get information about the packet.
     * @return Information about the packet.
     */
    virtual std::string info() const = 0;

    /**
     * @brief Overloaded insertion operator to print information about the packet.
     * @param os The output stream.
     * @param packet The packet to print.
     * @return The output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Packet& packet);
};

/**
 * @brief Overloaded insertion operator to print information about the packet.
 * @param os The output stream.
 * @param packet The packet to print.
 * @return The output stream.
 */
std::ostream& operator<<(std::ostream& os, const Packet& packet);

#endif // PACKET_H
