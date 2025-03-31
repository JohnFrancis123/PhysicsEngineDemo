#include "AssetController.h"
#include "FileController.h"

StackAllocator* AssetController::Stack = nullptr;

AssetController::AssetController()
{
}

void AssetController::Initialize(int _stackSize) {
	Stack = new StackAllocator(); //free this memory in the destructor
	AssetController::Stack->AllocateStack(_stackSize);
	Asset::Pool = new ObjectPool<Asset>();
}

AssetController::~AssetController() {
	Clear();
}

void AssetController::Clear() {
	//Remove all assets from the object pool
	for (auto const& x : m_assets) {
		Asset::Pool->ReleaseResource(x.second); //x.second means the value, not the key of the dictionary.
	}
	if (Asset::Pool != nullptr) {
		delete Asset::Pool;
		Asset::Pool = nullptr;
	}
	Stack->ClearMemory();
	m_assets.clear();


	//delete Asset::Pool;
	//Stack->ClearMemory();
	//m_assets.clear();
	//delete Stack; //Here we delete the stack inside of AssetController to clear a potential memory leak.
}

Asset* AssetController::GetAsset(string _guid) {
	//If an asset has already been loaded, return the loaded asset
	if (m_assets.count(_guid) != 0) {
		return m_assets[_guid];
	}

	//Otherwise, load the asset and return it
	Asset* asset = Asset::Pool->GetResource(); //_guid is the correct string regardless of file type.
	asset->SetGUID(_guid);
	//the problem is regarding file type.
	asset->SetDataSize(FileController::Instance().GetFileSize(_guid)); //this is the error
	asset->SetData(Stack->GetMemory(asset->GetDataSize()));
	FileController::Instance().ReadFile(_guid, asset->GetData(), asset->GetDataSize());

	//Add a new asset to the map
	m_assets[_guid] = asset;

	return asset;
}
