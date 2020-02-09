/* MIT License
 *
 * Copyright (c) 2019 - 2020 Andreas Merkle <web@blue-andi.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*******************************************************************************
    DESCRIPTION
*******************************************************************************/
/**
 * @brief  JustText plugin
 * @author Andreas Merkle <web@blue-andi.de>
 * 
 * @addtogroup plugin
 *
 * @{
 */

#ifndef __JUSTTEXTPLUGIN_H__
#define __JUSTTEXTPLUGIN_H__

/******************************************************************************
 * Compile Switches
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include <stdint.h>
#include "Plugin.hpp"

#include <TextWidget.h>

/******************************************************************************
 * Macros
 *****************************************************************************/

/******************************************************************************
 * Types and Classes
 *****************************************************************************/

/**
 * Shows text over the whole display.
 * If the text is too long for the display width, it automatically scrolls.
 * 
 * Change text via REST API:
 * Text: POST \c "<base-uri>/text?show=<text>"
 */
class JustTextPlugin : public Plugin
{
public:

    /**
     * Constructs the plugin.
     * 
     * @param[in] name  Plugin name
     */
    JustTextPlugin(const String& name) :
        Plugin(name),
        m_textWidget(),
        m_url(),
        m_callbackWebHandler(nullptr)
    {
        /* Move the text widget one line lower for better look. */
        m_textWidget.move(0, 1);
    }

    /**
     * Destroys the plugin.
     */
    ~JustTextPlugin()
    {
    }

    /**
     * Plugin creation method, used to register on the plugin manager.
     * 
     * @param[in] name  Plugin name
     * 
     * @return If successful, it will return the pointer to the plugin instance, otherwise nullptr.
     */
    static Plugin* create(const String& name)
    {
        return new JustTextPlugin(name);
    }

    /**
     * Register web interface, e.g. REST API functionality.
     * 
     * @param[in] srv       Webserver
     * @param[in] baseUri   Base URI, use this and append plugin specific part.
     */
    void registerWebInterface(AsyncWebServer& srv, const String& baseUri) override;

    /**
     * Unregister web interface.
     * 
     * @param[in] srv   Webserver
     */
    void unregisterWebInterface(AsyncWebServer& srv) override;

    /**
     * Update the display.
     * The scheduler will call this method periodically.
     * 
     * @param[in] gfx   Display graphics interface
     */
    void update(IGfx& gfx);

    /**
     * Set text, which may contain format tags.
     * 
     * @param[in] formatText    Text, which may contain format tags.
     */
    void setText(const String& formatText);

private:

    TextWidget                  m_textWidget;           /**< Text widget, used for showing the text. */
    String                      m_url;                  /**< REST API URL */
    AsyncCallbackWebHandler*    m_callbackWebHandler;   /**< Callback web handler */

    /**
     * Instance specific web request handler, called by the static web request
     * handler. It will really handle the request.
     * 
     * @param[in] request   Web request
     */
    void webReqHandler(AsyncWebServerRequest *request);

};

/******************************************************************************
 * Functions
 *****************************************************************************/

#endif  /* __JUSTTEXTPLUGIN_H__ */

/** @} */