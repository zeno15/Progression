#include <Graphics/RenderData.hpp>

namespace Graphics {

	RenderData::RenderData(void) :
		RenderData(System::Mat4x4(1.0f), System::Mat4x4(1.0f)) {

	}

	RenderData::RenderData(const System::Mat4x4& _view, const System::Mat4x4& _projection) :
		RenderData(_view, _projection, std::string()) {

	}

	RenderData::RenderData(const System::Mat4x4& _view, const System::Mat4x4& _projection, const std::string& _shaderName) :
		RenderData(_view, _projection, _shaderName, nullptr) {

	}

	RenderData::RenderData(const System::Mat4x4& _view, const System::Mat4x4& _projection, const std::string& _shaderName, Graphics::Texture *_texture) :
		view(_view),
		projection(_projection),
		shaderName(_shaderName),
		texture(_texture) {

	}
}