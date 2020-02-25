#pragma once

#include "apollo.h"
//#include "IEquatable.h"

class Object //: public IEquatable<Object>
{
public:

	virtual sp_char* toString() = 0;

};

