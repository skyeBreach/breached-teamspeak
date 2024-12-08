// TODO: Fill out your copyright notice and run the 'copyright-update' script

#pragma once

#include <QtCore/QObject>

/*--------------------------------------------------------------------------------------------------------------------*/
// 

/**
 * @brief 
 */
class PluginBase: public QObject
{
    Q_OBJECT

    // TODO: Is this private or public?
    typedef QObject Super;

/*--------------------------------------------------------------------------------------------------------------------*/
// Construction, Initialization, and Destruction

public:
    /**
     * @brief 
     * 
     * @param pluginID 
     * @param parent 
     */
    PluginBase(const std::string pluginID, QObject* parent = nullptr);

    int Initialize();

    void Configure();

    void Shutdown();

/*--------------------------------------------------------------------------------------------------------------------*/
// Plugin Information

protected:
    /** The constant string identifier used for this plugin within TeamSpeak */
    const std::string pluginID;
    
/*--------------------------------------------------------------------------------------------------------------------*/

};

/*--------------------------------------------------------------------------------------------------------------------*/
