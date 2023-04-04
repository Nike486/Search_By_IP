#pragma once

#include <boost/beast.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <iostream>
#include <fstream>
#include <iostream>
#include "nlohmann/json.hpp"


std::string MAIN_API = "ip-api.com";
std::string API_ARGUMENTS = "/json/";

namespace http = boost::beast::http;

class Client
{
public:
    std::string getResponse (std::string ip)
    {
        boost::asio::io_context io;
        boost::asio::ip::tcp::resolver resolver(io);
        boost::asio::ip::tcp::socket socket(io);

        boost::asio::connect(socket, resolver.resolve(MAIN_API, "80"));

        std::string arguments = API_ARGUMENTS + ip;
        http::request<http::string_body> req (http::verb::get, arguments, 11);

        req.set(http::field::host, MAIN_API);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

        http::write(socket, req);

        std::string response;

        boost::beast::flat_buffer buffer;
        http::response<http::dynamic_body> res;
        http::read(socket, buffer, res);
        response = boost::beast::buffers_to_string(res.body().data());

        socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
        return response;
    }
};

void record ()
{
    std::ifstream read("result.json");
    nlohmann::json jsonRead;
    read >> jsonRead;

    double lat = jsonRead["lat"];
    double lon = jsonRead["lon"];
    read.close();

    std::string mapLink = "https://geotree.ru/coordinates?lat=" + std::to_string(lat) + "&lon=" + std::to_string(lon) + "&z=18&mlat=" + std::to_string(lat) + "&mlon=" + std::to_string(lon) + "&c=" + std::to_string(lon) + "," + std::to_string(lat);

    std::ofstream HTMLFile ("answer.html");
    HTMLFile
    << "<p>status:" << jsonRead["status"] << "</p>" << std::endl
    << "<p>country:" << jsonRead["country"] << "</p>" << std::endl
    << "<p>countryCode:" << jsonRead["countryCode"] << "</p>" << std::endl
    << "<p>region:" << jsonRead["region"] << "</p>" << std::endl
    << "<p>regionName:" << jsonRead["regionName"] << "</p>" << std::endl
    << "<p>city:" << jsonRead["city"] << "</p>" << std::endl
    << "<p>zip:" << jsonRead["zip"] << "</p>" << std::endl
    << "<p>timezone:" << jsonRead["timezone"] << "</p>" << std::endl
    << "<p>isp:" << jsonRead["isp"] << "</p>" << std::endl
    << "<p>org:" << jsonRead["org"] << "</p>" << std::endl
    << "<p>as:" << jsonRead["as"] << "</p>" << std::endl
    << "<p>query:" << jsonRead["query"] << "</p>" << std::endl
    << "<a href=" << mapLink << ">On the map</a>" << std::endl;
}

