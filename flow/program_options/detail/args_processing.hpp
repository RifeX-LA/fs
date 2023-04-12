#pragma once

#include <iostream>
#include <boost/program_options.hpp>
#include <flow/process.hpp>
#include <flow/filesystem.hpp>
#include <flow/program_options/detail/invoked_without_error.hpp>

namespace flow::program_options::detail {

    std::string create_process_args(std::string_view cmd_arg, const std::filesystem::path& path, bool check_path = false) {
        std::string process_args = std::string("./root --") + cmd_arg.data() + "=" + path.string();
        if (check_path) {
            process_args += " --check-path";
        }
        return process_args;
    }

    template <typename Fn>
    void process_cmd_arg(const boost::program_options::variables_map& vm, std::string_view cmd_arg, Fn&& fn, bool try_as_root) {
        if (!vm.count(cmd_arg.data())) {
            return;
        }

        auto path = vm[cmd_arg.data()].as<std::string>();
        bool check_path_needed = vm.count("check-path");
        bool path_good = !check_path_needed || invoked_without_file_error(filesystem::check_file_path, path);

        if ((!path_good || !std::invoke(std::forward<Fn>(fn), path)) && try_as_root) {
            std::cout << "Trying as root...\n";
            process::run_as_root(create_process_args(cmd_arg, path, check_path_needed));
        }
    }

} // namespace flow::program_options::detail
