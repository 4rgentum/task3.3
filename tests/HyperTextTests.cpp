#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "../include/Packets/HyperTextPacket.h"

TEST_CASE("Test HyperTextPacket default constructor", "[HyperTextPacket]") {
    HyperTextPacket packet;

    SECTION("Test Sender Address") {
        REQUIRE(packet.getSenderAddress() == "");
    }

    SECTION("Test Receiver Address") {
        REQUIRE(packet.getReceiverAddress() == "");
    }

    SECTION("Test Code Type") {
        REQUIRE(packet.getCodeType() == Data::CodeType::Undefined);
    }

    SECTION("Test Info Type") {
        REQUIRE(packet.getInfoType() == Data::InfoType::Undefined);
    }

    SECTION("Test Message") {
        REQUIRE(packet.getMessage() == "Message not available");
    }

    SECTION("Test Number of Links") {
        REQUIRE(packet.getNumLinks() == 0);
    }

    SECTION("Test Links") {
        REQUIRE(packet.getLinks().empty());
    }
}

TEST_CASE("Test HyperTextPacket parameterized constructor", "[HyperTextPacket]") {
    HyperTextPacket packet("sender", "receiver", Data::CodeType::ASCII, Data::InfoType::Data, "message");

    SECTION("Test Sender Address") {
        REQUIRE(packet.getSenderAddress() == "sender");
    }

    SECTION("Test Receiver Address") {
        REQUIRE(packet.getReceiverAddress() == "receiver");
    }

    SECTION("Test Code Type") {
        REQUIRE(packet.getCodeType() == Data::CodeType::ASCII);
    }

    SECTION("Test Info Type") {
        REQUIRE(packet.getInfoType() == Data::InfoType::Data);
    }

    SECTION("Test Message") {
        REQUIRE(packet.getMessage() == "message");
    }

    SECTION("Test Number of Links") {
        REQUIRE(packet.getNumLinks() == 0);
    }

    SECTION("Test Links") {
        REQUIRE(packet.getLinks().empty());
    }
}

TEST_CASE("Test HyperTextPacket copy constructor", "[HyperTextPacket]") {
    HyperTextPacket original("sender", "receiver", Data::CodeType::ASCII, Data::InfoType::Data, "message");
    original.addLink(LinkDescriptor(LinkDescriptor::ProtocolType::HTTP, "example.com"));

    HyperTextPacket copy(original);

    SECTION("Test Sender Address") {
        REQUIRE(copy.getSenderAddress() == "sender");
    }

    SECTION("Test Receiver Address") {
        REQUIRE(copy.getReceiverAddress() == "receiver");
    }

    SECTION("Test Code Type") {
        REQUIRE(copy.getCodeType() == Data::CodeType::ASCII);
    }

    SECTION("Test Info Type") {
        REQUIRE(copy.getInfoType() == Data::InfoType::Data);
    }

    SECTION("Test Message") {
        REQUIRE(copy.getMessage() == "message");
    }

    SECTION("Test Number of Links") {
        REQUIRE(copy.getNumLinks() == 1);
    }

    SECTION("Test Links") {
        REQUIRE(copy.getLinks().size() == 1);
        REQUIRE(copy.getLinks()[0].getProtocol() == LinkDescriptor::ProtocolType::HTTP);
        REQUIRE(copy.getLinks()[0].getServerName() == "example.com");
    }
}

TEST_CASE("Test HyperTextPacket move constructor", "[HyperTextPacket]") {
    HyperTextPacket original("sender", "receiver", Data::CodeType::ASCII, Data::InfoType::Data, "message");
    original.addLink(LinkDescriptor(LinkDescriptor::ProtocolType::HTTP, "example.com"));

    HyperTextPacket moved(std::move(original));

    SECTION("Test Sender Address") {
        REQUIRE(moved.getSenderAddress() == "sender");
    }

    SECTION("Test Receiver Address") {
        REQUIRE(moved.getReceiverAddress() == "receiver");
    }

    SECTION("Test Code Type") {
        REQUIRE(moved.getCodeType() == Data::CodeType::ASCII);
    }

    SECTION("Test Info Type") {
        REQUIRE(moved.getInfoType() == Data::InfoType::Data);
    }

    SECTION("Test Message") {
        REQUIRE(moved.getMessage() == "message");
    }

    SECTION("Test Number of Links") {
        REQUIRE(moved.getNumLinks() == 1);
    }

    SECTION("Test Links") {
        REQUIRE(moved.getLinks().size() == 1);
        REQUIRE(moved.getLinks()[0].getProtocol() == LinkDescriptor::ProtocolType::HTTP);
        REQUIRE(moved.getLinks()[0].getServerName() == "example.com");
    }
}

TEST_CASE("Test HyperTextPacket copy assignment operator", "[HyperTextPacket]") {
    HyperTextPacket original("sender", "receiver", Data::CodeType::ASCII, Data::InfoType::Data, "message");
    original.addLink(LinkDescriptor(LinkDescriptor::ProtocolType::HTTP, "example.com"));

    HyperTextPacket copy;
    copy = original;

    SECTION("Test Sender Address") {
        REQUIRE(copy.getSenderAddress() == "sender");
    }

    SECTION("Test Receiver Address") {
        REQUIRE(copy.getReceiverAddress() == "receiver");
    }

    SECTION("Test Code Type") {
        REQUIRE(copy.getCodeType() == Data::CodeType::ASCII);
    }

    SECTION("Test Info Type") {
        REQUIRE(copy.getInfoType() == Data::InfoType::Data);
    }

    SECTION("Test Message") {
        REQUIRE(copy.getMessage() == "message");
    }

    SECTION("Test Number of Links") {
        REQUIRE(copy.getNumLinks() == 1);
    }

    SECTION("Test Links") {
        REQUIRE(copy.getLinks().size() == 1);
        REQUIRE(copy.getLinks()[0].getProtocol() == LinkDescriptor::ProtocolType::HTTP);
        REQUIRE(copy.getLinks()[0].getServerName() == "example.com");
    }
}

TEST_CASE("Test HyperTextPacket move assignment operator", "[HyperTextPacket]") {
    HyperTextPacket original("sender", "receiver", Data::CodeType::ASCII, Data::InfoType::Data, "message");
    original.addLink(LinkDescriptor(LinkDescriptor::ProtocolType::HTTP, "example.com"));

    HyperTextPacket moved;
    moved = std::move(original);

    SECTION("Test Sender Address") {
        REQUIRE(moved.getSenderAddress() == "sender");
    }

    SECTION("Test Receiver Address") {
        REQUIRE(moved.getReceiverAddress() == "receiver");
    }

    SECTION("Test Code Type") {
        REQUIRE(moved.getCodeType() == Data::CodeType::ASCII);
    }

    SECTION("Test Info Type") {
        REQUIRE(moved.getInfoType() == Data::InfoType::Data);
    }

    SECTION("Test Message") {
        REQUIRE(moved.getMessage() == "message");
    }

    SECTION("Test Number of Links") {
        REQUIRE(moved.getNumLinks() == 1);
    }

    SECTION("Test Links") {
        REQUIRE(moved.getLinks().size() == 1);
        REQUIRE(moved.getLinks()[0].getProtocol() == LinkDescriptor::ProtocolType::HTTP);
        REQUIRE(moved.getLinks()[0].getServerName() == "example.com");
    }
}

TEST_CASE("Test HyperTextPacket getType", "[HyperTextPacket]") {
    HyperTextPacket packet("sender", "receiver", Data::CodeType::ASCII, Data::InfoType::Data, "message");

    SECTION("Test Type") {
        REQUIRE(packet.getType() == "HT");
    }
}

TEST_CASE("Test HyperTextPacket info", "[HyperTextPacket]") {
    HyperTextPacket packet("sender", "receiver", Data::CodeType::ASCII, Data::InfoType::Data, "message");
    packet.addLink(LinkDescriptor(LinkDescriptor::ProtocolType::HTTP, "example.com"));

    std::string expectedInfo = "HyperText Packet: Sender Address - sender, Receiver Address - receiver, Code Type - ASCII, Info Type - Data, Message - message, Number of Links - 1";
    packet.info();
}

TEST_CASE("Test HyperTextPacket setCodeType", "[HyperTextPacket]") {
    HyperTextPacket packet;
    packet.setCodeType(Data::CodeType::BIN);

    SECTION("Test Code Type") {
        REQUIRE(packet.getCodeType() == Data::CodeType::BIN);
    }
}

TEST_CASE("Test HyperTextPacket setInfoType", "[HyperTextPacket]") {
    HyperTextPacket packet;
    packet.setInfoType(Data::InfoType::Control);

    SECTION("Test Info Type") {
        REQUIRE(packet.getInfoType() == Data::InfoType::Control);
    }
}

TEST_CASE("Test HyperTextPacket setMessage", "[HyperTextPacket]") {
    HyperTextPacket packet;
    packet.setMessage("new message");

    SECTION("Test Message") {
        REQUIRE(packet.getMessage() == "new message");
    }
}

TEST_CASE("Test HyperTextPacket getNumLinks", "[HyperTextPacket]") {
    HyperTextPacket packet;
    packet.addLink(LinkDescriptor(LinkDescriptor::ProtocolType::HTTP, "example.com"));

    SECTION("Test Number of Links") {
        REQUIRE(packet.getNumLinks() == 1);
    }
}

TEST_CASE("Test HyperTextPacket getLinks", "[HyperTextPacket]") {
    HyperTextPacket packet;
    packet.addLink(LinkDescriptor(LinkDescriptor::ProtocolType::HTTP, "example.com"));
    packet.addLink(LinkDescriptor(LinkDescriptor::ProtocolType::FTP, "ftp.example.com"));

    SECTION("Test Number of Links") {
        REQUIRE(packet.getLinks().size() == 2);
    }

    SECTION("Test First Link") {
        REQUIRE(packet.getLinks()[0].getProtocol() == LinkDescriptor::ProtocolType::HTTP);
        REQUIRE(packet.getLinks()[0].getServerName() == "example.com");
    }

    SECTION("Test Second Link") {
        REQUIRE(packet.getLinks()[1].getProtocol() == LinkDescriptor::ProtocolType::FTP);
        REQUIRE(packet.getLinks()[1].getServerName() == "ftp.example.com");
    }
}

TEST_CASE("Test HyperTextPacket setLinks", "[HyperTextPacket]") {
    HyperTextPacket packet;
    packet.addLink(LinkDescriptor(LinkDescriptor::ProtocolType::HTTP, "example.com"));
    packet.addLink(LinkDescriptor(LinkDescriptor::ProtocolType::FTP, "ftp.example.com"));

    std::vector<LinkDescriptor> newLinks;
    newLinks.emplace_back(LinkDescriptor(LinkDescriptor::ProtocolType::HTTP, "secure.example.com"));
    packet.setLinks(newLinks);

    SECTION("Test Number of Links") {
        REQUIRE(packet.getLinks().size() == 1);
    }

    SECTION("Test Link") {
        REQUIRE(packet.getLinks()[0].getProtocol() == LinkDescriptor::ProtocolType::HTTP);
        REQUIRE(packet.getLinks()[0].getServerName() == "secure.example.com");
    }
}

TEST_CASE("Test HyperTextPacket addLink", "[HyperTextPacket]") {
    HyperTextPacket packet;
    packet.addLink(LinkDescriptor(LinkDescriptor::ProtocolType::HTTP, "example.com"));
    packet.addLink(LinkDescriptor(LinkDescriptor::ProtocolType::FTP, "ftp.example.com"));

    SECTION("Test Number of Links") {
        REQUIRE(packet.getLinks().size() == 2);
    }

    SECTION("Test First Link") {
        REQUIRE(packet.getLinks()[0].getProtocol() == LinkDescriptor::ProtocolType::HTTP);
        REQUIRE(packet.getLinks()[0].getServerName() == "example.com");
    }

    SECTION("Test Second Link") {
        REQUIRE(packet.getLinks()[1].getProtocol() == LinkDescriptor::ProtocolType::FTP);
        REQUIRE(packet.getLinks()[1].getServerName() == "ftp.example.com");
    }
}

TEST_CASE("Test HyperTextPacket subscript operator", "[HyperTextPacket]") {
    HyperTextPacket packet;
    packet.addLink(LinkDescriptor(LinkDescriptor::ProtocolType::HTTP, "example.com"));

    SECTION("Test First Link") {
        REQUIRE(packet[0].getProtocol() == LinkDescriptor::ProtocolType::HTTP);
        REQUIRE(packet[0].getServerName() == "example.com");
    }
}
