#ifndef DATA_H
#define DATA_H

#include <iostream>

/**
 * @brief The Data class represents a data structure with code and information types.
 */
class Data {
public:
    /**
     * @brief Enumeration for code types.
     */
    enum class CodeType {
        ASCII,      /**< ASCII code type */
        BIN,        /**< BIN code type */
        Undefined   /**< Undefined code type */
    };

    /**
     * @brief Enumeration for information types.
     */
    enum class InfoType {
        Control,    /**< Control information type */
        Data,       /**< Data information type */
        Undefined   /**< Undefined information type */
    };

    /**
     * @brief Default constructor.
     */
    Data();

    /**
     * @brief Constructor with code and information types.
     * @param codeType The code type.
     * @param infoType The information type.
     */
    Data(CodeType codeType, InfoType infoType);

    /**
     * @brief Copy constructor.
     * @param other The other Data object to copy from.
     */
    Data(const Data& other);

    /**
     * @brief Move constructor.
     * @param other The other Data object to move from.
     */
    Data(Data&& other) noexcept;

    /**
     * @brief Copy assignment operator.
     * @param other The other Data object to copy from.
     * @return A reference to the assigned Data object.
     */
    Data& operator=(const Data& other);

    /**
     * @brief Move assignment operator.
     * @param other The other Data object to move from.
     * @return A reference to the moved Data object.
     */
    Data& operator=(Data&& other) noexcept;

    /**
     * @brief Get the code type.
     * @return The code type.
     */
    CodeType getCodeType() const;

    /**
     * @brief Get the information type.
     * @return The information type.
     */
    InfoType getInfoType() const;

    /**
     * @brief Set the code type.
     * @param codeType The code type to set.
     */
    void setCodeType(CodeType codeType);

    /**
     * @brief Set the information type.
     * @param infoType The information type to set.
     */
    void setInfoType(InfoType infoType);

private:
    CodeType code;  /**< The code type. */
    InfoType info;  /**< The information type. */
};

#endif // DATA_H
