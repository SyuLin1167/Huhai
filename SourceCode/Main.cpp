#include<DxLib.h>
#include"Scene/SceneManager/SceneManager.h"

int WINAPI WinMain(_In_ HINSTANCE,_In_opt_ HINSTANCE,_In_ LPSTR,_In_ int)
{
    //�Q�[���V�[���Ǘ�
    SceneManager* sceneManager = new SceneManager;
    sceneManager->Init();
    sceneManager->GameLoop();
    delete sceneManager;

    //�\�t�g�̏I��
    return 0;
}