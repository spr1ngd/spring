#pragma once
#include "vector2.h"
#include "transform.h"
#include "node.h"

namespace spring 
{
	class RectTransform : public Node
	{
	public:
		Vector2 pivot;
		Vector2 size;

	public:
		RectTransform();

		void SetPivot(Vector2 pivot);
	};
}