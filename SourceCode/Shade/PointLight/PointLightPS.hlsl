// �s�N�Z���V�F�[�_�[�̓���
struct PS_INPUT
{
	float2 TexCoords0      : TEXCOORD0;    // �e�N�X�`�����W
	float3 VPosition       : TEXCOORD1;    // ���W( �r���[��� )
	float3 VNormal         : TEXCOORD2;    // �@��( �r���[��� )
};

// �s�N�Z���V�F�[�_�[�̏o��
struct PS_OUTPUT
{
	float4 Color0          : COLOR0;
};

// �}�e���A���p�����[�^
struct MATERIAL
{
	float4 Diffuse;      // �f�B�t���[�Y�J���[
	float4 Specular;     // �X�y�L�����J���[
	float4 Power;        // �X�y�L�����̋���
};

// ���C�g�p�����[�^
struct LIGHT
{
	float4 Position;               // ���W( �r���[��� )
	float3 Direction;              // ����( �r���[��� )
	float4 Diffuse;                // �f�B�t���[�Y�J���[
	float4 Specular;               // �X�y�L�����J���[
	float4 Ambient;                // �A���r�G���g�J���[�ƃ}�e���A���̃A���r�G���g�J���[����Z��������
	float4 Range_FallOff_AT0_AT1;  // x:�L������  y:�X�|�b�g���C�g�pFallOff  z:�����ɂ�錸�������p�p�����[�^�O  w:�����ɂ�錸�������p�p�����[�^�P
	float4 AT2_SpotP0_SpotP1;      // x:�����ɂ�錸�������p�p�����[�^�Q  y:�X�|�b�g���C�g�p�p�����[�^�O( cos( Phi / 2.0f ) )  z:�X�|�b�g���C�g�p�p�����[�^�P( 1.0f / ( cos( Theta / 2.0f ) - cos( Phi / 2.0f ) ) )
};


// C++ ���Őݒ肷��e�N�X�`����萔�̒�`
sampler  DiffuseMapTexture             : register(s0);		// �f�B�t���[�Y�}�b�v�e�N�X�`��
float4   cfAmbient_Emissive            : register(c1);		// �G�~�b�V�u�J���[ + �}�e���A���A���r�G���g�J���[ * �O���[�o���A���r�G���g�J���[
MATERIAL cfMaterial : register(c2);		// �}�e���A���p�����[�^
float4   cfFactorColor                 : register(c5);		// �s�����x��
LIGHT    cfLight[6]                  : register(c32);		// ���C�g�p�����[�^


// �|�C���g���C�g�̌v�Z������֐�
inline void CalcPointLight(
	const in    PS_INPUT PSInput,
	const in    int      LightNo,
	const in    float3   Normal,
	const in    float3   V_to_Eye,
	inout float4   TotalDiffuse,
	inout float4   TotalSpecular
)
{
	float  DiffuseAngleGen;
	float3 TempF3;
	float  Temp;
	float3 lLightTemp;
	float  lLightDistancePow2;
	float  lLightGen;
	float3 lLightDir;

	// ���C�g�����x�N�g���̌v�Z
	lLightDir = normalize(PSInput.VPosition.xyz - cfLight[LightNo].Position.xyz);


	// ���������l�v�Z =======================================================( �J�n )

	// ���_�ƃ��C�g�ʒu�Ƃ̋����̓������߂�
	lLightTemp = PSInput.VPosition.xyz - cfLight[LightNo].Position.xyz;
	lLightDistancePow2 = dot(lLightTemp, lLightTemp);

	// �������̌v�Z lLightGen = 1 / ( �����l0 + �����l1 * ���� + �����l2 * ( ���� * ���� ) )
	lLightGen = 1.0f / (cfLight[LightNo].Range_FallOff_AT0_AT1.z + cfLight[LightNo].Range_FallOff_AT0_AT1.w * sqrt(lLightDistancePow2) + cfLight[LightNo].AT2_SpotP0_SpotP1.x * lLightDistancePow2);

	// �L�������O�������猸�������ő�ɂ��鏈��
	lLightGen *= step(lLightDistancePow2, cfLight[LightNo].Range_FallOff_AT0_AT1.x);

	// ���������l�v�Z =======================================================( �I�� )


	// �f�B�t���[�Y�F�v�Z

	// �f�B�t���[�Y�p�x�������v�Z
	DiffuseAngleGen = saturate(dot(Normal, -lLightDir));

	// �f�B�t���[�Y�J���[�~�ϒl += ( ���C�g�̃f�B�t���[�Y�J���[ * �}�e���A���f�B�t���[�Y�J���[ * �f�B�t���[�Y�J���[�p�x������ + ���C�g�̃A���r�G���g�J���[�ƃ}�e���A���̃A���r�G���g�J���[����Z��������  ) * �����E�X�|�b�g���C�g�̊p�x������
	TotalDiffuse += (cfLight[LightNo].Diffuse * cfMaterial.Diffuse * DiffuseAngleGen + cfLight[LightNo].Ambient) * lLightGen;


	// �X�y�L�����J���[�v�Z

	// �n�[�t�x�N�g���̌v�Z
	TempF3 = normalize(V_to_Eye - lLightDir);

	// Temp = pow( max( 0.0f, N * H ), cfMaterial.Power.x )
	Temp = pow(max(0.0f, dot(Normal, TempF3)), cfMaterial.Power.x);

	// �X�y�L�����J���[�~�ϒl += Temp * �����E�X�|�b�g���C�g�̊p�x������ * ���C�g�̃X�y�L�����J���[
	TotalSpecular += Temp * lLightGen.x * cfLight[LightNo].Specular;
}



// main�֐�
PS_OUTPUT main(PS_INPUT PSInput)
{
	PS_OUTPUT PSOutput;
	float4 TextureDiffuseColor;
	float4 SpecularColor;
	float3 Normal;
	float4 TotalDiffuse;
	float4 TotalSpecular;
	float3 V_to_Eye;


	// �@���̏���
	Normal = normalize(PSInput.VNormal);

	// ���_���W���王�_�ւ̃x�N�g���𐳋K��
	V_to_Eye = normalize(-PSInput.VPosition);

	// �f�B�t���[�Y�J���[�ƃX�y�L�����J���[�̒~�ϒl��������
	TotalDiffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	TotalSpecular = float4(0.0f, 0.0f, 0.0f, 0.0f);


	// �|�C���g���C�g�O�`�T�̏��� +++++++++++++++++++++++++++++++++++++++++++++++++++++++( �J�n )

	CalcPointLight(PSInput, 0, Normal, V_to_Eye, TotalDiffuse, TotalSpecular);
	CalcPointLight(PSInput, 1, Normal, V_to_Eye, TotalDiffuse, TotalSpecular);
	CalcPointLight(PSInput, 2, Normal, V_to_Eye, TotalDiffuse, TotalSpecular);
	CalcPointLight(PSInput, 3, Normal, V_to_Eye, TotalDiffuse, TotalSpecular);
	CalcPointLight(PSInput, 4, Normal, V_to_Eye, TotalDiffuse, TotalSpecular);
	CalcPointLight(PSInput, 5, Normal, V_to_Eye, TotalDiffuse, TotalSpecular);

	// �|�C���g���C�g�O�`�T�̏��� +++++++++++++++++++++++++++++++++++++++++++++++++++++++( �I�� )


	// �o�̓J���[�v�Z +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( �J�n )

	// TotalDiffuse = ���C�g�f�B�t���[�Y�J���[�~�ϒl + ( �}�e���A���̃A���r�G���g�J���[�ƃO���[�o���A���r�G���g�J���[����Z�������̂ƃ}�e���A���G�~�b�V�u�J���[�����Z�������� )
	TotalDiffuse += cfAmbient_Emissive;

	// SpecularColor = ���C�g�̃X�y�L�����J���[�~�ϒl * �}�e���A���̃X�y�L�����J���[
	SpecularColor = TotalSpecular * cfMaterial.Specular;

	// �o�̓J���[ = TotalDiffuse * �e�N�X�`���J���[ + SpecularColor
	TextureDiffuseColor = tex2D(DiffuseMapTexture, PSInput.TexCoords0.xy);
	PSOutput.Color0.rgb = TextureDiffuseColor.rgb * TotalDiffuse.rgb + SpecularColor.rgb;

	// �A���t�@�l = �e�N�X�`���A���t�@ * �}�e���A���̃f�B�t���[�Y�A���t�@ * �s�����x
	PSOutput.Color0.a = TextureDiffuseColor.a * cfMaterial.Diffuse.a * cfFactorColor.a;

	// �o�̓J���[�v�Z +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( �I�� )


	// �o�̓p�����[�^��Ԃ�
	return PSOutput;
}