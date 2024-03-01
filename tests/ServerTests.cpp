#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "../include/Server.h"

TEST_CASE("Server tests", "[Server]") {
    SECTION("Constructor and getter methods") {
        Server server("TestServer", "192.168.0.1");
        REQUIRE(server.getServerName() == "TestServer");
        REQUIRE(server.getServerAddress() == "192.168.0.1");
    }

    SECTION("Setter methods") {
        Server server;
        server.setName("NewServerName");
        REQUIRE(server.getServerName() == "NewServerName");

        server.setIPAddress("192.168.0.2");
        REQUIRE(server.getServerAddress() == "192.168.0.2");
    }

    SECTION("Adding packets to transmission table") {
        Server server("TestServer", "192.168.0.1");
        std::shared_ptr<Packet> packet1 = std::make_shared<MailPacket>("192.168.0.1", "192.168.0.2", "Sender", "Hello");
        std::shared_ptr<Packet> packet2 = std::make_shared<FilePacket>("192.168.0.2", "192.168.0.1",
                                                                       Data::CodeType::ASCII, Data::InfoType::Control,
                                                                       "File");

        server.addPacketToTransmissionTable(packet1);
        server.addPacketToTransmissionTable(packet2);

        REQUIRE(server.findByPriority("192.168.0.1") == packet2);
    }

    SECTION("Erasing packets from transmission table by priority") {
        Server server("TestServer", "192.168.0.1");
        std::shared_ptr<Packet> packet1 = std::make_shared<MailPacket>("192.168.0.1", "192.168.0.2", "Sender", "Hello");
        std::shared_ptr<Packet> packet2 = std::make_shared<FilePacket>("192.168.0.2", "192.168.0.1",
                                                                       Data::CodeType::ASCII, Data::InfoType::Control,
                                                                       "File");

        server.addPacketToTransmissionTable(packet1);
        server.addPacketToTransmissionTable(packet2);

        REQUIRE(server.eraseByPriority("192.168.0.2") == true);
        REQUIRE(server.findByPriority("192.168.0.2") == nullptr);
    }

}

TEST_CASE("Server methods", "[Server]") {
    SECTION("showSendersInfo") {
        Server server("TestServer", "192.168.1.1");
        std::shared_ptr<Packet> packet1 = std::make_shared<MailPacket>("192.168.1.1", "192.168.1.2", "John", "Hello");
        std::shared_ptr<Packet> packet2 = std::make_shared<FilePacket>("192.168.1.2", "192.168.1.1", Data::CodeType::ASCII, Data::InfoType::Control, "Received");

        server.addPacketToTransmissionTable(packet1);
        server.addPacketToTransmissionTable(packet2);

        std::ostringstream oss;
        server.showSendersInfo(oss);

        REQUIRE(oss.str() == "Sender Address: 192.168.1.2\nSender Address: 192.168.1.1\n");
    }

    SECTION("calculatePacketTypePercentage") {
        Server server("TestServer", "192.168.1.1");
        std::shared_ptr<Packet> packet1 = std::make_shared<MailPacket>("192.168.1.1", "192.168.1.2", "John", "Hello");
        std::shared_ptr<Packet> packet2 = std::make_shared<FilePacket>("192.168.1.2", "192.168.1.1", Data::CodeType::ASCII, Data::InfoType::Control, "Received");
        std::shared_ptr<Packet> packet3 = std::make_shared<HyperTextPacket>("192.168.1.3", "192.168.1.4", Data::CodeType::ASCII, Data::InfoType::Control, "Hi");

        server.addPacketToTransmissionTable(packet1);
        server.addPacketToTransmissionTable(packet2);
        server.addPacketToTransmissionTable(packet3);

        float mailPercentage = server.calculatePacketTypePercentage("M");
        float filePercentage = server.calculatePacketTypePercentage("F");
        float hyperTextPercentage = server.calculatePacketTypePercentage("HT");

        // Check if the percentages are calculated correctly
        REQUIRE(mailPercentage == Approx(33.3333).epsilon(0.01));
        REQUIRE(filePercentage == Approx(33.3333).epsilon(0.01));
        REQUIRE(hyperTextPercentage == Approx(33.3333).epsilon(0.01));
    }

    SECTION("calculatePacketTypePercentageMT") {
        Server server("TestServer", "192.168.1.1");
        std::shared_ptr<Packet> packet1 = std::make_shared<MailPacket>("192.168.1.1", "192.168.1.2", "John", "Hello");
        std::shared_ptr<Packet> packet2 = std::make_shared<FilePacket>("192.168.1.2", "192.168.1.1", Data::CodeType::ASCII, Data::InfoType::Control, "Received");
        std::shared_ptr<Packet> packet3 = std::make_shared<HyperTextPacket>("192.168.1.3", "192.168.1.4", Data::CodeType::ASCII, Data::InfoType::Control, "Hi");

        server.addPacketToTransmissionTable(packet1);
        server.addPacketToTransmissionTable(packet2);
        server.addPacketToTransmissionTable(packet3);

        float mailPercentage = server.calculatePacketTypePercentageMT("M");
        float filePercentage = server.calculatePacketTypePercentageMT("F");
        float hyperTextPercentage = server.calculatePacketTypePercentageMT("HT");

        REQUIRE(mailPercentage == Approx(33.3333).epsilon(0.01));
        REQUIRE(filePercentage == Approx(33.3333).epsilon(0.01));
        REQUIRE(hyperTextPercentage == Approx(33.3333).epsilon(0.01));
    }
}

TEST_CASE("Server Multithreaded Packet Percentage Calculation Test", "[Server]") {
    SECTION("Calculate packet type percentage using multiple threads") {
        Server server("TestServer", "192.168.1.1");


        for (int i = 0; i < 2000; ++i) {
            std::shared_ptr<Packet> packet;
            if (i % 3 == 0) {
                packet = std::make_shared<MailPacket>("192.168.1.1", "192.168.1." + std::to_string(i), "Sender", "Hello");
            } else if (i % 3 == 1) {
                packet = std::make_shared<FilePacket>("192.168.1.2" + std::to_string(i), "192.168.1." + std::to_string(i), Data::CodeType::ASCII, Data::InfoType::Control, "FileData");
            } else {
                packet = std::make_shared<HyperTextPacket>("192.168.1.3", "192.168.1." + std::to_string(i), Data::CodeType::ASCII, Data::InfoType::Control, "HyperTextData");
            }
            server.addPacketToTransmissionTable(packet);
        }

        float mailPercentage = server.calculatePacketTypePercentageMT("M");
        float filePercentage = server.calculatePacketTypePercentageMT("F");
        float hyperTextPercentage = server.calculatePacketTypePercentageMT("HT");

        REQUIRE(mailPercentage == Approx(33.35f).epsilon(0.01f));
        REQUIRE(filePercentage == Approx(33.35f).epsilon(0.01f));
        REQUIRE(hyperTextPercentage == Approx(33.3f).epsilon(0.01f));
    }
}

