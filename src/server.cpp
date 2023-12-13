#include "server.h"

#include <string>

#include <boost/json/src.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/process/system.hpp>
#include <boost/process/search_path.hpp>
#include <boost/process/args.hpp>

namespace json = boost::json;
namespace fs = boost::filesystem;
namespace bp = boost::process;

const bp::filesystem::path ffmpeg = bp::search_path("ffmpeg");

HTTPServer::HTTPServer(const tcp::endpoint& ep)
    : context_{1}, acceptor_{context_, ep}
{
}

int HTTPServer::exec() {
    while (true) {
        tcp::socket socket{context_};
        acceptor_.accept(socket);
        read(socket);
    }

    return 0;
}

void HTTPServer::read(tcp::socket& socket) {
    http::read(socket, buffer_, request_, ec_);

    if (ec_ == http::error::end_of_stream) {
        return;
    }

    process_request(socket);
}

void HTTPServer::process_request(tcp::socket& socket) {
    if (request_.method() == http::verb::post) {
        if (request_.target() == "/upload") {
            response_.version(11);   // HTTP/1.1
            response_.result(http::status::ok);
            response_.set(http::field::server, "Beast");

            fs::create_directory("output");
            json::value parsed;
            parsed = json::parse(request_.body());
            std::string link = json::serialize(parsed.get_object().begin()->value());
            boost::erase_all(link, "\"");
            bp::system(ffmpeg, bp::args({"-i", link, "-b:v", "1M", "-g", "60", "-hls_time", "2", "-hls_list_size", "0", "output/output.m3u8"}));
            
            response_.body() = "Video playlist was placed in " + fs::current_path().string() + "/output" + '\n';
            response_.prepare_payload();
        } else if (request_.target() == "/clean") {
            response_.version(11);   // HTTP/1.1
            response_.result(http::status::ok);
            response_.set(http::field::server, "Beast");

            fs::remove_all("output");

            response_.body() = "Output files were cleaned.\n";
            response_.prepare_payload();
        } else {
            return;
        }

        write(socket);
    }
}

void HTTPServer::write(tcp::socket& socket) {
    http::write(socket, response_);
}
