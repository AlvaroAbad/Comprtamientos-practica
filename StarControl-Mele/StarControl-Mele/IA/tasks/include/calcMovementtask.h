#ifndef SCM_IA_CALCMOVEMENTTASK_H
#define SCM_IA_CALCMOVEMENTTASK_H

#include "tasknode.h"

class CalculateMovementTask : public ATaskNode
{
public:
	CalculateMovementTask(Entity * owner, TreeContext * context) :ATaskNode(owner, context) {};
	virtual ~CalculateMovementTask() {};
	virtual void Init();
	virtual TResult Run();
private:
	double linearSpeed;
};
#endif // !SCM_IA_CALCMOVEMENTTASK_H
