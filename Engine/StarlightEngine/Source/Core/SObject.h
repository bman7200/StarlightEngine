// Copyright © 2025 Bman, Inc. All rights reserved.

#pragma once

class SObject
{
public:
	SObject(SObject* InOuter);
	~SObject();

private:
	SObject* Outer;
};
