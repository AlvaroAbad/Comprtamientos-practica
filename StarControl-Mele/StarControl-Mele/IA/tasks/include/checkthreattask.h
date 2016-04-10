#ifndef SCM_IA_CHECKTHREATTASK_H
#define SCM_IA_CHECKTHREATTASK_H

#include "tasknode.h"

class CheckTHreatTask :public ATaskNode
{
public:
	CheckTHreatTask(Entity * owner, TreeContext * context) :ATaskNode(owner,context) {}
	virtual ~CheckTHreatTask() {};
	virtual void Init();
	virtual TResult Run();
private:

};

#endif // !SCM_IA_CHECKTHREATTASK_H

