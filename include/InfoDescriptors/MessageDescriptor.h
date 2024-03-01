#ifndef MESSAGEDESCRIPTOR_H
#define MESSAGEDESCRIPTOR_H

#include <iostream>
#include <string>
#include <memory>

/**
 * @brief Class for storing message descriptors.
 */
class MessageDescriptor {
private:
    int length; /**< Length of the message. */
    std::shared_ptr<std::string> message; /**< Pointer to the message. */

public:
    /**
     * @brief Constructor of the class.
     * @param msg The string containing the message.
     */
    explicit MessageDescriptor(const std::string& msg);

    /**
     * @brief Default constructor of the class.
     */
    MessageDescriptor();

    /**
     * @brief Copy constructor.
     */
    MessageDescriptor(const MessageDescriptor& other) = default;

    /**
     * @brief Move constructor.
     */
    MessageDescriptor(MessageDescriptor&& other) noexcept = default;

    /**
     * @brief Copy assignment operator.
     */
    MessageDescriptor& operator=(const MessageDescriptor& other) = default;

    /**
     * @brief Move assignment operator.
     */
    MessageDescriptor& operator=(MessageDescriptor&& other) noexcept = default;

    /**
     * @brief Get the length of the message.
     * @return The length of the message.
     */
    int getLength() const;

    /**
     * @brief Get the message as a string.
     * @return The message as a string.
     */
    std::string getMessage() const;

    /**
     * @brief Get the message as a shared pointer.
     * @return The message as a shared pointer.
     */
    std::shared_ptr<std::string> getMessagePtr() const;

    /**
     * @brief Change the message to a new one.
     * @param msg The new message.
     */
    void changeMessage(const std::string& msg);
};

#endif // MESSAGEDESCRIPTOR_H
