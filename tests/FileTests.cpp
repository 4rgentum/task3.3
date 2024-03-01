#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "../include/Packets/FilePacket.h"

TEST_CASE("Test FilePacket Parameterized Constructor", "[FilePacket]") {
    FilePacket filePacket("sender", "receiver", Data::CodeType::ASCII, Data::InfoType::Control, "message");

    SECTION("Test Sender Address") {
    REQUIRE(filePacket.getSenderAddress() == "sender");
    }

    SECTION("Test Receiver Address") {
    REQUIRE(filePacket.getReceiverAddress() == "receiver");
    }

    SECTION("Test Code Type") {
    REQUIRE(filePacket.getCodeType() == Data::CodeType::ASCII);
    }

    SECTION("Test Info Type") {
    REQUIRE(filePacket.getInfoType() == Data::InfoType::Control);
    }

    SECTION("Test Message") {
    REQUIRE(filePacket.getMessage() == "message");
    }
}

TEST_CASE("Test FilePacket Copy Constructor", "[FilePacket]") {
    FilePacket filePacket("sender", "receiver", Data::CodeType::ASCII, Data::InfoType::Control, "message");
    FilePacket copyFilePacket(filePacket);

    SECTION("Test Sender Address") {
    REQUIRE(copyFilePacket.getSenderAddress() == filePacket.getSenderAddress());
    }

    SECTION("Test Receiver Address") {
    REQUIRE(copyFilePacket.getReceiverAddress() == filePacket.getReceiverAddress());
    }

    SECTION("Test Code Type") {
    REQUIRE(copyFilePacket.getCodeType() == filePacket.getCodeType());
    }

    SECTION("Test Info Type") {
    REQUIRE(copyFilePacket.getInfoType() == filePacket.getInfoType());
    }

    SECTION("Test Message") {
    REQUIRE(copyFilePacket.getMessage() == filePacket.getMessage());
    }
}

TEST_CASE("Test FilePacket Move Constructor", "[FilePacket]") {
    FilePacket filePacket("sender", "receiver", Data::CodeType::ASCII, Data::InfoType::Control, "message");
    FilePacket movedFilePacket(std::move(filePacket));

    SECTION("Test Sender Address") {
    REQUIRE(movedFilePacket.getSenderAddress() == "sender");
    }

    SECTION("Test Receiver Address") {
    REQUIRE(movedFilePacket.getReceiverAddress() == "receiver");
    }

    SECTION("Test Code Type") {
    REQUIRE(movedFilePacket.getCodeType() == Data::CodeType::ASCII);
    }

    SECTION("Test Info Type") {
    REQUIRE(movedFilePacket.getInfoType() == Data::InfoType::Control);
    }

    SECTION("Test Message") {
    REQUIRE(movedFilePacket.getMessage() == "message");
    }
}

TEST_CASE("Test FilePacket Copy Assignment Operator", "[FilePacket]") {
    FilePacket filePacket("sender", "receiver", Data::CodeType::ASCII, Data::InfoType::Control, "message");
    FilePacket copyFilePacket;
    copyFilePacket = filePacket;

    SECTION("Test Sender Address") {
    REQUIRE(copyFilePacket.getSenderAddress() == filePacket.getSenderAddress());
    }

    SECTION("Test Receiver Address") {
    REQUIRE(copyFilePacket.getReceiverAddress() == filePacket.getReceiverAddress());
    }

    SECTION("Test Code Type") {
    REQUIRE(copyFilePacket.getCodeType() == filePacket.getCodeType());
    }

    SECTION("Test Info Type") {
    REQUIRE(copyFilePacket.getInfoType() == filePacket.getInfoType());
    }

    SECTION("Test Message") {
    REQUIRE(copyFilePacket.getMessage() == filePacket.getMessage());
    }
}

TEST_CASE("Test FilePacket Move Assignment Operator", "[FilePacket]") {
    FilePacket filePacket("sender", "receiver", Data::CodeType::ASCII, Data::InfoType::Control, "message");
    FilePacket movedFilePacket;
    movedFilePacket = std::move(filePacket);

    SECTION("Test Sender Address") {
    REQUIRE(movedFilePacket.getSenderAddress() == "sender");
    }

    SECTION("Test Receiver Address") {
    REQUIRE(movedFilePacket.getReceiverAddress() == "receiver");
    }

    SECTION("Test Code Type") {
    REQUIRE(movedFilePacket.getCodeType() == Data::CodeType::ASCII);
    }

    SECTION("Test Info Type") {
    REQUIRE(movedFilePacket.getInfoType() == Data::InfoType::Control);
    }

    SECTION("Test Message") {
    REQUIRE(movedFilePacket.getMessage() == "message");
    }
}

TEST_CASE("Test FilePacket getType and info", "[FilePacket]") {
    FilePacket filePacket("sender", "receiver", Data::CodeType::ASCII, Data::InfoType::Control, "message");

    SECTION("Test getType") {
    REQUIRE(filePacket.getType() == "F");
    }

    SECTION("Test info") {
    std::string expectedInfo = "File Packet: Sender Address - sender, Receiver Address - receiver, Code Type - ASCII, Info Type - Control, Message - message";
    REQUIRE(filePacket.info() == expectedInfo);
    }
}

TEST_CASE("Test FilePacket toHyperTextPacket", "[FilePacket]") {
    FilePacket filePacket("sender", "receiver", Data::CodeType::ASCII, Data::InfoType::Control, "message");
    HyperTextPacket hyperTextPacket = filePacket.toHyperTextPacket();

    SECTION("Test Sender Address") {
        REQUIRE(hyperTextPacket.getSenderAddress() == "sender");
    }

    SECTION("Test Receiver Address") {
        REQUIRE(hyperTextPacket.getReceiverAddress() == "receiver");
    }

    SECTION("Test Code Type") {
        REQUIRE(hyperTextPacket.getCodeType() == Data::CodeType::ASCII);
    }

    SECTION("Test Info Type") {
        REQUIRE(hyperTextPacket.getInfoType() == Data::InfoType::Control);
    }

    SECTION("Test Message") {
        REQUIRE(hyperTextPacket.getMessage() == "message");
    }
}

TEST_CASE("Test FilePacket setCodeType", "[FilePacket]") {
    FilePacket filePacket("sender", "receiver", Data::CodeType::ASCII, Data::InfoType::Control, "message");
    filePacket.setCodeType(Data::CodeType::BIN);

    SECTION("Test Code Type") {
        REQUIRE(filePacket.getCodeType() == Data::CodeType::BIN);
    }
}

TEST_CASE("Test FilePacket setInfoType", "[FilePacket]") {
    FilePacket filePacket("sender", "receiver", Data::CodeType::ASCII, Data::InfoType::Control, "message");
    filePacket.setInfoType(Data::InfoType::Data);

    SECTION("Test Info Type") {
        REQUIRE(filePacket.getInfoType() == Data::InfoType::Data);
    }
}

TEST_CASE("Test FilePacket setMessage", "[FilePacket]") {
    FilePacket filePacket("sender", "receiver", Data::CodeType::ASCII, Data::InfoType::Control, "message");
    filePacket.setMessage("new message");

    SECTION("Test Message") {
        REQUIRE(filePacket.getMessage() == "new message");
    }
}
