#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "../include/Packets/MailPacket.h"

TEST_CASE("Test MailPacket Constructors", "[MailPacket]") {
    SECTION("Test parameterized constructor") {
        MailPacket mailPacket("sender", "receiver", "user", "message");
        REQUIRE(mailPacket.getSenderAddress() == "sender");
        REQUIRE(mailPacket.getReceiverAddress() == "receiver");
        REQUIRE(mailPacket.getUsername() == "user");
        REQUIRE(mailPacket.getMessage() == "message");
    }

    SECTION("Test default constructor") {
        MailPacket mailPacket;
        REQUIRE(mailPacket.getSenderAddress().empty());
        REQUIRE(mailPacket.getReceiverAddress().empty());
        REQUIRE(mailPacket.getUsername().empty());
        REQUIRE(mailPacket.getMessage() == "Message not available");
    }
}

TEST_CASE("Test MailPacket Setters and Getters", "[MailPacket]") {
    MailPacket mailPacket;
        SECTION("Test setUsername") {
        mailPacket.setUsername("user");
        REQUIRE(mailPacket.getUsername() == "user");
    }

    SECTION("Test setMessage") {
        mailPacket.setMessage("message");
        REQUIRE(mailPacket.getMessage() == "message");
    }

}

TEST_CASE("Test MailPacket toFilePacket", "[MailPacket]") {
    MailPacket mailPacket("sender", "receiver", "user", "message");
    FilePacket filePacket = mailPacket.toFilePacket();
    REQUIRE(filePacket.getSenderAddress() == "sender");
    REQUIRE(filePacket.getReceiverAddress() == "receiver");
    REQUIRE(filePacket.getMessage() == "message");
}

TEST_CASE("Test MailPacket Copy Constructor", "[MailPacket]") {
    MailPacket mailPacket("sender", "receiver", "user", "message");
    MailPacket copyMailPacket(mailPacket);

    SECTION("Test Sender Address") {
        REQUIRE(copyMailPacket.getSenderAddress() == mailPacket.getSenderAddress());
    }

    SECTION("Test Receiver Address") {
        REQUIRE(copyMailPacket.getReceiverAddress() == mailPacket.getReceiverAddress());
    }

    SECTION("Test Username") {
        REQUIRE(copyMailPacket.getUsername() == mailPacket.getUsername());
    }

    SECTION("Test Message") {
        REQUIRE(copyMailPacket.getMessage() == mailPacket.getMessage());
    }
}

TEST_CASE("Test MailPacket Move Constructor", "[MailPacket]") {
    MailPacket mailPacket("sender", "receiver", "user", "message");
    MailPacket movedMailPacket(std::move(mailPacket));

    SECTION("Test Sender Address") {
        REQUIRE(movedMailPacket.getSenderAddress() == "sender");
    }

    SECTION("Test Receiver Address") {
        REQUIRE(movedMailPacket.getReceiverAddress() == "receiver");
    }

    SECTION("Test Username") {
        REQUIRE(movedMailPacket.getUsername() == "user");
    }

    SECTION("Test Message") {
        REQUIRE(movedMailPacket.getMessage() == "message");
    }
}

TEST_CASE("Test MailPacket Copy Assignment Operator", "[MailPacket]") {
    MailPacket mailPacket("sender", "receiver", "user", "message");
    MailPacket copyMailPacket;
    copyMailPacket = mailPacket;

    SECTION("Test Sender Address") {
        REQUIRE(copyMailPacket.getSenderAddress() == mailPacket.getSenderAddress());
    }

    SECTION("Test Receiver Address") {
        REQUIRE(copyMailPacket.getReceiverAddress() == mailPacket.getReceiverAddress());
    }

    SECTION("Test Username") {
        REQUIRE(copyMailPacket.getUsername() == mailPacket.getUsername());
    }

    SECTION("Test Message") {
        REQUIRE(copyMailPacket.getMessage() == mailPacket.getMessage());
    }
}

TEST_CASE("Test MailPacket Move Assignment Operator", "[MailPacket]") {
    MailPacket mailPacket("sender", "receiver", "user", "message");
    MailPacket movedMailPacket;
    movedMailPacket = std::move(mailPacket);

    SECTION("Test Sender Address") {
        REQUIRE(movedMailPacket.getSenderAddress() == "sender");
    }

    SECTION("Test Receiver Address") {
        REQUIRE(movedMailPacket.getReceiverAddress() == "receiver");
    }

    SECTION("Test Username") {
        REQUIRE(movedMailPacket.getUsername() == "user");
    }

    SECTION("Test Message") {
        REQUIRE(movedMailPacket.getMessage() == "message");
    }
}

TEST_CASE("Test MailPacket getType and info", "[MailPacket]") {
    MailPacket mailPacket("sender", "receiver", "user", "message");

    SECTION("Test getType") {
        REQUIRE(mailPacket.getType() == "M");
    }

    SECTION("Test info") {
        std::string expectedInfo = "Mail Packet: Sender Address - sender, Receiver Address - receiver, Username - user, Message - message";
        REQUIRE(mailPacket.info() == expectedInfo);
    }
}

