// TODO: Fill out your copyright notice and run the 'copyright-update' script

#include "breached-teamspeak/core/plugin.h"
#include "breached-teamspeak/teamspeak.h"

#include "teamspeak/public_definitions.h"

#define PATH_BUFSIZE 512

using namespace breached::teamspeak;

/*--------------------------------------------------------------------------------------------------------------------*/
// PluginBase: Construction/Destruction

PluginBase::PluginBase(const std::string pluginID, QObject* parent)
    : Super(parent)
    , pluginID(pluginID)
{

}

int PluginBase::Initialize()
{
    // TODO: Convert to internal logging library
    GetTS3Functions().logMessage("Plugin: Starting initialization", LogLevel::LogLevel_INFO, pluginID.c_str(), 0);

    // Initial Testing path vars
    char appPath[PATH_BUFSIZE];
    char resourcesPath[PATH_BUFSIZE];
    char configPath[PATH_BUFSIZE];
    char pluginPath[PATH_BUFSIZE];

    GetTS3Functions().getAppPath(appPath, PATH_BUFSIZE);
    GetTS3Functions().getResourcesPath(resourcesPath, PATH_BUFSIZE);
    GetTS3Functions().getConfigPath(configPath, PATH_BUFSIZE);
    GetTS3Functions().getPluginPath(pluginPath, PATH_BUFSIZE, pluginID.c_str());

    char buff[100];
    snprintf(buff, sizeof(buff), "PLUGIN: App path: %s\nResources path: %s\nConfig path: %s\nPlugin path: %s\n", appPath, resourcesPath, configPath, pluginPath);
    GetTS3Functions().logMessage(
        buff, 
        LogLevel_INFO, 
        pluginID.c_str(), 
        0
    );

    // TODO: Convert to internal logging library
    GetTS3Functions().logMessage("Plugin: Successfully initialized plugin", LogLevel::LogLevel_INFO, pluginID.c_str(), 0);
    return 0;
}

void PluginBase::Configure()
{}

void PluginBase::Shutdown() 
{

}

/*--------------------------------------------------------------------------------------------------------------------*/
