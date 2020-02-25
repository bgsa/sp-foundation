#ifndef I_EQUATABLE_HEADER
#define I_EQUATABLE_HEADER

template <typename T>
class IEquatable {
public:

	virtual bool equals(T* other) 
	{
		return this == other;
	}

};

#endif // !I_EQUATABLE_HEADER