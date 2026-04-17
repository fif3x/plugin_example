#ifndef PLUGIN_LOADER
#define PLUGIN_LOADER

#include <vector>
#include <string>
#include <optional>

namespace pluginloader {
    std::vector<std::string> locate_plugins();
    void load_plugin_symbol(std::vector<std::string> plugins, std::string symbol, std::optional<const char*> var); // symbol is for dlsym()
}

#endif

/*
int main()  
{
    HMODULE b = LoadLibraryA(path);
    int* m = reinterpret_cast<int*>(GetProcAddress(b, "idk"));
    if (m == 0) { return 1; }
    std::cout << *m << "\n";

}

dll code
extern "C" {
    __declspec(dllexport) int idk = 3897;
 }

prints out 3897
*/