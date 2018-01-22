
#include <Windows.h>
#pragma comment(lib,"winmm.lib")

#include <tchar.h>

#include"Direct3D.h"

#include "Sprite.h"
#include "Texture.h"
#include "DirectInput.h"

#include"ExternGV.h"
#include"Player.h"

#include <random>

//�E�B���h�E�v���V�[�W��
LRESULT CALLBACK WndPrc
(
	HWND hWnd,	//�E�B���h�E�̃n���h��
	UINT msg,	//���b�Z�[�W
	WPARAM wParam,
	LPARAM lParam
)
{
	switch (msg)
	{
	case WM_DESTROY:

		PostQuitMessage(0);

		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

//�E�B���h�E�ݒ�̖��O
static const TCHAR* WC_BASIC = _T("Basic");

//��肽���E�B���h�E�̐ݒ��
//�o�^����֐�
HRESULT RegistClassEx(HINSTANCE hInstance)
{
	//�E�B���h�E�̐ݒ��ۑ�����\����
	WNDCLASSEX wcex;

	//wcex�̐擪�A�h���X����
	//WNDCLASSEX�̒������̃�������
	//�S��0�Ŗ��߂�
	memset(&wcex, 0, sizeof(WNDCLASSEX));
	//�܂��wcex���g�p���Ă��郁�����̈��
	//�S��0�ŏ��������鏈��

	//�E�B���h�E�̐ݒ�

	//�\���̂̃T�C�Y
	wcex.cbSize = sizeof(WNDCLASSEX);

	//�E�B���h�E�̐ݒ���ɒǉ�����ߑ���t���Ȃ��̂�
	//0�ŌŒ�
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;

	//Window�̃X�^�C��
	//���ꂼ�ꂪ�r�b�g�P�ʂ̃t���O�ł��邽��
	//�I�A���Z�ō����������̂��X�^�C���̍ŏI�I�Ȑݒ�
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;

	//WinMain�̃C���X�^���X�n���h��
	wcex.hInstance = hInstance;

	//�E�B���h�E�v���V�[�W���̃A�h���X
	//�֐��|�C���^�̐ݒ�
	//�E�B���h�E�v���V�[�W����OS���Ăяo����悤�ɂ���
	wcex.lpfnWndProc = (WNDPROC)WndPrc;

	//�w�i�F
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

	//���j���[�@�Ȃ�
	wcex.lpszMenuName = NULL;

	//�E�B���h�E�N���X�̖��O�@���̃E�B���h�E�ݒ�̖��O
	wcex.lpszClassName = WC_BASIC;

	//�A�C�R���@�f�t�H���g�̂��g��
	wcex.hIcon = (HICON)LoadImage(NULL,
		MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON,
		0,
		0,
		LR_DEFAULTSIZE | LR_SHARED);
	wcex.hIconSm = NULL;

	//�J�[�\�� �f�t�H���g�̂��̂��g��
	wcex.hCursor = (HCURSOR)LoadImage(NULL,
		MAKEINTRESOURCE(IDC_ARROW),
		IMAGE_CURSOR,
		0,
		0,
		LR_DEFAULTSIZE | LR_SHARED);

	//�ݒ肵���E�B���h�E�N���X��o�^
	//�o�^�����E�B���h�E�ݒ�łȂ���
	//�E�B���h�E����邱�Ƃ��ł��Ȃ�
	return RegisterClassEx(&wcex);
	//HRESULT�^�̎��s���ʂ��߂����
}


//�o�^�����ݒ����ɃE�B���h�E���쐬����
HRESULT MakeWindow
(HINSTANCE hInstance,//WinMain�̎��ʎq
	HWND &refHWnd,	//�E�B���h�E�̎��ʎq
					//�������E�B���h�E�̍쐬���ł�����
					//���̕ϐ��Ɏ��ʎq��������
	int width = WindowWidthSize,	//�N���C�A���g�̈�̕�
	int height = WindowHeightSize)	//�N���C�A���g�̈�̍���
						//�N���C�A���g�̈�̓E�B���h�E�S�̂���
						//�O�g�⃁�j���[�̕��������������ƍ��͎v���Ă�����OK
{
	//�N���C�A���g�̈�̂������������߂�
	RECT rect;
	rect.top = 0;
	rect.left = 0;
	rect.right = width;
	rect.bottom = height;

	//�N���C�A���g�̈��ێ�����̂ɕK�v��
	//�E�B���h�E�̂����������v�Z
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE/*TRUE*/);
	//���������s������rect�̒l���X�V�����

	//WS_OVERLAPPEDWINDOW�̓E�B���h�E�̃X�^�C���̈��

	//�E�B���h�E�̃n���h��
	//�E�B���h�E�̎��ʂɎg�p����
	HWND hWnd;

	hWnd = CreateWindowEx
	(0,						//�E�B���h�E�g���X�^�C��
		WC_BASIC,				//��肽���E�B���h�E�N���X
								//���炩���ߓo�^���ꂽ����
		_T("�N���C��"),			//�E�B���h�E�̃^�C�g��
		WS_OVERLAPPEDWINDOW,	//�E�B���h�E�̃X�^�C��
		CW_USEDEFAULT,			//�ʒux���W �f�t�H���g�̒l
		CW_USEDEFAULT,			//�ʒuy���W �f�t�H���g�̒l
		rect.right - rect.left,	//�E�B���h�E�S�̂̕�
		rect.bottom - rect.top, //�E�B���h�E�S�̂̍���
		NULL,					//�e�E�B���h�E�̃n���h��
		NULL,					//���j���[�̃n���h��
		hInstance,				//WinMain�̃n���h��

		NULL);

	if (hWnd == NULL)
	{
		return S_FALSE;//HRESULT�^�@���s��\�����ʎq�̈��
	}

	//�E�B���h�E���A�N�e�B�u�ɂ��ĕ\��
	//hWnd�ŃE�B���h�E�̎��ʂ����Ă��邱�Ƃɒ���
	ShowWindow(hWnd, SW_SHOWNORMAL);

	//�N���C�A���g�̈�̍X�V
	UpdateWindow(hWnd);

	//�Q�Ɠn���ɂȂ��Ă��������
	//�E�B���h�E�̎��ʃn���h�����R�s�[����
	//����ɂ���č�������E�B���h�E�̎��ʃn���h����
	//�Ăяo�����̃v���O�����œ��邱�Ƃ��ł���
	refHWnd = hWnd;

	//HRESULT�^�@������\�����ʎq�̈��
	return S_OK;
}


//�G���g���[�|�C���g
//�v���O�����̊J�n�֐�

int _stdcall WinMain
(HINSTANCE hInstance,	//�v���O���������ʂ���n���h��
	HINSTANCE hPrevInstance,//�A�v���P�[�V�����̑O�̃C���X�^���X�n���h��
							//win32���Ə��NULL
	LPSTR lpCmdLine,		//�R�}���h���C������
	int nCmdShow)		//�E�B���h�E�̕\�����
{
	//���b�Z�[�W�{�b�N�X
	MessageBox(NULL,		//�E�B���h�E�̃n���h�� 
		TEXT("�e�X�g"),		//�{��
		TEXT("�e�X�g-�^�C�g��"),//�^�C�g��
		MB_OK);				//���b�Z�[�W�{�b�N�X�̃^�C�v
							//MB_OK  ok�̃{�^�����\��

	if (FAILED(RegistClassEx(hInstance)))
	{
		MessageBox(NULL,
			TEXT("�E�B���h�E�N���X�ݒ莸�s"),
			TEXT("�e�X�g-�^�C�g��"),
			MB_OK);
		return 0;
	}

	HWND hWnd = NULL;

	//�������E�B���h�E���쐬������
	//hWnd�ɃE�B���h�E�̎��ʃn���h��������
	if (FAILED(MakeWindow(hInstance, hWnd)))
	{
		MessageBox(NULL,
			TEXT("�E�B���h�E�쐬���s"),
			TEXT("�e�X�g-�^�C�g��"),
			MB_OK);
		return 0;
	}

	//Direct3D���Ǘ�����N���X(�V���O���g��)�ւ̎Q�Ƃ��擾
	Direct3D& d3d = Direct3D::GetInstance();

	//Direct3DDevice�̍쐬�����݂�
	if (d3d.TryCreate(hWnd))
	{
		MessageBox(NULL,
			TEXT("Direct3D Device�쐬����"),
			TEXT("�e�X�g-�^�C�g��"),
			MB_OK);
	}

	d3d.SetRenderState(RENDERSTATE::RENDER_ALPHATEST);

	DirectInput * pDi = DirectInput::GetInstance();
	pDi->Init(hWnd);

	Player player;
	Object object;

	int frame = 0;

	//�w�i�摜
	Sprite spriteImgBg;
	spriteImgBg.SetSize(WindowWidthSize, WindowHeightSize);
	spriteImgBg.SetPos(WindowWidthSize / 2, WindowHeightSize / 2);
	//Player�摜
	Sprite spriteImgPlayer;
	spriteImgPlayer.SetSize(player.getSizeX(), player.getSizeY());
	//�}�b�v�摜
	Sprite spriteImgObject[object.setMaxPosY][object.setMaxPosX];
	//�f�[�^����
	for (int y = 0; y < object.setMaxPosY; y++)
	{
		for (int x = 0; x < object.setMaxPosX; x++)
		{
			spriteImgObject[y][x].SetSize(object.getObjectSize(), object.getObjectSize());
		}
	}

	//�e�N�X�`���ݒ�
	Texture imgBg;
	imgBg.Load(_T("Texture/cl_Bg.png"));
	Texture imgPlayer;
	imgPlayer.Load(_T("Texture/cl_Player.png"));
	imgPlayer.SetDivide(4, 1);
	imgPlayer.SetNum(2, 0);
	Texture imgObject;
	imgObject.Load(_T("Texture/cl_BaseBlock.png"));
	imgObject.SetDivide(2, 1);

	//���������Z�����ɐݒ�
	Game_Mode Mode = GameStartProcessing;

	MSG msg = {};

	//���C���v���O����-------------------------------------------------
	while (msg.message != WM_QUIT)
	{

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			//���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�ɕϊ���
			//��������b�Z�[�W�L���[�Ƀ|�X�g����
			TranslateMessage(&msg);

			//���b�Z�[�W�̊��蓖��
			//�E�B���h�E�v���V�[�W���Ń��b�Z�[�W������
			DispatchMessage(&msg);
		}
		else
		{
			pDi->Update();//�L�[��Ԃ̍X�V

			switch (Mode)
			{
			//�X�^�[�g���
			case Game_Mode::StartScreenProcessing:

				break;

			//��������
			case Game_Mode::GameStartProcessing:

				player.~Player();

				object.MapCreate();
				player.PlayerCreate();

				//�v���C���[����i���������j�Ɉړ�
				Mode = PlayerProcessing;
				break;

			//�v���C���[����
			case Game_Mode::PlayerProcessing:

					//�ړ�����
					player.PlayerMove(pDi,&imgPlayer);
					//�d�͏���
					object.FallingProcessing();
					player.FallingProcessing(&object);

				break;

			//�Q�[���I��
			case Game_Mode::GameEndProcessing:

				if (pDi->MouseButton(0)) { Mode = GameStartProcessing; }

				break;
			}

			//�`�揈��
			//�o�b�N�o�b�t�@�̃N���A
			if (SUCCEEDED(d3d.BeginScene()))
			{
				d3d.ClearScreen();
				//�w�i
				spriteImgBg.Draw(imgBg);
				//�v���C���[
				spriteImgPlayer.SetPos
				(player.getPosX() + player.getSizeX() / 2.0f,
					player.getPosY() + player.getSizeY() / 2.0f);
				spriteImgPlayer.Draw(imgPlayer);

				//�}�b�v
				for (int y = 0; y < object.setMaxPosY; y++)
				{
					for (int x = 0; x < object.setMaxPosX; x++)
					{
						spriteImgObject[y][x].SetPos
						(x*object.getObjectSize() + object.getObjectSize() / 2,
							y*object.getObjectSize() + object.getObjectSize() / 2);

						switch (object.mapData[y + object.setPosY][x])
						{
						case 0:
							break;
						case 1:
							imgObject.SetNum(0, 0);
							spriteImgObject[y][x].Draw(imgObject);
							break;
						case 2:
							imgObject.SetNum(1, 0);
							spriteImgObject[y][x].Draw(imgObject);
							break;
						}
					}
				}

				//�`��I���̍��}
				d3d.EndScene();
				//�o�b�N�o�b�t�@���t�����g�֔��f
				d3d.Present();
			}
		}
	}

	return 0;
};
