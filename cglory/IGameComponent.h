#pragma once
#include "IUnknown.h"

namespace cglory {
	namespace game {
		template<int ID>
		class IGameComponent :
			public IUnknownTemplate<2>
		{
		public:
			static const int compID = ID;
		};
	}
}