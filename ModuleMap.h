#ifndef MODULEMAP_H
#define MODULEMAP_H

#include <windows.h>
#include <psapi.h>
#include <filesystem>
#include <iostream>
#include <thread>
#include <string>
#include <map>
#include <utility>
#include <vector>
#include <algorithm>

class ModuleMap {
    // Map to store module names and base addresses
    std::map<std::string,uintptr_t> map;

    // Primary function, gets all modules of currently program and populates the map
    // Takes a filter; empty filter will get all modules
    static std::map<std::string,uintptr_t> GetModuleMap(std::vector<std::string> moduleFilter);

public:
    // Constructor takes a vector of module names as a filter.
    // Filter left blank will get all modules.
    explicit ModuleMap(std::vector<std::string> moduleFilter = {}){
        map = GetModuleMap(std::move(moduleFilter));
    }

    // Assumes you have a console.
    // Prints module map in format: [<module name> : <base address>]
    void PrintModulesToConsole();

    // Lookup base address in map.
    uintptr_t RetrieveModuleBase(const std::string& moduleName);

    ~ModuleMap(){}
};


#endif //MODULEMAP_H
