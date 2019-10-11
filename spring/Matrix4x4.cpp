#include "matrix4x4.h"

using namespace spring;

Matrix4x4::Matrix4x4(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44)
{
	this->m11 = m11;
	this->m12 = m12;
	this->m13 = m13;
	this->m14 = m14;
	this->m21 = m21;
	this->m22 = m22;
	this->m23 = m23;
	this->m24 = m24;
	this->m31 = m31;
	this->m32 = m32;
	this->m33 = m33;
	this->m34 = m34;
	this->m41 = m41;
	this->m42 = m42;
	this->m43 = m43;
	this->m44 = m44;
}

float& Matrix4x4::operator[](int index) 
{
	return this->m[index];
}

Vector3 Matrix4x4::Rotate(float angle,Vector3 axis,Vector3 vec3)
{
	// todo 
	return vec3;
}

Matrix4x4 Matrix4x4::RotateX(float angle) 
{
	float sinine = Mathf::Sin(angle);
	float cosine = Mathf::Cos(angle);
	Matrix4x4 result
	(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, cosine, sinine, 0.0f,
		0.0f, -sinine, cosine, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
	return result;
}

Matrix4x4 Matrix4x4::RotateY(float angle) 
{
	float sinine = Mathf::Sin(angle);
	float cosine = Mathf::Cos(angle);
	Matrix4x4 result
	(
		cosine, 0.0f, -sinine, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		sinine, 0.0f, cosine, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
	return result;
}

Matrix4x4 Matrix4x4::RotateZ(float angle) 
{
	float sinine = Mathf::Sin(angle);
	float cosine = Mathf::Cos(angle);
	Matrix4x4 result
	(
		cosine, sinine, 0.0f, 0.0f,
		-sinine, cosine, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0, 1.0f
	);
	return result;
}

Vector3 Matrix4x4::Scale(Vector3 scale, Vector3 vec3)
{
	Matrix4x4 scaling
	(
		scale.x, 0.0f, 0.0f, 0.0f,
		0.0f, scale.y, 0.0f, 0.0f,
		0.0f, 0.0f, scale.z, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f
	);
	return scaling * vec3;
}

Matrix4x4 Matrix4x4::Scale(float x, float y, float z)
{
	Matrix4x4 scaling
	(
		x, 0.0f, 0.0f, 0.0f,
		0.0f, y, 0.0f, 0.0f,
		0.0f, 0.0f, z, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f
	);
	return scaling;
}

Vector3 Matrix4x4::Translate(Vector3 offset, Vector3 vec3)
{
	Matrix4x4 tranlation
	(
		1.0f,0.0f,0.0f,offset.x,
		0.0f,1.0f,0.0f,offset.y,
		0.0f,0.0f,1.0f,offset.z,
		0.0f,0.0f,0.0f,1.0f
	);
	return tranlation * vec3;
}

Matrix4x4 Matrix4x4::Translate(float x, float y, float z) 
{
	Matrix4x4 translation
	(
		1.0f,0.0f,0.0f,x,
		0.0f,1.0f,0.0f,y,
		0.0f,0.0f,1.0f,z,
		0.0f,0.0f,0.0f,1.0f
	);
	return translation;
}

Matrix4x4 Matrix4x4::Transpose(const Matrix4x4 mat4) 
{ 
	// todo 
	return mat4;
}

Matrix4x4 Matrix4x4::Inverse(const Matrix4x4 mat4) 
{
	// todo
	return mat4;
}

void Matrix4x4::transpose() 
{
	// todo 
}

void Matrix4x4::inverse() 
{
	// todo 
}

Matrix4x4 Matrix4x4::operator+(const Matrix4x4 mat4) 
{
	Matrix4x4 result
	(
		this->m11 + mat4.m11, this->m12 + mat4.m12, this->m13 + mat4.m13, this->m14 + mat4.m14,
		this->m21 + mat4.m21, this->m22 + mat4.m22, this->m23 + mat4.m23, this->m24 + mat4.m24,
		this->m31 + mat4.m31, this->m32 + mat4.m32, this->m33 + mat4.m33, this->m34 + mat4.m34,
		this->m41 + mat4.m41, this->m42 + mat4.m42, this->m43 + mat4.m43, this->m44 + mat4.m44
	);
	return result;
}

Matrix4x4 Matrix4x4::operator-(const Matrix4x4 mat4) 
{
	Matrix4x4 result
	(
		this->m11 - mat4.m11, this->m12 - mat4.m12, this->m13 - mat4.m13, this->m14 - mat4.m14,
		this->m21 - mat4.m21, this->m22 - mat4.m22, this->m23 - mat4.m23, this->m24 - mat4.m24,
		this->m31 - mat4.m31, this->m32 - mat4.m32, this->m33 - mat4.m33, this->m34 - mat4.m34,
		this->m41 - mat4.m41, this->m42 - mat4.m42, this->m43 - mat4.m43, this->m44 - mat4.m44
	);
	return result;
}

Matrix4x4 Matrix4x4::operator*(const float f) 
{
	Matrix4x4 result
	(
		this->m11 * f, this->m12 * f, this->m13 * f, this->m14 * f,
		this->m21 * f, this->m22 * f, this->m23 * f, this->m24 * f,
		this->m31 * f, this->m32 * f, this->m33 * f, this->m34 * f,
		this->m41 * f, this->m42 * f, this->m43 * f, this->m44 * f
	);
	return result;
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4 mat4) 
{
	Matrix4x4 result
	(
		this->m11 * mat4.m11 + this->m12 * mat4.m21 + this->m13 * mat4.m31 + this->m14 * mat4.m41,
		this->m11 * mat4.m12 + this->m12 * mat4.m22 + this->m13 * mat4.m32 + this->m14 * mat4.m42,
		this->m11 * mat4.m13 + this->m12 * mat4.m23 + this->m13 * mat4.m33 + this->m14 * mat4.m43,
		this->m11 * mat4.m14 + this->m12 * mat4.m24 + this->m13 * mat4.m34 + this->m14 * mat4.m44,

		this->m21 * mat4.m11 + this->m22 * mat4.m21 + this->m23 * mat4.m31 + this->m24 * mat4.m41,
		this->m21 * mat4.m12 + this->m22 * mat4.m22 + this->m23 * mat4.m32 + this->m24 * mat4.m42,
		this->m21 * mat4.m13 + this->m22 * mat4.m23 + this->m23 * mat4.m33 + this->m24 * mat4.m43,
		this->m21 * mat4.m14 + this->m22 * mat4.m24 + this->m23 * mat4.m34 + this->m24 * mat4.m44,

		this->m31 * mat4.m11 + this->m32 * mat4.m21 + this->m33 * mat4.m31 + this->m34 * mat4.m41,
		this->m31 * mat4.m12 + this->m32 * mat4.m22 + this->m33 * mat4.m32 + this->m34 * mat4.m42,
		this->m31 * mat4.m13 + this->m32 * mat4.m23 + this->m33 * mat4.m33 + this->m34 * mat4.m43,
		this->m31 * mat4.m14 + this->m32 * mat4.m24 + this->m33 * mat4.m34 + this->m34 * mat4.m44,

		this->m41 * mat4.m11 + this->m42 * mat4.m21 + this->m43 * mat4.m31 + this->m44 * mat4.m41,
		this->m41 * mat4.m12 + this->m42 * mat4.m22 + this->m43 * mat4.m32 + this->m44 * mat4.m42,
		this->m41 * mat4.m13 + this->m42 * mat4.m23 + this->m43 * mat4.m33 + this->m44 * mat4.m43,
		this->m41 * mat4.m14 + this->m42 * mat4.m24 + this->m43 * mat4.m34 + this->m44 * mat4.m44
	);
	return result;
}

Vector2 Matrix4x4::operator*(const Vector2 vec2) 
{
	Vector4 result
	(
		this->m11 * vec2.x + this->m12 * vec2.y,
		this->m21 * vec2.x + this->m22 * vec2.y,
		this->m31 * vec2.x + this->m32 * vec2.y,
		this->m41 * vec2.x + this->m42 * vec2.y
	);
	return result;
}

Vector3 Matrix4x4::operator*(const Vector3 vec3) 
{
	Vector4 result
	(
		this->m11 * vec3.x + this->m12 * vec3.y + this->m13 * vec3.z,
		this->m21 * vec3.x + this->m22 * vec3.y + this->m23 * vec3.z,
		this->m31 * vec3.x + this->m32 * vec3.y + this->m33 * vec3.z,
		this->m41 * vec3.x + this->m42 * vec3.y + this->m43 * vec3.z
	);
	return result;
}

Vector4 Matrix4x4::operator*(const Vector4 vec4) 
{
	Vector4 result
	(
		this->m11 * vec4.x + this->m12 * vec4.y + this->m13 * vec4.z + this->m14 * vec4.w,
		this->m21 * vec4.x + this->m22 * vec4.y + this->m23 * vec4.z + this->m24 * vec4.w,
		this->m31 * vec4.x + this->m32 * vec4.y + this->m33 * vec4.z + this->m34 * vec4.w,
		this->m41 * vec4.x + this->m42 * vec4.y + this->m43 * vec4.z + this->m44 * vec4.w
	);
	return result;
}