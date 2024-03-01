#include "Application/Controller/Controller.h"

int main() {
    std::string serverName = "MyServer";
    std::string serverAddress = "192.168.1.1";
    Controller controller(serverName, serverAddress);
    controller.run();
    return 0;
}
