#include <Graphics/Vertex.hpp>

namespace Graphics {
	Vertex::Vertex(void) :
		Vertex(System::Vector3f()) {}
	Vertex::Vertex(const System::Vector3f& _position) : 
		Vertex(_position, Colour::White) {}
	Vertex::Vertex(const System::Vector3f& _position, const Graphics::Colour& _colour) : 
		Vertex(_position, _colour, System::Vector2f()) {}
	Vertex::Vertex(const System::Vector3f& _position, const System::Vector2f& _texture) : 
		Vertex(_position, Colour::White, _texture) {}
	Vertex::Vertex(const System::Vector3f& _position, const Graphics::Colour& _colour, const System::Vector2f& _texture) :
		position(_position),
		colour(_colour),
		texture(_texture) {}
}