
// ortho graphic vertex shader

//	�t���X�N���[���̃R�s�[�Ȃǂ�

vs_2_0

// ���̓��W�X�^
dcl_position0			v0				// ���W�ϊ�������PS�֏o��
dcl_texcoord0			v8				// �e�N�X�`�����W�O

// �萔
//	c0.xy		SceneSharpness ( 0.0f soft _ 0.5f sharp ) / WIDTH

//----------------------------------------------------------------
//----------------------------------------------------------------

// ���W

mov			oPos,		v0							// �ϊ������ɍ��W�o��

// �e�N�X�`��

add			oT0,		v8,			c0

