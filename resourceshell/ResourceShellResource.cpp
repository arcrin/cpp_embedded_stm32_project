#include "ResourceShellResource.h"  

void ResourceShellResource::Init() {}

CommandHandler(ResourceShellResource::Handler) {
    switch (Command) {
        case PING: {
            Output = "pong";
            return SHELLERR::OK;
        }
        default: {
            break;  
        }
    }
    return SHELLERR::IMPLEMENTATION;
}