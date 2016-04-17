#ifndef SCM_IA_CALCAVOIDANCEDESTINY_H
#define SCM_IA_CALCAVOIDANCEDESTINY_H

#include "tasknode.h"

class CalculateAvoidanceDestiny : public ATaskNode
{
public:
	CalculateAvoidanceDestiny(Entity * owner, TreeContext * context) :ATaskNode(owner, context) {};
	virtual ~CalculateAvoidanceDestiny() {};
	virtual void Init();
	virtual TResult Run();
private:
	double linearSpeed;
};
#endif // !SCM_IA_CALCAVOIDANCEDESTINY_H