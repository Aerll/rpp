# About
**rules++** is a simple language written in C++, which allows you to create the most complex automappers.

## Getting started
To start using **rules++**, you need 3 files, which you can grab from [here](https://github.com/Aerll/rpp/releases/tag/v1.0.0):
  - an executable, which translates **rules++** code to **rules**
  - **base.r** - an implementation of the most common functions
  - **base.p** - a collection of useful presets
  
A tutorial, explaining every feature in detail, is available on the [wiki](https://github.com/Aerll/rpp/wiki).

## Utilities for Notepad++
Utilities include syntax highlighting and auto completion. Preferable theme can be found [here](https://github.com/cydh/VS2015-Dark-Npp).<br/>
Don't forget to check _Enable global background colour_ in _Settings -> Style Configurator..._

## Extension for VS Code
This extension supports basic syntax highlighting. To install it follow [this](https://code.visualstudio.com/docs/editor/extension-marketplace#_install-from-a-vsix) guide.<br/>
<br/>
After installing, open your folder in vs code and paste the following snippet into _settings.json_ file, which can be accessed via _Ctrl+Shift+P -> Preferences: Open Workspace Settings (JSON)_:
```json
{
    "workbench.colorTheme": "rpp",
    "workbench.preferredDarkColorTheme": "rpp",
    "workbench.preferredHighContrastColorTheme": "rpp",
    "workbench.preferredLightColorTheme": "rpp"
}
```
