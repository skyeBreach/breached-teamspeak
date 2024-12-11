#include "breached-teamspeak/teamspeak.h"

static struct TS3Functions tsFunctions;

void breached::teamspeak::SetTS3Functions(const struct TS3Functions funcs)
{
    // Only set the function ptrs if they have not been set previously
    if(tsFunctions.getClientLibVersion == nullptr) 
    {
        tsFunctions = funcs;
        return;
    }
    // TODO: if so then we need to create a debug warning 
}

TS3Functions breached::teamspeak::GetTS3Functions()
{
    return tsFunctions;
}