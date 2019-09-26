#include "matrix2x2.h"

using namespace spring;

Matrix2x2::Matrix2x2(float m11, float m12, float m21, float m22) 
{
	this->m11 = m11;
	this->m12 = m12;
	this->m21 = m21;
	this->m22 = m22;
}

Vector2 Matrix2x2::Translate(Vector2 offset, Vector2 vec2) 
{
	Matrix2x2 translation(1.0f, offset.x, 1.0f, offset.y);
	return translation * vec2;
}

Vector2 Matrix2x2::Scale(Vector2 scale, Vector2 vec2) 
{
	Matrix2x2 scaling(scale.x,0.0f,0.0f,scale.y);
	return scaling * vec2;
}

Vector2 Matrix2x2::Rotate(float angle,Vector2 vec2) 
{
	float radian = Mathf::Radian(angle);
	float cosine = Mathf::Cos(radian);
	float sine = Mathf::Sin(radian);
	Matrix2x2 rotation(cosine, -sine, sine, cosine);
	return rotation * vec2;
}

Matrix2x2 Matrix2x2::Transpose(const Matrix2x2 mat2) 
{
	Matrix2x2 result
	(
		mat2.m11,mat2.m21,
		mat2.m12,mat2.m22
	);
	return result;
}

Matrix2x2 Matrix2x2::Inverse(const Matrix2x2 mat2) 
{
	float m11, m12, m21, m22;
	m11 = (1 + (mat2.m12 * mat2.m21) / (mat2.m11 * mat2.m22 - mat2.m12 * mat2.m21)) / mat2.m11;
	m12 = -(mat2.m21) / (mat2.m11 * mat2.m22 - mat2.m12 * mat2.m21);
	m21 = (-(mat2.m11 * mat2.m12) / (mat2.m11 * mat2.m22 - mat2.m21 * mat2.m12)) / mat2.m11;
	m22 = mat2.m11 / (mat2.m11 * mat2.m22 - mat2.m21 * mat2.m12);
	Matrix2x2 result(m11,m12,m21,m22);
	return result;
}

void Matrix2x2::transpose() 
{
	Matrix2x2 mat2 = Matrix2x2::Transpose(*this);
	this->m11 = mat2.m11;
	this->m12 = mat2.m12;
	this->m21 = mat2.m21;
	this->m22 = mat2.m22;
}

void Matrix2x2::inverse()
{
	Matrix2x2 inverse = Matrix2x2::Inverse(*this);
	this->m11 = inverse.m11;
	this->m12 = inverse.m12;
	this->m21 = inverse.m21;
	this->m22 = inverse.m22;
}

Vector2 Matrix2x2::operator*(const Vector2 vec2) 
{
	Vector2 result
	(
		this->m11 * vec2.x + this->m12 * vec2.y,
		this->m21 * vec2.x + this->m22 * vec2.y
	);
	return result;
}

Matrix2x2 Matrix2x2::operator*(Matrix2x2 mat2)
{
	Matrix2x2 result
	(
		this->m11 * mat2.m11 + this->m12 * mat2.m21,
		this->m11 * mat2.m12 + this->m12 * mat2.m22,
		this->m21 * mat2.m11 + this->m22 * mat2.m21,
		this->m21 * mat2.m12 + this->m22 * mat2.m22
	);
	return result;
}

Matrix2x2 Matrix2x2::operator+(Matrix2x2 mat2) 
{
	Matrix2x2 result
	(
		this->m11 + mat2.m11,
		this->m12 + mat2.m12,
		this->m21 + mat2.m21,
		this->m22+ mat2.m22
	);
	return result;
}

Matrix2x2 Matrix2x2::operator-(Matrix2x2 mat2)
{
	Matrix2x2 result
	(
		this->m11 - mat2.m11,
		this->m12 - mat2.m12,
		this->m21 - mat2.m21,
		this->m22 - mat2.m22
	);
	return result;
}