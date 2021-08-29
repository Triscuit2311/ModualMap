#include "ModuleMap.h"

std::map<std::string, uintptr_t> ModuleMap::GetModuleMap(std::vector<std::string> moduleFilter) {
    // Allocate space for modules to be stored
    HMODULE modules [1024];
    
    // Necessary callback for EnumProcessModules
    DWORD numOfModules;
    
    // Temporary map to store modules and addresses in 
    std::map<std::string,uintptr_t> moduleMap;
    
    // On success returns true and stores the following:
    //      modules -> modules[]
    //      number of modules -> numOfModules
    if(EnumProcessModules(GetCurrentProcess(),modules,sizeof(modules),&numOfModules)){
        
        // Iterate though modules
        for(UINT i = 0; i<(numOfModules/sizeof(HMODULE));i++){
            
            // Storage for Module path
            TCHAR currModulePath[MAX_PATH];
            
            // Get module path and store in currModulePath
            if(GetModuleFileNameA(modules[i],currModulePath,sizeof(currModulePath))){

                // Create path var from current module
                std::filesystem::path currPath(currModulePath);

                // Get the module base for the current module
                uintptr_t thisModuleBaseAddr =
                        (uintptr_t)GetModuleHandle(                 // Cast to uintptr_t
                        currPath.filename().string().c_str());      // Path.filename - > std::string -> LPCSTR

                // If there is any modules in the filter
                if(!moduleFilter.empty()){
                    // Check if the filter contains this module
                    // Add it to our temporary map if it does.
                    if(std::find(moduleFilter.begin(), moduleFilter.end(),
                                 currPath.filename().string()) != moduleFilter.end()) {
                        moduleMap[currPath.filename().string()] = thisModuleBaseAddr;
                    }
                } else {
                    // If the filter is empty, add all modules.
                    moduleMap[currPath.filename().string()] = thisModuleBaseAddr;
                }
            }
        }
    }
    // Return our temporary map
    return moduleMap;
}


uintptr_t ModuleMap::RetrieveModuleBase(const std::string& moduleName) {
    if(!map.contains(moduleName)){
        std::cout << "INFO: module [" << moduleName << "] is not in module map.\n";
        return 0;
    }
    return map.at(moduleName);
}

void ModuleMap::PrintModulesToConsole() {
    for (auto &item : map) {
        std::cout << "\t["<< item.first << " : 0x";
        std::cout << std::hex << std::uppercase << item.second << std::nouppercase << std::dec << "]\n";
    }
}
