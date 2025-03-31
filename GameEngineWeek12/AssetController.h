#ifndef ASSET_CONTROLLER_H
#define ASSET_CONTROLLER_H

#include "StandardIncludes.h"
#include "StackAllocator.h"
#include "Asset.h"

class AssetController : public Singleton<AssetController> //This is derived from Singleton, meaning it can only be instantiated once.
{
public:
	//Constructors/Destructors
	AssetController();
	virtual ~AssetController();

	//Methods
	void Initialize(int _stackSize);
	void Clear();
	Asset* GetAsset(string _guid);

	//Members
	static StackAllocator* Stack;

private:
	//Members
	map<string, Asset*> m_assets; //This is a dictionary. The first value is always the key.
};

#endif //ASSET_CONTROLLER_H