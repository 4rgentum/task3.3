#include "../../include/InfoDescriptors/MessageDescriptor.h"

MessageDescriptor::MessageDescriptor(const std::string& msg)
        : length(msg.size()), message(std::make_shared<std::string>(msg)) {}

MessageDescriptor::MessageDescriptor()
        : length(0), message(nullptr) {}

int MessageDescriptor::getLength() const { return length; }

std::string MessageDescriptor::getMessage() const {
    if(message != nullptr) return *message;
    else return "Message not available";
}

std::shared_ptr<std::string> MessageDescriptor::getMessagePtr() const { return message; }

void MessageDescriptor::changeMessage(const std::string& msg) {
    auto newMessage = std::make_shared<std::string>(msg);
    message = newMessage;
    length = msg.size();
}
