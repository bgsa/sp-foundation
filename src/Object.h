#ifndef OBJECT_HEADER
#define OBJECT_HEADER

#include "SpectrumFoundation.h"
//#include "IEquatable.h"

class Object //: public IEquatable<Object>
{
public:

	virtual sp_char* toString() = 0;

};

#endif // !OBJECT_HEADER