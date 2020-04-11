#include "Jankpch.h"
#include "Layer.h"

namespace Jank {

	Layer::Layer(const std::string& debugName)
		: m_DebugName(debugName)
	{}

	Layer::~Layer() {}
}