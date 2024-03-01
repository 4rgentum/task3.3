#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "../include/TransmissionTable.h"

TEST_CASE("TransmissionTable tests", "[TransmissionTable]") {
    SECTION("insert, find, erase, empty, size, contains, operator[]") {
        TransmissionTable table;

        std::shared_ptr<Packet> packet1 = std::make_shared<MailPacket>("192.168.1.1", "192.168.1.2", "Jon", "Hello");
        std::shared_ptr<Packet> packet2 = std::make_shared<FilePacket>("192.168.1.2", "192.168.1.1", Data::CodeType::ASCII, Data::InfoType::Control, "Received");
        std::shared_ptr<Packet> packet3 = std::make_shared<HyperTextPacket>("192.168.1.3", "192.168.1.4", Data::CodeType::ASCII, Data::InfoType::Control, "Hi");

        table.insert(packet1);
        table.insert(packet2);
        table.insert(packet3);

        REQUIRE(table.size() == 3);
        REQUIRE_FALSE(table.empty());

        SECTION("Finding packets") {
            REQUIRE(table.find("192.168.1.2", "M") == packet1);
            REQUIRE(table.find("192.168.1.1", "F") == packet2);
            REQUIRE(table.find("192.168.1.4", "HT") == packet3);
            REQUIRE(table.find("192.168.1.4", "F") == nullptr);
        }

        SECTION("Erasing packets") {
            REQUIRE(table.erase("192.168.1.2", "M"));
            REQUIRE(table.size() == 2);
            REQUIRE_FALSE(table.contains("192.168.1.1", "M"));

            REQUIRE_FALSE(table.erase("192.168.1.4", "F"));
            REQUIRE(table.size() == 2);
        }

        SECTION("Operator[]") {
            std::string str1 = "192.168.1.4";
            std::string str2 = "192.168.1.1";
            auto pair1 = std::make_pair<const std::string&, const std::string&>(str1, "HT");
            auto pair2 = std::make_pair<const std::string&, const std::string&>(str2, "F");
            auto packet = table[pair1];
            REQUIRE(packet == packet3);

            const auto& constTable = table;
            auto constPacket = constTable[pair2];
            REQUIRE(constPacket == packet2);
        }
    }

    SECTION("Stream insertion operator") {
        TransmissionTable table;


        std::shared_ptr<Packet> packet1 = std::make_shared<MailPacket>("192.168.1.1", "192.168.1.2", "Jon", "Hello");
        std::shared_ptr<Packet> packet2 = std::make_shared<FilePacket>("192.168.1.2", "192.168.1.1", Data::CodeType::ASCII, Data::InfoType::Control, "Received");

        table.insert(packet1);
        table.insert(packet2);

        std::ostringstream oss;
        oss << table;
    }

    SECTION("Iterators") {
        TransmissionTable table;

        std::shared_ptr<Packet> packet1 = std::make_shared<MailPacket>("192.168.1.1", "192.168.1.2", "Jon", "Hello");
        std::shared_ptr<Packet> packet2 = std::make_shared<FilePacket>("192.168.1.2", "192.168.1.1", Data::CodeType::ASCII, Data::InfoType::Control, "Received");

        table.insert(packet1);
        table.insert(packet2);

        SECTION("Iterator") {
            int count = 0;
            for (auto it = table.begin(); it != table.end(); ++it) {
            count++;
            }
            REQUIRE(count == 2);
        }

        SECTION("Const Iterator") {
            const TransmissionTable& constTable = table;
            int count = 0;
            for (auto it = constTable.begin(); it != constTable.end(); ++it) {
                count++;
            }
            REQUIRE(count == 2);
        }
    }
}
