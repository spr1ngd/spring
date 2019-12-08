#pragma once
#include "guilayout.h"
#include "editorwindow.h"
#include "inspectorwindow.h"

namespace spring
{
	namespace editor 
	{
		class SpringEditor
		{
		public:
			static bool enabled;
			static void Initialize();
			static void Release();
		};
	}
}