# colorize

### About
This library allows you to recolor your any pEntity (peds, vehicles, ...) in GTA SA in RGBA format (yes, you can also make entity transparent).  
Targets only selected entities. Other entities with same model would be stay original.

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