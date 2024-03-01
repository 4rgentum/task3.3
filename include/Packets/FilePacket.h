#ifndef FILEPACKET_H
#define FILEPACKET_H

#include "Packet.h"
#include "HyperTextPacket.h"
#include "../InfoDescriptors/Data.h"
#include "../InfoDescriptors/MessageDescriptor.h"
#include <exception>

/**
 * @brief Class representing a file packet, a type of network packet.
 */
class FilePacket : public Packet {
private:
    Data data; /**< Data information associated with the file packet. */

public:
    /**
     * @brief Parameterized constructor for FilePacket class.
     * @param sender The sender's address.
     * @param receiver The receiver's address.
     * @param code The code type associated with the file packet.
     * @param info The info type associated with the file packet.
     * @param msg The message content.
     */
    FilePacket(const std::string& sender, const std::string& receiver, Data::CodeType code, Data::InfoType info, const std::string& msg);

    /**
     * @brief Default constructor for FilePacket class.
     */
    FilePacket() = default;

    /**
     * @brief Copy constructor for FilePacket class.
     * @param other The file packet to copy from.
     */
    FilePacket(const FilePacket& other);

    /**
     * @brief Move constructor for FilePacket class.
     * @param other The file packet to move from.
     */
    FilePacket(FilePacket&& other) noexcept;

    /**
     * @brief Copy assignment operator for FilePacket class.
     * @param other The file packet to copy from.
     * @return A reference to the assigned file packet.
     */
    FilePacket& operator=(const FilePacket& other);

    /**
     * @brief Move assignment operator for FilePacket class.
     * @param other The file packet to move from.
     * @return A reference to the assigned file packet.
     */
    FilePacket& operator=(FilePacket&& other) noexcept;

    /**
     * @brief Get the type of the packet.
     * @return The type of the packet.
     */
    std::string getType() const override;

    /**
     * @brief Get information about the file packet.
     * @return Information about the file packet.
     */
    std::string info() const override;

    /**
     * @brief Convert the file packet to a hypertext packet.
     * @return A hypertext packet containing the file packet's information.
     */
    HyperTextPacket toHyperTextPacket() const;

    /**
     * @brief Get the code type associated with the file packet.
     * @return The code type associated with the file packet.
     */
    Data::CodeType getCodeType() const;

    /**
     * @brief Get the info type associated with the file packet.
     * @return The info type associated with the file packet.
     */
    Data::InfoType getInfoType() const;

    /**
     * @brief Set the code type associated with the file packet.
     * @param codeType The new code type to set.
     */
    void setCodeType(Data::CodeType codeType);

    /**
     * @brief Set the info type associated with the file packet.
     * @param infoType The new info type to set.
     */
    void setInfoType(Data::InfoType infoType);

    /**
     * @brief Get the message content of the file packet.
     * @return The message content of the file packet.
     */
    std::string getMessage() const;

    /**
     * @brief Set the message content of the file packet.
     * @param msg The new message content to set.
     */
    void setMessage(const std::string& msg);

private:
    /**
     * @brief Get the string representation of the code type.
     * @param codeType The code type to convert.
     * @return The string representation of the code type.
     */
    std::string getCodeTypeString(Data::CodeType codeType) const;

    /**
     * @brief Get the string representation of the info type.
     * @param infoType The info type to convert.
     * @return The string representation of the info type.
     */
    std::string getInfoTypeString(Data::InfoType infoType) const;
};

#endif // FILEPACKET_H
