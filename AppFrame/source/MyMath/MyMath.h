#pragma once
#include <math.h>
//ŒvZŠÖ˜AŠÖ”‚ğ‚Ü‚Æ‚ß‚½ƒNƒ‰ƒX
class MyMath
{
	//‰~ü—¦
	static constexpr double PI = 3.14159265;
public:
	MyMath();
	~MyMath();
	//Šp“x’PˆÊ‚Ì•ÏŠ·
	//degree->rad
	template<typename T>
	static T DegToRad(T deg) { return deg * PI / 180.0; }
	//rad->degree
	template<typename T>
	static T RadToDeg(T rad) { return rad * 180.0 / PI; }
	//”÷¬‚È’l‚Æ‚Ì”äŠr
	static bool NearZero(double vol, double epsiron = 0.001);
	//‹…–ÊÀ•WŒn‚©‚çƒfƒJƒ‹ƒgÀ•WŒn‚É•ÏŠ·‚·‚é
	static class Vector3D ConvertToCartesian(class Vector3D angle, float radius);
	//Å’Z‹——£Œn
	//“_‚Æ’¼ü‚ÌÅ’Z‹——£
	static float DisPointAndLine(class Vector3D& v1, class Vector3D& v2s, class Vector3D& v2e, class Vector3D& mp, double& t);
	//“_‚Æü•ª‚ÌÅ’Z‹——£
	static float DisPointAndSegment(class Vector3D& v1, class Vector3D& v2s, class Vector3D& v2e, class Vector3D& mp, double& t);
	//’¼ü‚Æ’¼ü‚ÌÅ’Z‹——£
	static float DisLineAndLine(class Vector3D& v1s, class Vector3D& v1e, class Vector3D& v1m, double& t1, class Vector3D& v2s, class Vector3D& v2e, class Vector3D& v2m, double& t2);
	//ü•ª‚Æü•ª‚ÌÅ’Z‹——£
	static float DisSegAndSeg(class Vector3D& v1s, class Vector3D& v1e, class Vector3D& v1m, double& t1, class Vector3D& v2s, class Vector3D& v2e, class Vector3D& v2m, double& t2);
	//“_‚ÆAABB‚ÌÅ’Z‹——£
	static float DisPointAndAABB(class Vector3D v1, double w1, double h1, double d1, class Vector3D v2);
	//“–‚½‚è”»’èŒn
	//“_‚ÆîŒ`‚Ì“–‚½‚è”»’è
	static bool ColPointAndFan(class Vector3D v1, class Vector3D v2, float rad);
};
