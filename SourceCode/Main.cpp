#include<DxLib.h>
#include"Scene/SceneManager/SceneManager.h"

int WINAPI WinMain(_In_ HINSTANCE,_In_opt_ HINSTANCE,_In_ LPSTR,_In_ int)
{
    //�Q�[���V�[���Ǘ�
    SceneManager* sceneMgr = new SceneManager;
    sceneMgr->Init();
    sceneMgr->GameLoop();
    delete sceneMgr;

    //�\�t�g�̏I��
    return 0;
}