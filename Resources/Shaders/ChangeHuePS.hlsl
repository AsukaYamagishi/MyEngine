#include "PostEffectTest.hlsli"

Texture2D<float4> tex : register(t0); //0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0); //0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[

float3 HueChange(float max, float middle, float min)
{
    //�ω���
    const float step = 100;
    float oldnum = middle;
    float substep = 0;
    
    //1=middle->max, 2=max->min, 3=min->middle
    int loopCount = 1;
    
    //middle��max��
    while(loopCount == 1)
    {
        //���Ԓl���ő�l�𒴂���܂ŕω��ʂ𑫂�
        oldnum = middle;
        middle = middle + step;
        
        if (max < middle)
        {
        //�������ꍇ�ő�l�Ŏ~�߁A�����������ő�l�������
            substep = middle - max;
            middle = max;
            //substep = step - max;
            max = max + substep;
            loopCount += 1;
        }
    }
    
    while(loopCount==2)
    {
        //�ő�l���������̂��ŏ��l�𒴂���܂ŕω��ʂ�����
        oldnum = max;
        max = max - step;
        
        if (max > min)
        {
        //�������ꍇ�ŏ��l�Ŏ~�߁A���Ԃꂽ�����ŏ��l�ɑ���
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
    
    //�ő�l�ƍŏ��l�����߂�
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