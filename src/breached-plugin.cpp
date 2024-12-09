// TODO: Fill out your copyright notice and run the 'copyright-update' script

#include "breached-plugin.h"

#include "teamspeak/public_definitions.h"
#include "ts3_functions.h"

#define PATH_BUFSIZE 512


static struct TS3Functions teamspeakFunctions;

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
    teamspeakFunctions.logMessage("Plugin: Starting initialization", LogLevel::LogLevel_INFO, pluginID.c_str(), 0);

    // Initial Testing path vars
    char appPath[PATH_BUFSIZE];
    char resourcesPath[PATH_BUFSIZE];
    char configPath[PATH_BUFSIZE];
    char pluginPath[PATH_BUFSIZE];

    teamspeakFunctions.getAppPath(appPath, PATH_BUFSIZE);
    teamspeakFunctions.getResourcesPath(resourcesPath, PATH_BUFSIZE);
    teamspeakFunctions.getConfigPath(configPath, PATH_BUFSIZE);
    teamspeakFunctions.getPluginPath(pluginPath, PATH_BUFSIZE, pluginID.c_str());

    char buff[100];
    snprintf(buff, sizeof(buff), "PLUGIN: App path: %s\nResources path: %s\nConfig path: %s\nPlugin path: %s\n", appPath, resourcesPath, configPath, pluginPath);
    teamspeakFunctions.logMessage(
        buff, 
        LogLevel_INFO, 
        pluginID.c_str(), 
        0
    );

    // TODO: Convert to internal logging library
    teamspeakFunctions.logMessage("Plugin: Successfully initialized plugin", LogLevel::LogLevel_INFO, pluginID.c_str(), 0);
    return 0;
}

void PluginBase::Configure()
{}

void PluginBase::Shutdown() {}

/*--------------------------------------------------------------------------------------------------------------------*/
