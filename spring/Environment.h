#pragma once
#include "color.h"

namespace spring
{
	class Environment 
	{
	public:
		class AmbientSetting 
		{
		public:
			Color color;

			AmbientSetting() 
			{
				this->color = Color(50, 50, 50, 255);
			}
		};

		class ShadowSetting 
		{
		public:
			enum SampleLevel : int
			{
				Disable = 0,
				Double = 2,
				Quadruple = 4,
				Octuple = 8
			};

			SampleLevel sample = SampleLevel::Disable;

			ShadowSetting()
			{
				// sample = SampleLevel::Double;
			}
		};
	private:
		static AmbientSetting ambient;
		static ShadowSetting shadow;

	public:

		static const AmbientSetting& GetAmbientSetting();
		static const ShadowSetting& GetShadowSetting();

		static void SetAmbientSetting(Color ambientColor);
		static void SetShodowSetting(ShadowSetting::SampleLevel shadowSampleLevel);
	};
}