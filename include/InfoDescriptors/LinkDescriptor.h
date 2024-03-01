#ifndef LINKDESCRIPTOR_H
#define LINKDESCRIPTOR_H

#include <iostream>
#include <string>

/**
 * @brief The LinkDescriptor class represents a descriptor for a network link.
 */
class LinkDescriptor {
public:
    /**
     * @brief Enumeration for protocol types.
     */
    enum class ProtocolType {
        FTP,        /**< FTP protocol type */
        HTTP,       /**< HTTP protocol type */
        Undefined   /**< Undefined protocol type */
    };

    /**
     * @brief Default constructor.
     * Initializes the LinkDescriptor with an undefined protocol type and an empty server name.
     */
    LinkDescriptor();

    /**
     * @brief Constructor with protocol type and server name.
     * @param type The protocol type.
     * @param server The server name.
     */
    LinkDescriptor(ProtocolType type, const std::string& server);

    /**
     * @brief Copy constructor.
     * @param other The other LinkDescriptor object to copy from.
     */
    LinkDescriptor(const LinkDescriptor& other);

    /**
     * @brief Move constructor.
     * @param other The other LinkDescriptor object to move from.
     */
    LinkDescriptor(LinkDescriptor&& other) noexcept;

    /**
     * @brief Copy assignment operator.
     * @param other The other LinkDescriptor object to copy from.
     * @return A reference to the assigned LinkDescriptor object.
     */
    LinkDescriptor& operator=(const LinkDescriptor& other);

    /**
     * @brief Move assignment operator.
     * @param other The other LinkDescriptor object to move from.
     * @return A reference to the moved LinkDescriptor object.
     */
    LinkDescriptor& operator=(LinkDescriptor&& other) noexcept;

    /**
     * @brief Get the protocol type.
     * @return The protocol type.
     */
    ProtocolType getProtocol() const;

    /**
     * @brief Get the server name.
     * @return The server name.
     */
    std::string getServerName() const;

private:
    ProtocolType protocol;      /**< The protocol type. */
    std::string serverName;     /**< The server name. */
};

#endif // LINKDESCRIPTOR_H
