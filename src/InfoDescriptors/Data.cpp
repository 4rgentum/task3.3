#include "../../include/InfoDescriptors/Data.h"

Data::Data()
        : code(Data::CodeType::Undefined), info(Data::InfoType::Undefined) {}

Data::Data(Data::CodeType codeType, Data::InfoType infoType)
        : code(codeType), info(infoType) {}

Data::Data(const Data& other)
        : code(other.code), info(other.info) {}

Data::Data(Data&& other) noexcept
        : code(std::move(other.code)), info(std::move(other.info)) {}

Data& Data::operator=(const Data& other) {
    if (this != &other) {
        code = other.code;
        info = other.info;
    }
    return *this;
}

Data& Data::operator=(Data&& other) noexcept {
    if (this != &other) {
        code = std::move(other.code);
        info = std::move(other.info);
    }
    return *this;
}

Data::CodeType Data::getCodeType() const {
    return code;
}

Data::InfoType Data::getInfoType() const {
    return info;
}

void Data::setCodeType(Data::CodeType codeType) {
    code = codeType;
}

void Data::setInfoType(Data::InfoType infoType) {
    info = infoType;
}
