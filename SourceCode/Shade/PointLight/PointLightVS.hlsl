// ���_�V�F�[�_�[�̓���
struct VS_INPUT
{
	float4 Position        : POSITION;     // ���W( ���[�J����� )
	float3 Normal          : NORMAL0;      // �@��( ���[�J����� )
	float4 Diffuse         : COLOR0;       // �f�B�t���[�Y�J���[
	float4 Specular        : COLOR1;       // �X�y�L�����J���[
	float4 TexCoords0      : TEXCOORD0;    // �e�N�X�`�����W
};

// ���_�V�F�[�_�[�̏o��
struct VS_OUTPUT
{
	float4 Position        : POSITION;     // ���W( �v���W�F�N�V������� )
	float2 TexCoords0      : TEXCOORD0;    // �e�N�X�`�����W
	float3 VPosition       : TEXCOORD1;    // ���W( �r���[��� )
	float3 VNormal         : TEXCOORD2;    // �@��( �r���[��� )
};




// C++ ���Őݒ肷��萔�̒�`
float4              cfAmbient_Emissive        : register(c1);		// �}�e���A���G�~�b�V�u�J���[ + �}�e���A���A���r�G���g�J���[ * �O���[�o���A���r�G���g�J���[
float4              cfProjectionMatrix[4]   : register(c2);		// �r���[�@�@���@�ˉe�s��
float4              cfViewMatrix[3]         : register(c6);		// ���[���h�@���@�r���[�s��
float4              cfTextureMatrix[3][2] : register(c88);		// �e�N�X�`�����W����p�s��
float4              cfLocalWorldMatrix[3]   : register(c94);		// ���[�J���@���@���[���h�s��


// main�֐�
VS_OUTPUT main(VS_INPUT VSInput)
{
	VS_OUTPUT VSOutput;
	float4 lWorldPosition;
	float4 lViewPosition;
	float3 lWorldNrm;
	float3 lViewNrm;


	// ���_���W�ϊ� ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( �J�n )

	// ���[�J�����W�����[���h���W�ɕϊ�
	lWorldPosition.x = dot(VSInput.Position, cfLocalWorldMatrix[0]);
	lWorldPosition.y = dot(VSInput.Position, cfLocalWorldMatrix[1]);
	lWorldPosition.z = dot(VSInput.Position, cfLocalWorldMatrix[2]);
	lWorldPosition.w = 1.0f;

	// ���[���h���W���r���[���W�ɕϊ�
	lViewPosition.x = dot(lWorldPosition, cfViewMatrix[0]);
	lViewPosition.y = dot(lWorldPosition, cfViewMatrix[1]);
	lViewPosition.z = dot(lWorldPosition, cfViewMatrix[2]);
	lViewPosition.w = 1.0f;

	// �r���[���W���ˉe���W�ɕϊ�
	VSOutput.Position.x = dot(lViewPosition, cfProjectionMatrix[0]);
	VSOutput.Position.y = dot(lViewPosition, cfProjectionMatrix[1]);
	VSOutput.Position.z = dot(lViewPosition, cfProjectionMatrix[2]);
	VSOutput.Position.w = dot(lViewPosition, cfProjectionMatrix[3]);

	// ���_���W�ϊ� ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( �I�� )



	// �@�����r���[��Ԃ̊p�x�ɕϊ� =========================================( �J�n )

	// ���[�J���x�N�g�������[���h�x�N�g���ɕϊ�
	lWorldNrm.x = dot(VSInput.Normal, cfLocalWorldMatrix[0].xyz);
	lWorldNrm.y = dot(VSInput.Normal, cfLocalWorldMatrix[1].xyz);
	lWorldNrm.z = dot(VSInput.Normal, cfLocalWorldMatrix[2].xyz);

	// ���[���h�x�N�g�����r���[�x�N�g���ɕϊ�
	lViewNrm.x = dot(lWorldNrm, cfViewMatrix[0].xyz);
	lViewNrm.y = dot(lWorldNrm, cfViewMatrix[1].xyz);
	lViewNrm.z = dot(lWorldNrm, cfViewMatrix[2].xyz);

	// �@�����r���[��Ԃ̊p�x�ɕϊ� =========================================( �I�� )



	// �o�̓p�����[�^�Z�b�g ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( �J�n )

	// ���_���W��ۑ�
	VSOutput.VPosition = lViewPosition.xyz;

	// �@����ۑ�
	VSOutput.VNormal = lViewNrm;

	// �e�N�X�`�����W�ϊ��s��ɂ��ϊ����s�������ʂ̃e�N�X�`�����W���Z�b�g
	VSOutput.TexCoords0.x = dot(VSInput.TexCoords0, cfTextureMatrix[0][0]);
	VSOutput.TexCoords0.y = dot(VSInput.TexCoords0, cfTextureMatrix[0][1]);

	// �o�̓p�����[�^�Z�b�g ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( �I�� )


	// �o�̓p�����[�^��Ԃ�
	return VSOutput;
}
