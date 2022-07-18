#include "PostEffectTest.hlsli"

Texture2D<float4> tex : register(t0); //0番スロットに設定されたテクスチャ
SamplerState smp : register(s0); //0番スロットに設定されたサンプラー

float rand(float2 seed)
{
    return frac(sin(dot(seed.xy, float2(12.9898, 78.233))) * 43758.5453123);
}

float4 main(VSOutput input) : SV_TARGET
{
    float4 texcolor = tex.Sample(smp, input.uv);
    float3 color = { 0, 0, 0 };
    
    float s = sin(input.uv.y * 1000.0f);
    float c = cos(input.uv.x * 1000.0f);
    
    //0に近いほど暗くなる
    //カラーノイズは寄せたい色に数字を足す
    //c=縦, s=横
    color += float3(s, s, s) * 0.7f;
    
    //数字が大きいほどノイズがかかる(砂嵐みたいなやつ)
    float r = rand(input.uv * time);
    color += float3(r, r, r) * 0.5f;
    
    //数字が速いほどちかちかする
    float flash = sin(30.0f * time);
    color += float3(flash, flash, flash) * 0.02f;
    
    return float4(texcolor.rgb * color.rgb, 1);
}