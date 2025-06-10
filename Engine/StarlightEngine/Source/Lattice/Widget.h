// Copyright © 2025 Bman, Inc. All rights reserved.

#pragma once

// Starlight Engine
#include "Object/Object.h"

// Forward Declarations
class SUserController;

class SWidget : public SObject
{
public:
	TWeakObjectPtr<SUserController> GetOwningUserController() { return OwningUserController; }

protected:
	// Only to be called by widgets that add the child.
	void SetParentWidget(TWeakObjectPtr<SWidget> InParentWidget);

private:
	TWeakObjectPtr<SUserController> OwningUserController = TWeakObjectPtr<SUserController>();
	TWeakObjectPtr<SWidget> ParentWidget = TWeakObjectPtr<SWidget>();
};
