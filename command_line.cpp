#include <iostream>

int main(int argc, char** argv) {
    // argc will be the number of strings pointed to by argv.
    // This will (in practice) be 1 plus the number of arguments.
    // Equally int main(int num_args, char** arg_strings)
    // Try the command: ./command test1 test2 test3 test4

    std::cout << "Have " << argc << " arguments:" << std::endl;
    for (int i = 0; i < argc; ++i) {
        std::cout << argv[i] << std::endl;
    }
}
