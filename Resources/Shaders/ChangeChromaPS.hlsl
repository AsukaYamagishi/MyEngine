#include "PostEffectTest.hlsli"

Texture2D<float4> tex : register(t0); //0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0); //0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[

float4 main(VSOutput input) : SV_TARGET
{
    float4 texcolor = tex.Sample(smp, input.uv);
    
    float maxcol;
    if (texcolor.r >= texcolor.g)
        maxcol = texcolor.r;
    else
        maxcol = texcolor.g;
    
    if (texcolor.b > maxcol)
        return float4(texcolor.rg * 2.0f, texcolor.b, 1);
    else
    {
        if (texcolor.r >= texcolor.g)
            return float4(texcolor.r, texcolor.gb * 2.0f, 1);
        else
            return float4(texcolor.r * 2.0f, texcolor.g, texcolor.b * 2.0f, 1);
    }
}