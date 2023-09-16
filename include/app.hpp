#ifndef RPP_APP_HPP
#define RPP_APP_HPP

#include <filesystem>
#include <optional>
#include <string>
#include <vector>

struct Cli {
    std::vector<std::filesystem::path> inputFiles;
    std::optional<std::filesystem::path> output;
    std::optional<long long> stack;
    std::vector<std::filesystem::path> includes;
    bool skipPreprocessor;
    bool silent;
};

class App final {
public:
    static Cli parseCli(int argc, char** argv);
    static int exec(const Cli& cli);
    static void pause();
};

#endif // RPP_APP_HPP
