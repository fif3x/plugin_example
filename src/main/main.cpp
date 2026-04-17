#include <iostream>
#include <vector>
#include <string>
#include "../../include/main/pluginloader.h"

int main(){

    namespace pl = pluginloader;
    
    std::vector<std::string> plugins = pl::locate_plugins();
    
    pl::load_plugin_symbol(plugins, "start", {});
    

    std::string input = { };

    std::cout << "---------------------\n";

    pl::load_plugin_symbol(plugins, "before_prompt", {});

    std::cout << "INPUT: ";

    pl::load_plugin_symbol(plugins, "after_prompt", {});

    std::getline(std::cin, input);

    pl::load_plugin_symbol(plugins, "input", input.c_str());


    return 0;
}