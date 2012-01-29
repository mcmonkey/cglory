#include "StdAfx.h"
#include "CellPathNode.h"


CellPathNode::CellPathNode(void)
{
	cell		= NULL;
	previousCell= NULL;
	costTo		= ~0;	// (max value of an integer)
}


CellPathNode::~CellPathNode(void)
{
}

bool CellPathNode::operator==(CellPathNode const other) const
{
	return other.cell == this->cell;
}

bool CellPathNode::operator==(Cell * const other) const
{
	return other == this->cell;
}

bool operator ==(shared_ptr<CellPathNode> const me, Cell* other)
{
	return *me == other;
}