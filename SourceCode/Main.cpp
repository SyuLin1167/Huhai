#include<DxLib.h>
#include<memory>
#include"Scene/SceneManager/SceneManager.h"

int WINAPI WinMain(_In_ HINSTANCE,_In_opt_ HINSTANCE,_In_ LPSTR,_In_ int)
{
    //�Q�[���V�[���Ǘ�
    std::unique_ptr<SceneManager> sceneManager(new SceneManager);
    sceneManager->Init();
    sceneManager->GameLoop();

    //�\�t�g�̏I��
    return 0;
}