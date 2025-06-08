// Copyright © 2025 Bman, Inc. All rights reserved.

// Header
#include "Object.h"

SObject::SObject(SObjectWeakPtr InOuter, const FString& InName)
	: Name(InName)
	, Outer(InOuter)
{
	if (Name.IsEmpty())
	{
		Name = typeid(InOuter).name();
	}

	if (SObjectPtr SharedOuter = Outer.lock())
	{
		SharedOuter->AddInner(shared_from_this());
	}
}

SObject::~SObject()
{
	HandleDestroy();
	// When an SObject is destroyed, its shared_ptr to its Inners will be released.
	// This will automatically decrement the reference count of the inner objects.
	// If the reference count drops to zero, the inner objects will also be destroyed,
	// triggering a recursive cleanup.
}

bool SObject::IsValid(SObject* Object)
{
	if (Object == nullptr)
	{
		return false;
	}

	if (Object->Outer.expired())
	{
		return false;
	}

	return true;
}

bool SObject::MarkForDestruction()
{
	if (Outer.expired())
	{
		return false;
	}

	GetOuterShared()->RemoveInner(shared_from_this());
	return true;
}

void SObject::HandleDestroy()
{
	//
}

void SObject::AddInner(const SObjectPtr& NewInner)
{
	if (NewInner && std::find(Inners.begin(), Inners.end(), NewInner) == Inners.end())
	{
		Inners.push_back(NewInner);
	}
}

void SObject::RemoveInner(const SObjectPtr& OldInner)
{
	if (OldInner)
	{
		Inners.erase(std::remove_if(
				Inners.begin(),
				Inners.end(),
				[&](const SObjectPtr& PredicateObject)
				{
					return PredicateObject == OldInner;
				}),
			Inners.end());
	}
}
