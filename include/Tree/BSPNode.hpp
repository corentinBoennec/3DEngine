#include "Plan.hpp"


class BSPNode {
private:
	Plan plan;
	BSPNode * front;
	BSPNode * back;

public:
	BSPNode(Plan p, BSPNode * f, BSPNode * b);
	Plan getPlan();
	BSPNode * getFrontNode();
	BSPNode * getBackNodes();

};