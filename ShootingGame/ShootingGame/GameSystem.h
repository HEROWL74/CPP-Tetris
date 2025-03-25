#pragma once

//GameSystem�N���X
//�E���̃Q�[���̓y��ƂȂ�N���X

class GameSystem
{
public:
	//���̃Q�[���̏��������s��
	void Initialize();
	//���̃Q�[���̎��Ԃ�i�߂�
	void Execute();

//=========================================
// ���񂱂̃N���X���A�ǂ�����ł��A�N�Z�X�ł���悤��
// �V���O���g���p�^�[���ɂ��Ă����܂��B
// �������ȉ��A�V���O���g���p�^�[���̃R�[�h
//=========================================
private:
	//�B��̃C���X�^���X�p�̃|�C���^
	static inline GameSystem* s_instance;
	//�R���X�g���N�^�́Aprivate�ɂ���
	GameSystem() {}
public:

	//�C���X�^���X�쐬
	static void CreateInstance()
	{
		DeleteInstance();

		s_instance = new GameSystem();
	}
	//�C���X�^���X�폜
	static void DeleteInstance()
	{
		if (s_instance != nullptr)
		{
			delete s_instance;
			s_instance = nullptr;
		}
	}
	//�B��̃C���X�^���X�擾
	static GameSystem& GetInstance()
	{
		
		return *s_instance;
	}
};
//GameSystem�̗B��̃C���X�^���X���ȒP�Ɏ擾���邽�߂̃}�N�����`
#define GAMESYS GameSystem::GetInstance()
