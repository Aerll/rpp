#ifndef RPP_APP_HPP
#define RPP_APP_HPP

#include <filesystem>
#include <optional>
#include <string>
#include <vector>
#include <cstdint>

struct Cli {
    std::vector<std::filesystem::path> inputFiles;
    std::optional<std::filesystem::path> output;
    std::optional<int64_t> stack;
    std::vector<std::filesystem::path> includes;
    bool skipPreprocessor;
    bool pause = true;
};

class App final {
public:
    static Cli parseCli(int argc, char** argv);
    static int exec(const Cli& cli);
    static void pause();
};

#endif // RPP_APP_HPP
