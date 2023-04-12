#include "flow/program_options.hpp"

int main(int argc, char* argv[]) {
    auto [desc, vm] = flow::program_options::parse(argc, argv);
    flow::program_options::process(vm);

    return 0;
}