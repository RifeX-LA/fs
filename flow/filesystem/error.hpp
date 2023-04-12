#pragma once

#include <utility>
#include <stdexcept>
#include <filesystem>

namespace flow::filesystem {

    struct file_error : std::runtime_error {
        explicit file_error(const std::filesystem::path& path, const std::string& msg = "") : std::runtime_error(path.string() + msg) {}
    };

    struct read_error : file_error {
        explicit read_error(const std::filesystem::path& p) : file_error(p.string(), " : can't open this file") {}
    };

    struct write_error : file_error {
        explicit write_error(const std::filesystem::path& p) : file_error(p.string(), " : can't create this file") {}
    };

} // namespace flow::filesystem
