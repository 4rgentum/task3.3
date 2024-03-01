#ifndef MAILPACKET_H
#define MAILPACKET_H

#include "Packet.h"
#include "FilePacket.h"
#include <exception>
#include "../InfoDescriptors/MessageDescriptor.h"

/**
 * @brief Class representing a mail packet, a type of network packet.
 */
class MailPacket : public Packet {
private:
    std::string username; /**< The username associated with the mail packet. */

public:
    /**
     * @brief Parameterized constructor for MailPacket class.
     * @param sender The sender's address.
     * @param receiver The receiver's address.
     * @param user The username associated with the mail packet.
     * @param msg The message content.
     * @throw std::invalid_argument if the username exceeds 20 characters.
     */
    MailPacket(const std::string& sender, const std::string& receiver, const std::string& user, const std::string& msg);

    /**
     * @brief Default constructor for MailPacket class.
     */
    MailPacket() = default;

    /**
     * @brief Copy constructor for MailPacket class.
     * @param other The mail packet to copy from.
     */
    MailPacket(const MailPacket& other);

    /**
     * @brief Move constructor for MailPacket class.
     * @param other The mail packet to move from.
     */
    MailPacket(MailPacket&& other) noexcept;

    /**
     * @brief Copy assignment operator for MailPacket class.
     * @param other The mail packet to copy from.
     * @return A reference to the assigned mail packet.
     */
    MailPacket& operator=(const MailPacket& other);

    /**
     * @brief Move assignment operator for MailPacket class.
     * @param other The mail packet to move from.
     * @return A reference to the assigned mail packet.
     */
    MailPacket& operator=(MailPacket&& other) noexcept;

    /**
     * @brief Get the type of the packet.
     * @return The type of the packet.
     */
    std::string getType() const override;

    /**
     * @brief Get information about the mail packet.
     * @return Information about the mail packet.
     */
    std::string info() const override;

    /**
     * @brief Convert the mail packet to a file packet.
     * @return A file packet containing the mail packet's information.
     */
    FilePacket toFilePacket() const;

    /**
     * @brief Get the username associated with the mail packet.
     * @return The username associated with the mail packet.
     */
    std::string getUsername() const;

    /**
     * @brief Set the username associated with the mail packet.
     * @param newUser The new username to set.
     * @throw std::invalid_argument if the new username exceeds 20 characters.
     */
    void setUsername(const std::string& newUser);

    /**
     * @brief Get the message content of the mail packet.
     * @return The message content of the mail packet.
     */
    std::string getMessage() const;

    /**
     * @brief Set the message content of the mail packet.
     * @param newMsg The new message content to set.
     */
    void setMessage(const std::string& newMsg);
};

#endif // MAILPACKET_H
