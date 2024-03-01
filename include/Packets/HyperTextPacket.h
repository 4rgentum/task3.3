#ifndef HYPERTEXTPACKET_H
#define HYPERTEXTPACKET_H

#include "Packet.h"
#include "../InfoDescriptors/Data.h"
#include "../InfoDescriptors/MessageDescriptor.h"
#include "../InfoDescriptors/LinkDescriptor.h"
#include <exception>
#include <vector>

/**
 * @brief Class representing a hypertext packet, a type of network packet.
 */
class HyperTextPacket : public Packet {
private:
    Data data; /**< Data information associated with the hypertext packet. */
    int numLinks = 0; /**< Number of links in the hypertext packet. */
    std::vector<LinkDescriptor> links; /**< List of link descriptors in the hypertext packet. */

public:
    /**
     * @brief Parameterized constructor for HyperTextPacket class.
     * @param sender The sender's address.
     * @param receiver The receiver's address.
     * @param code The code type associated with the hypertext packet.
     * @param info The info type associated with the hypertext packet.
     * @param msg The message content.
     */
    HyperTextPacket(const std::string& sender, const std::string& receiver, Data::CodeType code, Data::InfoType info, const std::string& msg);

    /**
     * @brief Default constructor for HyperTextPacket class.
     */
    HyperTextPacket() = default;

    /**
     * @brief Copy constructor for HyperTextPacket class.
     * @param other The hypertext packet to copy from.
     */
    HyperTextPacket(const HyperTextPacket& other);

    /**
     * @brief Move constructor for HyperTextPacket class.
     * @param other The hypertext packet to move from.
     */
    HyperTextPacket(HyperTextPacket&& other) noexcept;

    /**
     * @brief Copy assignment operator for HyperTextPacket class.
     * @param other The hypertext packet to copy from.
     * @return A reference to the assigned hypertext packet.
     */
    HyperTextPacket& operator=(const HyperTextPacket& other);

    /**
     * @brief Move assignment operator for HyperTextPacket class.
     * @param other The hypertext packet to move from.
     * @return A reference to the assigned hypertext packet.
     */
    HyperTextPacket& operator=(HyperTextPacket&& other) noexcept;

    /**
     * @brief Get the type of the packet.
     * @return The type of the packet.
     */
    std::string getType() const override;

    /**
     * @brief Get information about the hypertext packet.
     * @return Information about the hypertext packet.
     */
    std::string info() const override;

    /**
     * @brief Get the code type associated with the hypertext packet.
     * @return The code type associated with the hypertext packet.
     */
    Data::CodeType getCodeType() const;

    /**
     * @brief Get the info type associated with the hypertext packet.
     * @return The info type associated with the hypertext packet.
     */
    Data::InfoType getInfoType() const;

    /**
     * @brief Set the code type associated with the hypertext packet.
     * @param codeType The new code type to set.
     */
    void setCodeType(Data::CodeType codeType);

    /**
     * @brief Set the info type associated with the hypertext packet.
     * @param infoType The new info type to set.
     */
    void setInfoType(Data::InfoType infoType);

    /**
     * @brief Get the message content of the hypertext packet.
     * @return The message content of the hypertext packet.
     */
    std::string getMessage() const;

    /**
     * @brief Set the message content of the hypertext packet.
     * @param msg The new message content to set.
     */
    void setMessage(const std::string& msg);

    /**
     * @brief Get the number of links in the hypertext packet.
     * @return The number of links in the hypertext packet.
     */
    int getNumLinks() const;

    /**
     * @brief Get the list of link descriptors in the hypertext packet.
     * @return The list of link descriptors in the hypertext packet.
     */
    const std::vector<LinkDescriptor>& getLinks() const;

    /**
     * @brief Set the list of link descriptors in the hypertext packet.
     * @param lnks The new list of link descriptors to set.
     */
    void setLinks(const std::vector<LinkDescriptor>& lnks);

    /**
     * @brief Add a link descriptor to the hypertext packet.
     * @param link The link descriptor to add.
     */
    void addLink(const LinkDescriptor& link);

    /**
     * @brief Overloaded subscript operator to access links by index.
     * @param index The index of the link to access.
     * @return The link descriptor at the specified index.
     */
    LinkDescriptor& operator[](size_t index);

    /**
     * @brief Overloaded const subscript operator to access links by index.
     * @param index The index of the link to access.
     * @return The link descriptor at the specified index.
     */
    const LinkDescriptor& operator[](size_t index) const;

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

    /**
     * @brief Get the string representation of the protocol type.
     * @param protocolType The protocol type to convert.
     * @return The string representation of the protocol type.
     */
    std::string getProtocolTypeString(LinkDescriptor::ProtocolType protocolType) const;
};

#endif //HYPERTEXTPACKET_H
