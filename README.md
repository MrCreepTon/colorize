# colorize

### About
This library allows you to recolor your any pEntity (peds, vehicles, ...) in GTA SA in RGBA format (yes, you can also make entity transparent).  
Targets only selected entities. Other entities with same model would be stay original.
<img width="417" height="569" alt="image" src="https://github.com/user-attachments/assets/3f9a2a07-54f0-4961-bc25-94e2b74f5cb8" />

### Requirements
- GTA:SA 1.0 US
- Moonloader

### Functions
| Function                        | Description                     |
|---------------------------------|---------------------------------|
| colorPed(pedHandle, r, g, b, a) | Colors ped in specific color    |
| uncolorPed(pedHandle)           | Restores ped color              |
| color(pEntity, r, g, b, a)      | Colors entity in specific color |
| uncolor(pEntity)                | Restores entity color           |

Last 2 functions are universal and may be applied to any entity. First 2 functions relieve you from getting ped pointer and make color process a bit easier.

### Examples
Examples can be found [here](/examples)
