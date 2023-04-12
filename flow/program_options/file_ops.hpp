#pragma once

#include <flow/filesystem.hpp>
#include <flow/program_options/detail/invoked_without_error.hpp>

namespace flow::program_options {

    bool zip(const std::filesystem::path& file) {
        return detail::invoked_without_file_error(filesystem::zip, file);
    }

    bool hash(const std::filesystem::path& file) {
        auto hash_path = file.string() + ".hash";
        auto write_hash = [&](){filesystem::write_to_file(hash_path, filesystem::hash(file));};
        return detail::invoked_without_file_error(write_hash);
    }

    bool lines_count(const std::filesystem::path& file) {
        auto print_lines_count = [&]() {
            auto lines = filesystem::lines_count(file);
            std::cout << file.string() << " : lines count: " << lines << std::endl;
        };

        return detail::invoked_without_file_error(print_lines_count);
    }

} // namespace flow::program_options
