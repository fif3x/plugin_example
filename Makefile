CXX = g++
CXXFLAGS := -c
OBJFILES_RM := main.o pluginloader.o lt-plugin.o

main: main.o pluginloader.o
	@echo "Building main"
	$(CXX) main.o pluginloader.o -o main

lt-plugin: lt-plugin.o
	@echo "Building lt-plugin"
	$(CXX) lt-plugin.o -o lt-plugin

main.o: src/main/main.cpp
	$(CXX) $(CXXFLAGS) src/main/main.cpp

pluginloader.o: src/main/pluginloader.cpp
	$(CXX) $(CXXFLAGS) src/main/pluginloader.cpp

lt-plugin.o: src/main/lt-plugin.cpp
	$(CXX) $(CXXFLAGS) src/main/lt-plugin.cpp

clean:
	@echo "Removing object files"
	rm $(OBJFILES_RM)