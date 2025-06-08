# Starlight Engine Naming Conventions

## Introduction
This document outlines that naming conventions that were used when developing the engine and hence recommended to follow to stay consistent.

## Prefixes

### S - Starlight Object
`S` is used for **SObject**-based classes. Short for Starlight Object. This is the base class for all objects managed by the Starlight engine.
#### Examples:
* `SObject`: Base object class for all Starlight Engine objects.
* `SWorld`: Object representing the world, derives from `SObject`.

### F - Framework
`F` is used for **framework** structs. I also recommend using this prefix for any/all structs.
#### Examples:
* `FString`: String struct for chars.
* `FVector2`: Math struct for 2-dimensional points.
* `FColor`: Color struct for RGBA.
* `FInputKey`: For identifying a key.

### G - Globals
`G` is used for **global** singleton variables.
#### Examples:
* `GEngine` - Pointer to the global instance of Starlight Engine.
* `GEditor` - Pointer to the global instance of the Starlight Engine Editor.

### E - Enumerators
`E` is used for any **enumerators**. Makes the type easily identifable when reading through the code base.
#### Examples:
* `EInputKeyType`: Represents the type of input.
* `EInputAxisOrientation`: Represents horizontal or vertical axis for input.

### I - Interfaces
`I` is used for **interfaces**. Makes the type easily identifable when looking at class definitions.
#### Examples:
* `IInputHandler`: Can take input.

### X - Extensions
`X` is used for **extensions**, which are classes intended not to be the base class, but to provide repeated functionality with base implementations.
#### Examples:
* `XSerializable`: Provides serialization functions

---

## Conclusion
Of course it's entirely up to you (and/or your team) whether or not you adhere to these naming conventions but I would highly recommend it.
