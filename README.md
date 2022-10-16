*This code is released for free without any warranty or liability! Licensed under the [MIT License](LICENSE).*
# ModuleMap

Class for getting all modules of the current process into a map. While it may be easier to just walk the PEB and grab the modules that way, this works using the Windows API.

### Why?

Purely POC. I saw something like this being employed by some malware, so I thought I would write my own implementation. I've found it useful in a few dynamic analysis situations where we want to enumerate the loaded modules of a process.
