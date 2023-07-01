#include<DxLib.h>
#include"Scene/SceneManager/SceneManager.h"

int WINAPI WinMain(_In_ HINSTANCE,_In_opt_ HINSTANCE,_In_ LPSTR,_In_ int)
{
    //ゲームシーン管理
    SceneManager* sceneMgr = new SceneManager;
    sceneMgr->Init();
    sceneMgr->GameLoop();
    delete sceneMgr;

    //ソフトの終了
    return 0;
}