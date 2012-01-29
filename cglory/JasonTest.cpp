#include "StdAfx.h"
#include "JasonTest.h"
#include "CellPathNode.h"
#include "Cell.h"
#include "Unit.h"

#include <vector>

int moveOne(Cell* c, Cell* c2)
{
	return 1;
}

void JasonTest::test()
{
	Map m(20, 20, 2);
	Unit u = Unit();
	
	vector<shared_ptr<CellPathNode>> v = m.reachableCells(m.getCell(10, 10), 5, UnitTraversalHelper(&u, &Unit::visibilityTraverse));
	DeveloperConsole::writeLine("Test with 20x20, range 5, move 1");
	DeveloperConsole::writeLine(v.size());
	
}

JasonTest::JasonTest(void)
{
}


JasonTest::~JasonTest(void)
{
}
