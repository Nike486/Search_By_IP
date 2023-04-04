#include "header.h"

int main() {

    try
    {
        Client client;

        std::string request;

        std::cout << "Enter a request:";
        std::cin >> request;

        std::string response = client.getResponse(request);
        std::ofstream resultFile("result.json");
        resultFile << response;
        resultFile.close();

        record();
    }

    catch (std::exception err)
    {
        std::cout << "Error" << std::endl;
    }

    return 0;
}
