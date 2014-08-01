#ifndef HANDLERTEMPLATE_H
#define HANDLERTEMPLATE_H

#include <QtCore>
#include "Game/Environment.h"

class HandlerTemplate
{
public:
	HandlerTemplate();

//	virtual void load(dataStream or sth);
//	virtual void save(dataStream or sth);
	virtual void init(/*some args*/){}
	virtual QList<int> actions(Environment env);
};

#endif // HANDLERTEMPLATE_H
