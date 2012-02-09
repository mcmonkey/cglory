#pragma once


class IUnknown
{

public:
	template<class T>
	bool findComponent(T** outComponent) 
	{
		return queryInterface(T::interfaceId, outComponent);
	}
	virtual bool queryInterface(int id, void** outcomponent);
};


template<int ID>
class IUnknownTemplate :
	public IUnknown
{
public:
	static int const intefraceId = ID;
};
