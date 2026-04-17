# INSTRUCTIONS

1. Make sure you have `g++` and `make` installed.

2. 
- For Linux, create a directory in `~/.config/` named `libreterminal`, and then inside that folder, create another directory named `plugins`, so the directory `~/.config/libreterminal/plugins` exists.
- For Windows, create a directory in the disk you are using (which is probably `C:\\`) named `libreterminal` and then inside that folder a directory named `plugins`, so the directory `C:\\libreterminal\\plugins` exists.

3. Go in the extracted folder of this program, navigate to the `build/` folder, and run the needed file (`build.sh` for Linux, `build.bat` for Windows)

4. `cd` back to the root of the project and navigate to the directory `include/main`

5. Use the command `g++ -shared -fPIC -o plugin_example.so plugin_example.cpp` if you are on Linux, and `g++ -shared -fPIC -o plugin_example.dll plugin_example.cpp` if you are on Windows. You can change what the output file will be where it says `plugin_example.so/.dll`.

6. Navigate back to the root of the project, then on the bin directory, and run the `lt-plugin(.exe)` file. Press the option '2', on the "Plugin Location" input, put "/home/(youruser)/(folder_to_the_project)/include/main/(your_plugin_name).so" if you are on Windows and "C:\\(folder_to_the_project)\\include\\main\\(your_plugin_name).dll"

7. On the "Plugin name" input, put your plugin name.

8. Leave the lt-plugin program, navigate back to the `bin` folder of the project, and run the `main(.exe)` file. If the instructions are followed correctly, you should be able to see the outputs of the plugins, based on the code of the file compiled before (`plugin_example.cpp`)

9. Modify what the functions in `plugin_example.cpp` do, recompile it, use the `lt-plugin` program again to "Add plugin", and rerun the `main` program without recompiling, and see if the outputs have changed