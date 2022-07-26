#include "PostEffectTest.hlsli"

Texture2D<float4> tex : register(t0); //0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0); //0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[

float4 main(VSOutput input) : SV_TARGET
{
    float tiling = 5.0f;
    float4 texcolor = tex.Sample(smp, input.uv * float2(tiling, tiling));
    
    return float4(texcolor.rgb, 1);
}