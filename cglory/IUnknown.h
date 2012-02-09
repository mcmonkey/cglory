#pragma once


class IUnkown
{

public:
	template<class T>
	bool findComponent(T** outComponent) 
	{
		return findComponent(T::com_id, outComponent);
	}
	virtual bool findComponent(int id, void** outcomponent);
};


template<int ID>
class IUnkownTemplate :
	public IComponent
{
public:
	static int const com_id = ID;

};
