#pragma once

#include <unistd.h>
#include <string_view>
#include <boost/process.hpp>

namespace flow::process {

    [[nodiscard]] bool running_as_root() noexcept {
        return getuid() == 0;
    }

    int run(std::string_view args) {
        return boost::process::system(args.data(), boost::process::std_out > stdout, boost::process::std_err > stderr);
    }

    int run_as_root(std::string_view args) {
        return run(std::string("sudo -S ") + args.data());
    }

} // namespace flow::process
