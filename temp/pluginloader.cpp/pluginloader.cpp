#include "../../include/main/pluginloader.h"

#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <optional>

#ifdef __linux__

#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>

#define LIN

#elif defined(_WIN32)

#include <windows.h>

#define WIN

#endif


namespace fs = std::filesystem;
namespace pl = pluginloader;

std::vector<std::string> pl::locate_plugins(){
    std::string path = fs::path(std::getenv("HOME")) / ".config/libreterminal/plugins";

    std::vector<std::string> files = { };

    for (const auto & entry : fs::directory_iterator(path)){
        std::cout << "Found file: " << entry.path() << std::endl;
        
        if(fs::is_regular_file(fs::status(entry.path().string()))){
            files.push_back(entry.path().string());
        }
    
    }

    std::cout << std::endl;


    for(int index = 0; index < files.size();){
        #ifdef LIN
        if (files.at(index).find(".so") != std::string::npos) {
            index++;
        } else {
            files.erase(files.begin() + index);
        }
        #elif defined(WIN)
        if (files.at(index).find(".dll") != std::string::npos) {
            index++;
        } else {
            files.erase(files.begin() + index);
        }
        #endif
    }
    

    return files;
}

void pl::load_plugin_symbol(std::vector<std::string> plugins, std::string symbol, std::optional<const char*> var){ // symbol is for dlsym()

    for(int index = 0; index < plugins.size(); index++){

        void *handle;
        handle = dlopen(plugins.at(index).c_str(), RTLD_LAZY);
        char* error;

        
        if(symbol == "start"){
            #ifdef LIN

            void (*start)();

            if(!handle){
                fputs(dlerror(), stderr);
                exit(1);
            }

            // start = dlsym(handle, symbol.c_str()); --- IGNORE ---
            start = reinterpret_cast<void (*)()>(dlsym(handle, symbol.c_str()));

            if((error = dlerror()) != NULL){
                fputs(error, stderr);
                exit(1);
            }

            start();

            dlclose(handle);

            #elif defined(WIN)

            void (*start)();
            HMODULE handle = LoadLibraryA(plugins.at(index).c_str());
            
            if (!handle){
                fputs("Error when loading symbol start", stderr);
                exit(1);
            }

            start = reinterpret_cast<void (*)()>(GetProcAddress(handle, symbol.c_str()));

            if (!start){
                return 1;
            }

            start();

            FreeLibrary(handle);

            #endif

        } else if (symbol == "before_prompt"){
            void (*before_prompt)();

            if(!handle){
                fputs(dlerror(), stderr);
                exit(1);
            }

            before_prompt = reinterpret_cast<void (*)()>(dlsym(handle, symbol.c_str()));

            if((error = dlerror()) != NULL){
                fputs(error, stderr);
                exit(1);
            }

            before_prompt();

            dlclose(handle);

        } else if (symbol == "after_prompt"){
            void (*after_prompt)();

            if (!handle){
                fputs(dlerror(), stderr);
                exit(1);
            }

            after_prompt = reinterpret_cast<void (*)()>(dlsym(handle, symbol.c_str()));

            if((error = dlerror()) != NULL){
                fputs(error, stderr);
                exit(1);
            }

            after_prompt();

            dlclose(handle);

        }  else if (symbol == "input") {
            void (*input)(const char*);

            if (!handle){
                fputs(dlerror(), stderr);
                exit(1);
            }

            input = reinterpret_cast<void (*)(const char*)>(dlsym(handle, symbol.c_str()));

            if((error = dlerror()) != NULL){
                fputs(error, stderr);
                exit(1);
            }

            input(var.value_or("N/A"));

            dlclose(handle);

        } else {
            std::cout << "UNKNOWN SYMBOL: " << symbol << std::endl;
        }
    }
}