#pragma once

#include <iostream>
#include <flow/filesystem.hpp>

namespace flow::program_options::detail {

    template <typename Error, typename Fn, typename... Args>
    bool invoked_without_error(Fn&& fn, Args&&... args) noexcept(std::is_nothrow_invocable_v<Fn, Args...>) {
        try {
            std::invoke(std::forward<Fn>(fn), std::forward<Args>(args)...);
            return true;
        }
        catch (Error& e) {
            std::cout << e.what() << std::endl;
            return false;
        }
    }

    template <typename Fn, typename... Args>
    bool invoked_without_file_error(Fn&& fn, Args&&... args) noexcept(std::is_nothrow_invocable_v<Fn, Args...>) {
        return invoked_without_error<filesystem::file_error>(std::forward<Fn>(fn), std::forward<Args>(args)...);
    }

} // namespace flow::program_options::detail
