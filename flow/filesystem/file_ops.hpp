#pragma once

#include <fstream>
#include <cryptox/all.hxx>
#include <libzippp/libzippp.h>
#include <flow/filesystem/error.hpp>
#include <flow/filesystem/detail/file_ops.hpp>

namespace flow::filesystem {

    bool is_correct_file_path(const std::filesystem::path& path, std::error_code& err_code) {
        return std::filesystem::exists(path, err_code) && !std::filesystem::is_directory(path);
    }

    void check_file_path(const std::filesystem::path& path) {
        std::error_code err_code;
        bool correct_path = is_correct_file_path(path, err_code);

        if (bool access_denied = err_code.value() == 13; access_denied) {
            throw file_error(path, " : can't check path's existence (access denied)");
        }

        if (!correct_path) {
            throw file_error(path, " : such file doesn't exist");
        }
    }

    template <typename T>
    void write_to_file(const std::filesystem::path& file, const T& value) {
        detail::create_ofstream(file) << value;
    }

    std::string read_from_file(const std::filesystem::path& file) {
        auto fin = detail::create_ifstream(file);
        return {std::istream_iterator<char>{fin}, std::istream_iterator<char>{}};
    }

    std::size_t lines_count(const std::filesystem::path& file) {
        auto fin = detail::create_ifstream(file);
        return std::count(std::istreambuf_iterator<char>{fin}, std::istreambuf_iterator<char>{}, '\n') + 1;
    }

    void zip(const std::filesystem::path& file) {
        auto zip_path = file.string() + ".zip";
        detail::check_write_access(zip_path);

        libzippp::ZipArchive zip(zip_path);
        zip.open(libzippp::ZipArchive::Write);

        auto file_content = read_from_file(file);
        zip.addData(file.filename(), file_content.c_str(), file_content.size());
        zip.close();
    }

    template <typename Algorithm = cryptox::sha256>
    std::string hash(const std::filesystem::path& file) {
        auto file_content = read_from_file(file);
        auto hash = cryptox::digest<Algorithm>(file_content);
        return detail::hex(hash);
    }

} // namespace flow::filesystem
