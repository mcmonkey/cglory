#pragma once
#include "Cell.h"
#include <memory>

class Cell;
// Used for paths between cells.
class CellPathNode
{
//------------------------ Members -------------------------------------
public:
	unsigned int				costTo;			// The cost to get to the currentPathNode.
	shared_ptr<CellPathNode>	previousCell;	// The last node in the path.
	Cell*						cell;			// Cell contained within this.

public:
	CellPathNode(void);
	~CellPathNode(void);
	bool operator ==(CellPathNode const other) const;
	bool operator ==(Cell * const other) const;
};

bool operator ==(shared_ptr<CellPathNode> const, Cell* other);