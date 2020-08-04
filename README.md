# Pixelix
Full RGB LED matrix, based on an ESP32 and WS2812B LEDs.

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](http://choosealicense.com/licenses/mit/)
[![Repo Status](https://www.repostatus.org/badges/latest/wip.svg)](https://www.repostatus.org/#wip)
[![Release](https://img.shields.io/github/release/BlueAndi/esp-rgb-led-matrix.svg)](https://github.com/BlueAndi/esp-rgb-led-matrix/releases)
[![Build Status](https://travis-ci.org/BlueAndi/esp-rgb-led-matrix.svg?branch=master)](https://travis-ci.org/BlueAndi/esp-rgb-led-matrix)

![pixelix](./doc/images/pixelix.gif)

- [Pixelix](#pixelix)
- [Motivation](#motivation)
- [Overview](#overview)
- [Very First Startup](#very-first-startup)
- [Requirements](#requirements)
- [Electronic](#electronic)
- [Software](#software)
  - [IDE](#ide)
  - [Installation](#installation)
  - [Installation of test environment](#installation-of-test-environment)
  - [Build Project](#build-project)
  - [Update of the device](#update-of-the-device)
    - [Update via usb](#update-via-usb)
    - [Update over-the-air via espota](#update-over-the-air-via-espota)
    - [Update over-the-air via browser](#update-over-the-air-via-browser)
  - [Used Libraries](#used-libraries)
  - [Where to change panel topology?](#where-to-change-panel-topology)
  - [Structure](#structure)
  - [REST interface](#rest-interface)
  - [Websocket interface](#websocket-interface)
- [Issues, Ideas And Bugs](#issues-ideas-and-bugs)
- [License](#license)

# Motivation
I want to have a remote display to show multiple kind of information, running 24/7 reliable. Connected over wifi to the local network, it can be controlled via REST API or websocket.

| Some impressions |   |
| - | - |
| ![clock](./doc/images/PixelixClock.jpg) | ![date](./doc/images/PixelixDate.jpg) |
| ![photovoltic](./doc/images/PixelixPhotovoltaic.jpg) | ![pixelix](./doc/images/PixelixElectricity.jpg) |
| ![pixelix](./doc/images/PixelixWifiStatus.jpg) | ... |

# Overview
See [Overview.pdf](https://github.com/BlueAndi/esp-rgb-led-matrix/blob/master/doc/Overview.pdf).

# Very First Startup
If the device starts the very first time, the wifi station SSID and passphrase are empty. To be able to configure them, start the device and keep the button pressed. The device will then start up as wifi access point with the default SSID "pixelix" and the default password "Luke, I am your father.". The display itself will show the SSID and the IP of the webserver.
Connect to it and configure via webinterface the wifi station SSID and passphrase. Restart and voila!

# Requirements
See [requirements](https://github.com/BlueAndi/esp-rgb-led-matrix/blob/master/doc/REQUIREMENTS.md).

# Electronic
The main parts are:
* [ESP32 DevKitV1](https://github.com/playelek/pinout-doit-32devkitv1)
* WS2812B 5050 8x32 RGB Flexible LED Matrix Panel
* Power supply 5 V / 4 A

See [electronic detail](https://github.com/BlueAndi/esp-rgb-led-matrix/blob/master/doc/ELECTRONIC.md) and [bill-of-material](https://github.com/BlueAndi/esp-rgb-led-matrix/blob/master/doc/BOM.md).

# Software

## IDE
The [PlatformIO IDE](https://platformio.org/platformio-ide) is used for the development. Its build on top of Microsoft Visual Studio Code.

## Installation
1. Install [VSCode](https://code.visualstudio.com/).
2. Install PlatformIO IDE according to this [HowTo](https://platformio.org/install/ide?install=vscode).
3. Close and start VSCode again.
4. Recommended is to take a look to the [quick-start guide](https://docs.platformio.org/en/latest/ide/vscode.html#quick-start).

## Installation of test environment
1. For the test environment on windows platform, install [MinGW](http://www.mingw.org/).
    * Install as basic setup:
        * mingw-developer-toolkit-bin
        * mingw32-base-bin
        * mingw32-gcc-g++-bin
        * msys-base-bin
    * Install additional packages:
        * mingw32-libmingwex-dev
        * mingw32-libmingwex-dll
2. Place ```c:\mingw\bin``` on path.

## Build Project
1. Load workspace in VSCode.
2. Change to PlatformIO toolbar.
3. _Project Tasks -> Build_ or via hotkey ctrl-alt-b
4. Running tests with _Project Tasks -> env:native -> Test_

## Update of the device

### Update via usb
Set the following in the _platformio.ini_ configuration file:
* Set _upload_protocol_ to _esptool_.
* Clear _upload_port_.
* Clear _upload_flags_.

Build and upload the software via _Project Tasks -> Upload_ and the filesystem via _Project Tasks -> Upload File System image_.

### Update over-the-air via espota
Set the following in the _platformio.ini_ configuration file:
* Set _upload_protocol_ to _espota_.
* Set _upload_port_ to the device ip-address.
* Set _upload_flags_ to _--port=3232_ and set the password via _--auth=XXX_.

Build and upload the software via _Project Tasks -> Upload_ and the filesystem via _Project Tasks -> Upload File System image_.

### Update over-the-air via browser
1. Build and the software via _Project Tasks -> Build_ and the filesystem via _Project Tasks -> Upload File System image_.
2. Connect to the device.
3. Open browser add enter ip address of the device.
4. Jump to Update site.
5. Select firmware binary (firmware.bin) or filesystem binary (spiffs.bin) and click on upload.

## Used Libraries
* [Arduino](https://docs.platformio.org/en/latest/frameworks/arduino.html#framework-arduino) - ESP framework.
* [NeoPixelBus](https://github.com/Makuna/NeoPixelBus) - Controlling the LED matrix with hardware support (RMT).
* [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer) - Webserver.

## Where to change panel topology?
First adapt in ```./src/HAL/Board.h``` the _width_ and _height_ according your LED matrix.

In the ```./src/Gfx/LedMatrix.h``` file you have to change the member variable _m\_topo_ according to your physical panel topology. Take a look how your pixels are wired on the pcb and use the following page to choose the right one: https://github.com/Makuna/NeoPixelBus/wiki/Layout-objects

## Structure

<pre>
+---data            (All filesystem files (SPIFFS))
+---doc             (Documentation)
    +---datasheets  (Datasheets of electronic parts)
    +---design      (Design related documents)
    +---doxygen     (Sourcecode documentation)
    +---eagle-libs  (Eagle libraries)
    +---pcb         (Electronic PCB images)
    \---schematics  (Schematics)
+---include         (Include files)
+---lib             (Project specific (private) libraries)
+---src             (Sourcecode)
+---test            (Unit tests)
\---platform.ini    (Project configuration file)
</pre>

## REST interface

See [REST interface](https://github.com/BlueAndi/esp-rgb-led-matrix/blob/master/doc/REST.md).

## Websocket interface

See [websocket interface](https://github.com/BlueAndi/esp-rgb-led-matrix/blob/master/doc/WEBSOCKET.md).

# Issues, Ideas And Bugs
If you have further ideas or you found some bugs, great! Create a [issue](https://github.com/BlueAndi/esp-rgb-led-matrix/issues) or if you are able and willing to fix it by yourself, clone the repository and create a pull request.

# License
The whole source code is published under the [MIT license](http://choosealicense.com/licenses/mit/).
