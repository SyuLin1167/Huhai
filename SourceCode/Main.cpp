#include<DxLib.h>
#include"Scene/SceneManager/SceneManager.h"

int WINAPI WinMain(_In_ HINSTANCE,_In_opt_ HINSTANCE,_In_ LPSTR,_In_ int)
{
    //ゲームシーン管理
    SceneManager* sceneManager = new SceneManager;
    sceneManager->Init();
    sceneManager->GameLoop();
    delete sceneManager;

    //ソフトの終了
    return 0;
}