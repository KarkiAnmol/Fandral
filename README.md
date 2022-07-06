# Fandral

## What is it ?
It is simply a text editor.

## What is so special about it ?
Say if your touchpad stops working for some weird reason, then you are left with half functioning device which makes it very difficult for navigation while editing text. This editor will help you in such condition.

Jokes aside, Fandral integrates command line like featues of [vim](https://www.vim.org/ "the ubiquitous text editor") into a simple editor like notepad. You have both the GUI and cli environment at your disposal for faster text editing. There are also some handy features like pinch to zoom, code highliting and floating tabs which can be docked to different sides.

## Why should I use this and not some vscode extension ?
vscode has it's own place. If you're a person who does text editing a lot and want to do so more efficiently without leaving the comfort zone, then this is for you. We're not saying, vscode coupled with extension won't do the same job but seriously, what can't the vscode do coupled with the extension. Also, Fandral is faster and has different colors.
And Fandral text editor isn't intended for complex programming, it's intended for tasks which notepad does the best, smaller day to day stuffs.

## Building instructions
[BUILDING.md](https://github.com/Ciper100/Fandral/blob/gitpod/BUILDING.md)

## Can i install it ?
Not yet. Due to library limitation for static builds, the shipped version won't function properly so, there are no releases yet.

## How to use it ?
You can learn about the featues and how to use command line in the help section. There isn't much to learn if you're a little familiar with vim. Only few features are implemented for now, at to make it easier to use for most repeated tasks like copy-paste, delete, save etc.

## Why is it incomplete ?
It is a semester project which was carried out in a very short period and in much hurry. Different parts of this project is awaiting research. Such problems combined by problems imposed by library and platforms is the reason for current state of this project. 


## What doesn't work ?
- Code highliting doesn't work properly for implemented languages.
- Code highliting isn't implemented for many languages.
- The dark theme isn't applied proplerly in windows because of win32 api limitation of wxWidgets.
- wxWidgets library needs to be installed separately.
- help pages maynot function properly if help pages aren't present in resources folder.
