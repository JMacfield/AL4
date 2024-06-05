#include "Object3D.hlsli"

static const float32_t2 kIndex3x3[3][3] =
{
    { { -1.0f, -1.0f }, { 0.0f, -1.0f }, { 1.0f, -1.0f } },
    { { -1.0f, 0.0f }, { 0.0f, 0.0f }, { 1.0f, 0.0f } },
    { { -1.0f, 1.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f } },
};

static const float32_t kKernel3x3[3][3] =
{
    { 1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f },
    { 1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f },
    { 1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f },
};

ConstantBuffer<Material> gMaterial : register(b0);
Texture2D<float32_t4> gTexture : register(t0);
SamplerState gSampler : register(s0);
ConstantBuffer<DirectionalLight> gDirectionalLight : register(b1);

PixelShaderOutput main(VertexShaderOutput input) {
	PixelShaderOutput output;
    output.color.rgb = float32_t3(0.0f, 0.0f, 0.0f);
    output.color.a = 1.0f;
	
    uint32_t width, height;
    gTexture.GetDimensions(width, height);
    float32_t2 uvStepSize = float32_t2(rcp(width), rcp(height));
	
	
	//float4 transformedUV = mul(float32_t4(input.texcoord, 0.0f, 1.0f),gMaterial.uvTransform);
	//float32_t4 textureColor = gTexture.Sample(gSampler, transformedUV.xy);

	//if (gMaterial.enableLighting != 0) {//lightingする場合
	//	float Ndotl = dot(normalize(input.normal), -gDirectionalLight.direction);
	//	float cos = pow(Ndotl * 0.5f + 0.5f, 2.0f);
	//	output.color.rgb = gMaterial.color.rgb * textureColor.rgb * gDirectionalLight.color.rgb * cos * gDirectionalLight.intensity;
	//	output.color.a = gMaterial.color.a * textureColor.a;
	//	if (textureColor.a == 0.0) {
	//		discard;
	//	}
	//	if (textureColor.a <= 0.5) {
	//		discard;
	//	}
	//	if (output.color.a == 0.0) {
	//		discard;
	//	}
	//}
	//else {
	//	output.color = gMaterial.color * textureColor;
	//}
	
    //output.color = gTexture.Sample(gSampler, input.texcoord);
    //float32_t2 correct = input.texcoord * (1.0f - input.texcoord.yx);
    //float vignette = correct.x * correct.y * 16.0f;
    //vignette = saturate(pow(vignette, 0.8f));
    //output.color.rgb *= vignette;
	
    for (int32_t x = 0; x < 3; ++x)
    {
        for (int32_t y = 0; y < 3; ++y)
        {
            float32_t2 texcoord = input.texcoord + kIndex3x3[x][y] * uvStepSize;
            float32_t3 fetchColor = gTexture.Sample(gSampler, texcoord).rgb;
            output.color.rgb += fetchColor * kKernel3x3[x][y];
        }
    }
	
	return output;
}