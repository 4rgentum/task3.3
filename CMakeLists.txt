cmake_minimum_required(VERSION 3.22)
project(lab3)

set(CMAKE_CXX_STANDARD 20)

#add_compile_options(-fsanitize=thread)
#add_link_options(-fsanitize=thread)

add_compile_options(-fprofile-arcs -ftest-coverage)
link_libraries(gcov)

add_executable(lab3 main.cpp include/Packets/MailPacket.h
        src/Packets/MailPacket.cpp src/Packets/FilePacket.cpp  src/Packets/Packet.cpp include/Packets/Packet.h include/Packets/FilePacket.h
        include/InfoDescriptors/MessageDescriptor.h include/Funcs.h include/Packets/HyperTextPacket.h src/Packets/HyperTextPacket.cpp
        include/InfoDescriptors/LinkDescriptor.h include/InfoDescriptors/Data.h src/InfoDescriptors/LinkDescriptor.cpp
        src/InfoDescriptors/Data.cpp src/InfoDescriptors/MessageDescriptor.cpp include/TransmissionTable.h src/TransmissionTable.cpp
        include/Server.h src/Server.cpp Application/Controller/Controller.cpp Application/Controller/Controller.h
        Application/Visual/Visual.cpp Application/Visual/Visual.h)

add_executable(MailTests tests/MailTests.cpp include/Packets/MailPacket.h
        src/Packets/MailPacket.cpp src/Packets/FilePacket.cpp  src/Packets/Packet.cpp include/Packets/Packet.h include/Packets/FilePacket.h
        include/InfoDescriptors/MessageDescriptor.h include/Funcs.h include/Packets/HyperTextPacket.h src/Packets/HyperTextPacket.cpp
        include/InfoDescriptors/LinkDescriptor.h include/InfoDescriptors/Data.h src/InfoDescriptors/LinkDescriptor.cpp
        src/InfoDescriptors/Data.cpp src/InfoDescriptors/MessageDescriptor.cpp)

add_executable(FileTests tests/FileTests.cpp src/Packets/FilePacket.cpp
        src/Packets/Packet.cpp include/Packets/Packet.h include/Packets/FilePacket.h
        include/InfoDescriptors/MessageDescriptor.h include/Funcs.h include/Packets/HyperTextPacket.h src/Packets/HyperTextPacket.cpp
        include/InfoDescriptors/LinkDescriptor.h include/InfoDescriptors/Data.h src/InfoDescriptors/LinkDescriptor.cpp
        src/InfoDescriptors/Data.cpp src/InfoDescriptors/MessageDescriptor.cpp)

add_executable(HyperTextTests tests/HyperTextTests.cpp src/Packets/Packet.cpp include/Packets/Packet.h
        include/InfoDescriptors/MessageDescriptor.h include/Funcs.h include/Packets/HyperTextPacket.h src/Packets/HyperTextPacket.cpp
        include/InfoDescriptors/LinkDescriptor.h include/InfoDescriptors/Data.h src/InfoDescriptors/LinkDescriptor.cpp
        src/InfoDescriptors/Data.cpp src/InfoDescriptors/MessageDescriptor.cpp)

add_executable(MapTests tests/MapTests.cpp unordered_map/unordered_map.h)

add_executable(TableTests tests/TableTests.cpp include/Packets/MailPacket.h
        src/Packets/MailPacket.cpp src/Packets/FilePacket.cpp  src/Packets/Packet.cpp include/Packets/Packet.h include/Packets/FilePacket.h
        include/InfoDescriptors/MessageDescriptor.h include/Funcs.h include/Packets/HyperTextPacket.h src/Packets/HyperTextPacket.cpp
        include/InfoDescriptors/LinkDescriptor.h include/InfoDescriptors/Data.h src/InfoDescriptors/LinkDescriptor.cpp
        src/InfoDescriptors/Data.cpp src/InfoDescriptors/MessageDescriptor.cpp include/TransmissionTable.h src/TransmissionTable.cpp)

add_executable(ServerTests tests/ServerTests.cpp include/Packets/MailPacket.h
        src/Packets/MailPacket.cpp src/Packets/FilePacket.cpp  src/Packets/Packet.cpp include/Packets/Packet.h include/Packets/FilePacket.h
        include/InfoDescriptors/MessageDescriptor.h include/Funcs.h include/Packets/HyperTextPacket.h src/Packets/HyperTextPacket.cpp
        include/InfoDescriptors/LinkDescriptor.h include/InfoDescriptors/Data.h src/InfoDescriptors/LinkDescriptor.cpp
        src/InfoDescriptors/Data.cpp src/InfoDescriptors/MessageDescriptor.cpp include/TransmissionTable.h src/TransmissionTable.cpp
        include/Server.h src/Server.cpp)
