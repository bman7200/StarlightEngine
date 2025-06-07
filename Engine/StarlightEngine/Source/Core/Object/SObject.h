// Copyright © 2025 Bman, Inc. All rights reserved.

#pragma once

// Libraries
#include <memory>
#include <vector>
#include <string>

// Starlight Engine
#include "SObjectPtr.h"

// The base class for all objects in Starlight Engine.
// Relies on an "Outer" system, where all children of an outer are destroyed in a chain upon destruction.
class SObject : public std::enable_shared_from_this<SObject>
{
public:
	SObject(SObjectWeakPtr InOuter, const std::string& InName = "");

protected:
	virtual ~SObject();

public:
	static bool IsValid(SObject* Object);

	const std::string& GetName() const { return Name; }

	SObjectWeakPtr GetOuter() const { return Outer; }
	SObjectPtr GetOuterShared() const { return Outer.lock(); }

	/// @returns whether it was successfully marked newly for destruction.
	bool MarkForDestruction();

	virtual void HandleDestroy();

private:
	void AddInner(const SObjectPtr& NewInner);
	void RemoveInner(const SObjectPtr& OldInner);

	std::string Name;

	SObjectWeakPtr Outer;
	std::vector<SObjectPtr> Inners;
};
