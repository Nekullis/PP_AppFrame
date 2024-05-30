#pragma once
//定数
//円周率
constexpr double PI = 3.14159265;
//イージングクラス
class Easing
{
public:
	Easing();
    //線形補間
    static float Linear(float cnt, float start, float end, float frames);
    //二次関数
    static float InQuad(float cnt, float start, float end, float frames);
    static float OutQuad(float cnt, float start, float end, float frames);
    static float InOutQuad(float cnt, float start, float end, float frames);
    //三次関数
    static float InCubic(float cnt, float start, float end, float frames);
    static float OutCubic(float cnt, float start, float end, float frames);
    static float InOutCubic(float cnt, float start, float end, float frames);
    //四次関数
    static float InQuart(float cnt, float start, float end, float frames);
    static float OutQuart(float cnt, float start, float end, float frames);
    static float InOutQuart(float cnt, float start, float end, float frames);
    //五次関数
    static float InQuint(float cnt, float start, float end, float frames);
    static float OutQuint(float cnt, float start, float end, float frames);
    static float InOutQuint(float cnt, float start, float end, float frames);
    //三角関数「サイン」
    static float InSine(float cnt, float start, float end, float frames);
    static float OutSine(float cnt, float start, float end, float frames);
    static float InOutSine(float cnt, float start, float end, float frames);
    //指数関数
    static float InExpo(float cnt, float start, float end, float frames);
    static float OutExpo(float cnt, float start, float end, float frames);
    static float InOutExpo(float cnt, float start, float end, float frames);
    //円周1/4
    static float InCirc(float cnt, float start, float end, float frames);
    static float OutCirc(float cnt, float start, float end, float frames);
    static float InOutCirc(float cnt, float start, float end, float frames);
};

