/////////////////////////////////////////////////////////////////////////////
//
//	File: VoidRef.h
//
//	$Header: $
//
//
//	This defines the key-value pair structure used by all of the balanced
//	tree algorithms tested.
//
/////////////////////////////////////////////////////////////////////////////


#pragma once

#include "TwoThreeCommon.h"

struct VoidRef_t
{
	U32   Key;
	void* pContext;
};

