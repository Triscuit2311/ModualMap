# ModuleMap
Class for getting all modules of the current process into a map without walking the PEB.

It's easier to just walk the PEB and grab the modules that way, but this works too using the Windows API.
