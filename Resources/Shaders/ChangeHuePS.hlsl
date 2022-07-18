#include "PostEffectTest.hlsli"

Texture2D<float4> tex : register(t0); //0番スロットに設定されたテクスチャ
SamplerState smp : register(s0); //0番スロットに設定されたサンプラー

float3 HueChange(float max, float middle, float min)
{
    //変化量
    const float step = 100;
    float oldnum = middle;
    float substep = 0;
    
    //1=middle->max, 2=max->min, 3=min->middle
    int loopCount = 1;
    
    //middleをmaxに
    while(loopCount == 1)
    {
        //中間値が最大値を超えるまで変化量を足す
        oldnum = middle;
        middle = middle + step;
        
        if (max < middle)
        {
        //超えた場合最大値で止め、超えた分を最大値から引く
            substep = middle - max;
            middle = max;
            //substep = step - max;
            max = max + substep;
            loopCount += 1;
        }
    }
    
    while(loopCount==2)
    {
        //最大値だったものが最小値を超えるまで変化量を引く
        oldnum = max;
        max = max - step;
        
        if (max > min)
        {
        //超えた場合最小値で止め、あぶれた分を最小値に足す
            substep = step - (oldnum - min);
            max = min;
            //substep = step - min;
            min = min + substep;
            loopCount += 1;
        }
    }
    
    
    
}

float4 main(VSOutput input) : SV_TARGET
{
    float4 texcolor = tex.Sample(smp, input.uv);
    float r = texcolor.r;
    float g = texcolor.g;
    float b = texcolor.b;
    
    //最大値と最小値を求める
    if (r >= g)
    {
        if(b >= r)
        {
            HueChange(b, r, g);
            break;
        }
        else
        {
            if(g >= b)
            {
                HueChange(r, g, b);
                break;
            }
            else
            {
                HueChange(r, b, g);
                break;
            }
        }
    }
    else if(g > r)
    {
        if(r >= b)
        {
            HueChange(g, r, b);
            break;
        }
        else
        {
            if(g > b)
            {
                HueChange(g, b, r);
                break;
            }
            else
            {
                HueChange(b, g, r);
                break;
            }
        }
    }
    
    return texcolor;
}