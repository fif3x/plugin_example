#include <iostream>
#include <string>

// g++ -shared -fPIC -o plugin_example.so plugin_example.cpp

#ifdef _WIN32
    #define PLUGIN_EXPORT extern "C" __declspec(dllexport)
    #include <windef.h>
    #include <libloaderapi.h>
#else
    #define PLUGIN_EXPORT extern "C"
#endif

PLUGIN_EXPORT void start(){
    std::cout << "start plugin example" << std::endl;
}

PLUGIN_EXPORT void before_prompt(){
    std::cout << "before prompt plugin example" << std::endl;
}

PLUGIN_EXPORT void after_prompt(){
    std::cout << "after prompt plugin example" << std::endl;
}

PLUGIN_EXPORT void input(const char* input){
    std::cout << "input plugin example. input and HI will be displayed " << input << " HI" << std::endl;
}