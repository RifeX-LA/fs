#pragma once

#include <flow/program_options/file_ops.hpp>
#include <flow/program_options/detail/args_processing.hpp>

namespace flow::program_options {

    [[nodiscard]] auto parse(int argc, char* argv[]) {
        namespace po = boost::program_options;

        po::options_description desc("Options");
        desc.add_options()
            ("help,h", "Show help")
            ("zip", po::value<std::string>(), "Create zip archive with given file")
            ("hash", po::value<std::string>(), "Computes SHA-256 hash of given file")
            ("lines", po::value<std::string>(), "Get file's rows number")
            ("check-path", "Do options with path's existence checking");

        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv).options(desc).run(), vm);
        po::notify(vm);

        return std::pair(std::move(desc), std::move(vm));
    }

    void process(const boost::program_options::variables_map& vm, bool try_as_root = false) {
        detail::process_cmd_arg(vm, "hash", hash, try_as_root);
        detail::process_cmd_arg(vm, "zip", zip, try_as_root);
        detail::process_cmd_arg(vm, "lines", lines_count, try_as_root);
    }

} // namespace flow::program_options
