#include "matrix4x4.h"

using namespace spring;

float& Matrix4x4::operator[](int index) 
{
	return this->m[index];
}

//Vector3 Matrix4x4::Rotate( Vector3 angle ) 
//{
//	
//}
//
//Vector3 Matrix4x4::Scale(Vector3 scale) 
//{
//
//}
//
//Vector3 Matrix4x4::Translate(Vector3 offset) 
//{
//
//}