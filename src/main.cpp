
#include "compress.hpp"

namespace Options = boost::program_options;

int main(int argc, char *argv[])
{
    std::vector<std::string> filenames;

    Options::options_description generic("Generic Options");
    generic.add_options()
        ("help", "Display this help menu and exit.")
        ("version", "Display program version information and exit.")
    ;

    Options::options_description exec("Execution Options");
    exec.add_options()
        ("verbose,v", "Display detailed information during program execution")
    ;

    Options::options_description config("Configuration Options");
    config.add_options()
        ("algorithm", Options::value<std::string>(), "Specify the compression algorithm to use")
        ("filename,F", Options::value<std::vector<std::string>>(&filenames)->composing(), "Name of file(s) to compress")
    ;

    Options::options_description desc("Program Options");
    desc
        .add(generic)
        .add(exec)
        .add(config);
    
    Options::positional_options_description pos;
    pos.add("filename", -1);

    Options::variables_map vm;
    Options::store(
        Options::command_line_parser(argc, argv)
            .options(desc)
            .positional(pos)
            .run(),
        vm);
    Options::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;

        return EXIT_SUCCESS;
    }

    if (vm.count("version")) {
        std::cout << "<Program Version Info>" << std::endl;

        return EXIT_SUCCESS;
    }

    if (!vm.count("filename")) {
        // If no filename(s) was/were specified, notify the user and
        // exit with an error status.
        std::cerr << "No file(s) specified." << std::endl;

        return EXIT_FAILURE;
    }

    std::cout << "Files to compress: " << std::endl;

    for (const auto& filename : filenames) {
        std::cout << "\t" << filename << std::endl;
    }

    return EXIT_SUCCESS;
}
