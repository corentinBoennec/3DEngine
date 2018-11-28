#include "Tree\BSPNode.hpp"

BSPNode::BSPNode(Plan p, BSPNode * f, BSPNode * b)
{
	this->plan = p;
	this->front = f;
	this->back = b;
}
Plan BSPNode::getPlan()
{
	return plan;
}
BSPNode * BSPNode::getFrontNode()
{
	return front;
}
BSPNode * BSPNode::getBackNodes()
{
	return back;
}