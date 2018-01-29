#pragma once
#include "common.h"
#include <algorithm>
#include "stringhelpers.h"
#include "userinterface/sprite.h"
#include "userinterface/textureloader.h"
#include "novelinfo.h"

enum class ViewModeType
{
	List,
	Grid,
};

class NovelBrowser
{
private:
	SceCtrlData GamePad, GamePadLast;
	void Search(std::string SearchPath);
	std::vector<NovelInfo> NovelList;
	vita2d_pgf * pgf = vita2d_load_default_pgf();	//Font!
	int ItemSelected = 0;
	ViewModeType ViewMode = ViewModeType::List;
	bool drawDebug = false;

	int ScrollY = 0;
	int Scroll = 0;
	int GridPerLine = 5;

	TextureCache textureCache;
	UISprite IconVNDS = UISprite(textureCache.GetOrLoad(ASSET_VNDSFlag));
	UISprite IconVNVita = UISprite(textureCache.GetOrLoad(ASSET_VNVitaFlag));
	UISprite IconNoIcon = UISprite(textureCache.GetOrLoad(ASSET_NoIcon));
public:
	StatusType StatusCode;
	
	NovelBrowser();
	~NovelBrowser();
	
	NovelInfo Run();

	bool Tick(ViewModeType &ViewMode);
	void Draw();
	void DrawList();
	void DrawGrid();
	void DrawPreview();
	void DrawDebugOverlay();
};