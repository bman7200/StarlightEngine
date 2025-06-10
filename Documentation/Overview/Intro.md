# Starlight Engine
Developed by Bradman Harvey (with help)

## Introduction
Starlight Engine is a 2D Engine created with the intention of learning more C++ programming and understanding game engine logic better. This engine is in 2D because the options for 2D out there today aren't as flexible as I'd hope.

While these engines are infinitely valuable, here are some personal pitfalls that turned me away:
* **Unity**'s 2D is very good due to it's support for rigging and hierarchical objects/transforms but has some rendering quirks that turn me away from it (like tilesets with seams).
* **Unreal Engine** is a very powerful engine but it's 2D support is almost next to nothing, besides their amazing UMG designer for UI.
* **Godot** seems promising but their GDScript is too far removed from what I'm used to and I'm not sure it's worth learning the engine.
* **GameMaker Studio** renders exactly how I want to see my 2D pixel art games, but really doesn't have a lot of the editor affordances of modern engines like Unity and Unreal Engine (like prefabs / blueprints).
* **Others** like Scratch and GDevelop but they're more learning tools than fully-fledged engines.

So having used all these engines, there's definitely lots of value in each one, but I wanted to take a chance at developing my own.

## Core Concepts
There are several core elements that make up Starlight Engine.
* **SObject**: These are the base for all objects in the engine. They use an 'Outer' system to control lifetimes.
* **Lattice**: Lattice is the name of the UI framework. All UI stems from SWidget objects.
