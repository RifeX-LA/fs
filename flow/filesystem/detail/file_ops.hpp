#pragma once

#include <concepts>
#include <filesystem>
#include <boost/algorithm/hex.hpp>

namespace flow::filesystem::detail {

    template <typename FStream, typename Exception>
    FStream create_fstream(const std::filesystem::path& path) {
        FStream fstream(path);
        if (fstream.fail()) {
            throw Exception(path);
        }
        return fstream;
    }

    std::ofstream create_ofstream(const std::filesystem::path& path) {
        return create_fstream<std::ofstream, write_error>(path);
    }

    std::ifstream create_ifstream(const std::filesystem::path& path) {
        return create_fstream<std::ifstream, read_error>(path);
    }

    void check_write_access(const std::filesystem::path& file) {
        create_ofstream(file);
        std::filesystem::remove(file);
    }

    template <std::ranges::input_range R>
    std::string hex(R&& r) {
        std::string output;
        if constexpr (std::ranges::sized_range<R>) {
            output.reserve(std::ranges::size(r) * 2);
        }
        boost::algorithm::hex_lower(r, std::back_inserter(output));

        return output;
    }

} // flow::filesystem::detail
