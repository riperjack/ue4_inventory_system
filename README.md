# UE4 inventory system


## General information

This is my implementation of inventory system in UE4. Design was inspired by survival games like Minecraft, Rust, Dayz, etc. It was implemented in C++ and Blueprints. 

### Current features
* Detecting pickupable items with raytrace
* Drag and dropping items
* Swapping 2 items
* Dialog displaying item properties (name, damage, etc.) on mouse over
* Context menu visible after right click, displaying item actions, like "Equip" or "Drop"
* Highlight slot on mouse over 

### Planned features
* Stacking items of the same class
* Multiplayer support
* Possibility to loot chests, drawers and other containers and move items between them and inventory


## Usage
1. Clone the project
2. Open the project with Unreal Engine ( I used v.4.21, I have not verified compatibility with other versions )
3. Click 'File' -> 'Refresh Visual Studio Project'
4. Click 'Compile'
5. Open all the widgets from "Content/FirstPerson/UI" and for each of them click "Graph" and then "Refresh all nodes"
6. Click "Play"

## Controls
* Movement: WSAD
* Pickup item: 'E'
* Show / hide inventory: 'I'
* Drag and drop items: 'LMB'
* Item actions: 'RMB'

## Demo

![Alt Text](https://github.com/riperjack/ue4_inventory_system/raw/master/Docs/video.gif)


HQ demo available at:
https://www.youtube.com/watch?v=If1VznM4SrE

## Credits
* Weapon models made by "Knife":
 https://www.blendswap.com/blends/view/88429