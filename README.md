# So Bee It!

Welcome to the repository for our  [Cocos2d-x](https://cocos2d-x.org/) based mobile game.

'So Bee It' is an economy simulation game, playable only in  German, about keeping your own bees and tending to their needs.

The goal is to earn as much money as possible, as well as to  keep growing and expanding your hive population.

All interactions with the game are by single-touch, the game should be simple enough to be enjoyed by all age groups and includes small context-sensitive informational pop-ups.

## Installation

There is a folder called 'deploy', that includes an unsigned .apk for use with android devices. Functionality has been tested for Android Version 6.0 up to 9.0 devices, but it should be compatible with devices running 3.0 or higher that have at least HD resolution.

## Developing

1. Install the Cocos2d-x framework, we will assume you followed the official [tutorial on GitHub](https://github.com/cocos2d/cocos2d-x). 
2. Download NDK, SDK, JRE seperately or simply use Android Studio (all devs used this) to handle and track dependencies and ease the troubleshooting process. All can be gotten from [Google Developers](https://developer.android.com/)
3. Any IDE can be used, but we recommend [CLion](https://www.jetbrains.com/clion/) for Unix systems, Android Studio for Windows and Mac.
4. For editing the TileMap, we recommend [Tiled](https://www.mapeditor.org/) 

You should now be able to use Cocos2d-x specific functions, make changes to our code as well as compile and run it on Android. In case of issues or questions, head on over to their [GitBook documentation](https://docs.cocos2d-x.org/cocos2d-x/en/)
For specific coding questions, either the [api-ref](https://docs.cocos2d-x.org/api-ref/) is great, or alternatively you can search the [forums](https://discuss.cocos2d-x.org/) 

## Folder Hierarchy
- Classes Folder: This includes all base classes and their corresponding header files, organized thematically by folder. Notable are the AppDelegate files for general Cocos2d-x configurations as well as the Observer and Observable that are implemented by classes that use the corresponding functionality. 
- Ressources Folder: any image or sprite sources, usually in .png format, that is required for our project. 'TileMap' includes the HD and SD tileMap created with [Tiled](https://www.mapeditor.org/) that can also be edited with the same open-source software
- proj.android / proj.ios_mac / proj.linux / projwin32:  used for the corresponding operating system when compiling and running the project on that system. Do note that only proj.android is actively maintained and focused on
- deploy: includes the unsigned apk for installation
- cocos2d: any and all resources used by cocos2d-x, includes documentation, tests and template classes

## Troubleshooting

Your IDE of choice should return mistakes in your code, but at times it may refer to Cocos2d-x base classes instead of your source or header files, which means that you either made a mistake in your logic or you tried to do something that Cocos2d-x can't handle. In 99% of cases it's the first and not the second situation  ;-)

## Usage

Any questions regarding the usage of any part of this project or  its assets should be directed to  [Abilium GmbH](https://abilium.com/), as this was done by students at the university of Berne in the lecture Praktikum Software Engineering for the IT Company.