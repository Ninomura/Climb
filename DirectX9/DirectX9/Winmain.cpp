
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
	//���b�Z�[�W�����̂��߂̊֐�
	//DispatchMessage�ɂ���ČĂяo�����

	//�E�B���h�E�N���X�̓o�^����
	//�e�E�B���h�E�ɐݒ肳���

	//�A�v���P�[�V���������b�Z�[�W��
	//�擾������Ăяo�����

	//���b�Z�[�W�̗�

	//WM_DESTROY �E�B���h�E���j�����ꂽ
	//			 �~�{�^���������ꂽ���Ȃ�
	//WM_MOVE    �E�B���h�E���ړ�
	//WM_SIZE    �E�B���h�E�T�C�Y�̕ύX
	//��

	//���ʂȏ�����K�v�Ƃ���ꍇ
	//�܂��͎����œƎ��̏������`�������ꍇ
	//�����Ń��b�Z�[�W�̎�ނɉ�����
	//�������s��

	//��肠���� WM_DESTROY����������
	//�I�������̂ݒ�`

	switch (msg)
	{
	case WM_DESTROY:

		PostQuitMessage(0);

		//���b�Z�[�W�L���[��
		//�V����WM_QUIT���b�Z�[�W�𑗂�

		//�����ꃁ�b�Z�[�W�L���[����
		//���o����
		//���C�����[�v���I������
		//(���C�����[�v�̏I��������
		//���̂悤�ɍ��)
		break;
	}

	//�Ǝ��̏������s������
	//�f�t�H���g�̃E�B���h�E�v���V�[�W�������s

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

	//CS_HREDRAW ���T�C�Y���ς�����Ƃ��E�B���h�E�S�̂̍ĕ`��
	//   VREDRAW �c�T�C�Y���ς�����Ƃ��E�B���h�E�S�̂̍ĕ`��
	//   DBLCLKS �_�u���N���b�N�������������Ƃ��E�B���h�E�ɒʒm

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

	//Player�摜
	Sprite spriteImgPlayer;
	spriteImgPlayer.SetSize(player.sizeX, player.sizeY);

	Texture imgPlayer;
	imgPlayer.Load(_T("Texture/Player.png"));
	imgPlayer.SetDivide(3, 1);

	//���������Z�����ɐݒ�
	Game_Mode Mode = GameStartProcessing;

	MSG msg = {};

	//���C���v���O����-------------------------------------------------
	//quit���b�Z�[�W���o�Ă���܂Ń��[�v���J��Ԃ�
	//quit���b�Z�[�W�͏�L�̃E�B���h�E�v���V�[�W�����瑗�M
	//���M�̏����Ȃǂ̓E�B���h�E�v���V�[�W�����m�F
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

				//�v���C���[����i���������j�Ɉړ�
				Mode = PlayerProcessing;
				break;

			//�v���C���[����
			case Game_Mode::PlayerProcessing:

				//�ړ�����
				player.PlayerMove(pDi);
				//�d�͏���
				player.FallingProcess();
				break;

			//�Q�[���I��
			case Game_Mode::GameEndProcessing:

				if (pDi->MouseButton(0))
				{
					Mode = GameStartProcessing;
				}
				break;

			}

			//�`�揈��
			//�o�b�N�o�b�t�@�̃N���A
			if (SUCCEEDED(d3d.BeginScene()))
			{
				d3d.ClearScreen();

				spriteImgPlayer.SetPos(player.getX(), player.getY());
				spriteImgPlayer.Draw(imgPlayer);

				//�`��I���̍��}
				d3d.EndScene();
				//�o�b�N�o�b�t�@���t�����g�֔��f
				d3d.Present();
			}
		}
	}

	return 0;
};
