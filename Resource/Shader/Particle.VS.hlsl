#include"Particle.hlsli"

StructuredBuffer<ParticleForGPU> gParticle : register(t0);
ConstantBuffer<ViewProjectionMatrix> gViewProjectionMatrix : register(b1);

VertexShaderOutput main(VertexShaderInput input, uint32_t instanceId : SV_InstanceID)
{
    VertexShaderOutput output;
    float32_t4x4 WorldViewProjection = mul(gViewProjectionMatrix.view, gViewProjectionMatrix.projection);
    
    output.position = mul(input.position, mul(gParticle[instanceId].matWorld, WorldViewProjection));
    output.texcoord = input.texcoord;
	
    output.color = gParticle[instanceId].color;
    
    return output;
}