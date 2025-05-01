### Hand To Hand Strength Cap Remover
Oblivion Remastered will cap a player's Strength to 100 in damage calculations with
``` 
  if (100 < Strength) {
    Strength = 100;
  }
``` 
The Assembly Instruction:
``` 
14684a835 0f  4f  d8       CMOVG      EBX ,EAX
``` 

This replaces the CMOVG instruction with a NOP instruction, removing the check and the cap.

## Build

### Requirements
* [XMake](https://xmake.io) [2.8.2+]
* C++23 Compiler (MSVC, Clang-CL)

```
git clone --recurse-submodules https://github.com/Baestus/OBSE64_Hand_To_Hand_Strength_Cap_Remover.git
``` 
``` 
cd OBSE64_Hand_To_Hand_Strength_Cap_Remover
```
``` 
xmake build
```

## Install
Place the StrengthCapRemover.dll in
``` 
OblivionRemastered\Binaries\Win64\obse\plugins
```
then run the game through OBSE64.