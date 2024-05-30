#pragma once
//�萔
//�~����
constexpr double PI = 3.14159265;
//�C�[�W���O�N���X
class Easing
{
public:
	Easing();
    //���`���
    static float Linear(float cnt, float start, float end, float frames);
    //�񎟊֐�
    static float InQuad(float cnt, float start, float end, float frames);
    static float OutQuad(float cnt, float start, float end, float frames);
    static float InOutQuad(float cnt, float start, float end, float frames);
    //�O���֐�
    static float InCubic(float cnt, float start, float end, float frames);
    static float OutCubic(float cnt, float start, float end, float frames);
    static float InOutCubic(float cnt, float start, float end, float frames);
    //�l���֐�
    static float InQuart(float cnt, float start, float end, float frames);
    static float OutQuart(float cnt, float start, float end, float frames);
    static float InOutQuart(float cnt, float start, float end, float frames);
    //�܎��֐�
    static float InQuint(float cnt, float start, float end, float frames);
    static float OutQuint(float cnt, float start, float end, float frames);
    static float InOutQuint(float cnt, float start, float end, float frames);
    //�O�p�֐��u�T�C���v
    static float InSine(float cnt, float start, float end, float frames);
    static float OutSine(float cnt, float start, float end, float frames);
    static float InOutSine(float cnt, float start, float end, float frames);
    //�w���֐�
    static float InExpo(float cnt, float start, float end, float frames);
    static float OutExpo(float cnt, float start, float end, float frames);
    static float InOutExpo(float cnt, float start, float end, float frames);
    //�~��1/4
    static float InCirc(float cnt, float start, float end, float frames);
    static float OutCirc(float cnt, float start, float end, float frames);
    static float InOutCirc(float cnt, float start, float end, float frames);
};

