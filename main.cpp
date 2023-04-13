#include <flow/program_options.hpp>

int main(int argc, char* argv[]) {
    if (flow::process::running_as_root()) {
        std::cerr << "You must not to run this application as root. Root privileges will be requested if necessary\n";
        return 0;
    }

    auto [desc, vm] = flow::program_options::parse(argc, argv);

    if (vm.count("help")) {
        std::cout << desc;
        return 0;
    }

    flow::program_options::process(vm, !vm.count("no-root"));

    return 0;
}
