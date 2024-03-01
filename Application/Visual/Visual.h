#ifndef VISUAL_H
#define VISUAL_H

#include <iostream>

/**
 * @brief A class representing the visual interface for the server application.
 */
class Visual {
private:
    std::ostream& outputStream; /**< The output stream for displaying messages. */

public:

    /**
     * @brief Getter for the output stream.
     *
     * @return The output stream.
     */
    std::ostream& getOutputStream() const;

    /**
     * @brief Constructs a Visual object with the specified output stream.
     *
     * @param os The output stream.
     */
    explicit Visual(std::ostream& os = std::cout);

    /**
     * @brief Displays the main menu options.
     */
    void displayMenu() const;

    /**
     * @brief Displays a prompt to enter the receiver IP address.
     */
    void displayIpAddressPrompt() const;

    /**
     * @brief Displays the menu for selecting packet types.
     */
    void displayPacketTypeMenu() const;

    /**
     * @brief Displays a message for an invalid choice.
     */
    void displayInvalidChoiceMessage() const;

    /**
     * @brief Displays a message upon exiting the server program.
     */
    void displayExitMessage() const;

    /**
     * @brief Displays a message indicating a new packet added to the transmission table.
     */
    void displayPacketAddedMessage() const;

    /**
     * @brief Displays a message indicating a new packet cannot be added to the transmission table.
     */
    void displayPacketUnAddedMessage() const;

    /**
     * @brief Displays a message indicating the selection of a packet by IP address.
     *
     * @param ip The receiver IP address.
     */
    void displayPacketSelectedMessage(const std::string& ip) const;

    /**
     * @brief Displays a header for the senders information.
     */
    void displaySendersInfoHeader() const;

    /**
     * @brief Displays a header for the packet type percentage calculation.
     */
    void displayPercentageCalculationHeader() const;

    /**
     * @brief Displays a message for an invalid IP address format.
     */
    void displayInvalidIpAddressMessage() const;

    /**
     * @brief Displays a message indicating a packet removed from the transmission table.
     *
     * @param ip The receiver IP address.
     */
    void displayPacketRemovedMessage(const std::string& ip) const;

    /**
     * @brief Displays a header for all packets in the transmission table.
     */
    void displayAllPacketsHeader() const;

    /**
     * @brief Displays the menu for selecting the code type.
     */
    void displayCodeTypeMenu() const;

    /**
     * @brief Displays the menu for selecting the information type.
     */
    void displayInfoTypeMenu() const;

    /**
     * @brief Displays the prompt for entering a message.
     */
    void displayMessagePrompt() const;

    /**
     * @brief Displays the prompt for entering a username.
     */
    void displayUsernamePrompt() const;

    /**
     * @brief Displays the menu for selecting thread mode (single-threaded or multi-threaded).
     */
    void displayThreadModeMenu() const;

    void resultPercent(const std::string& type, float percent) const;
};

#endif //VISUAL_H
