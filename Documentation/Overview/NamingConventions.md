# Starlight Engine Naming Conventions

## Introduction
This document outlines that naming conventions that were used when developing the engine and hence recommended to follow to stay consistent.

## Prefixes

### `F` - Framework
Used for framework structs.
#### E.g.:
* `FString`: String struct for char manipulation.
* `FVector2`, `FVector3`: Math structs for storing n-dimensional points.
* `FColor`: Color struct for RGBA.
* `FInputKey`: For identifying a key.

### `G` - Globals
Used for global singleton variables.
#### E.g.:
* `GEngine` - Pointer to the global instance of Starlight Engine.

### `E` - Enumerators
Used for any enumerators. Makes the type easily identifable when reading through the code base.
#### E.g.:
* `EInputAxisOrientation`: Enum representing horizontal or vertical axis for input.

### `I` - Interfaces
Used for interfaces. Makes the type easily identifable when looking at class definitions.
#### E.g.:
* `IInputHandler`

### `X` - Extensions
Used for extensions, which are classes intended not to be the base class, but to provide repeated functionality with base implementations.

## Conclusion
Of course it's entirely up to you (and/or your team) whether or not you adhere to these naming conventions but I would highly recommend it.
