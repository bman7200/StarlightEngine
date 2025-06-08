// Copyright © 2025 Bman, Inc. All rights reserved.

#pragma once

// Libraries
#include <vector>

// Starlight Engine
#include "ObjectPtr.h"
#include "Framework/String.h"

// The base class for all objects in Starlight Engine.
// Relies on an "Outer" system, where all children of an outer are destroyed in a chain upon destruction.
class SObject : public XSharedClass<SObject>
{
public:
	SObject(SObjectWeakPtr InOuter, const FString& InName = "");

protected:
	virtual ~SObject();

public:
	static bool IsValid(SObject* Object);

	const FString& GetName() const { return Name; }

	SObjectWeakPtr GetOuter() const { return Outer; }
	SObjectPtr GetOuterShared() const { return Outer.lock(); }

	/// @returns whether it was successfully marked newly for destruction.
	bool MarkForDestruction();

	virtual void HandleDestroy();

private:
	void AddInner(const SObjectPtr& NewInner);
	void RemoveInner(const SObjectPtr& OldInner);

	FString Name;

	SObjectWeakPtr Outer;
	std::vector<SObjectPtr> Inners;
};
