#pragma once
#include "IOResource.h"

class ResourceShellResource : public IOResource {
    public:
        constexpr ResourceShellResource() = delete;
        constexpr ~ResourceShellResource() = delete;

        static void Init(); 
        static CommandHandler(Handler);

        CMD_MAP(
            PING, "Dummy command that returns \"pong\". Use this to test connectivity.",
        )
};