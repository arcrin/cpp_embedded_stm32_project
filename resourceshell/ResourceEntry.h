#pragma once
#include "macro_enum_map.h"
#include "Searchable.h" 
#include "IOResource.h"
#include "ResourceShellResource.h"

#define RESOURCE_MAP_CREATE_ENTRY(cls, help) RESOURCE_MAP_GET_VALUE(#cls, cls, help)
#ifdef RESOURCE_SHELL_ENABLE_HELP
#define RESOURCE_MAP_GET_VALUE(name, cls, help)             \
    {                                                       \
        name,                                               \
        cls::Init,                                          \
        cls::Handler,                                       \
        cls::Task,                                          \
        cls::CmdMap,                                        \
        (sizeof(cls::CmdMap) / sizeof(cls::CmdMap[0])),     \
        help                                                \
    }
#else
#define RESOURCE_MAP_GET_VALUE(name, cls, help)             \
    {                                                       \            
        name,                                               \ 
        cls::Init,                                          \ 
        cls::Handler,                                       \
        cls::Task,                                          \
        cls::CmdMap,                                        \
        (sizeof(cls::CmdMap) / sizeof(cls::CmdMap[0])),     \                        
    }
#endif

#define RESOURCE_MAP(...) \
MAKE_MAP(static constexpr const ResourceEntry ResourceInfo[], \
RESOURCE_MAP_GET_VALUE("_shell", Resource))