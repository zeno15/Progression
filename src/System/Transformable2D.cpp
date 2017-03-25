#include <System/Transformable2D.hpp>

#define TO_RADIANS(x) (x * 3.14159265f / 180.0f)

namespace System {

	Transformable2D::Transformable2D(void) :
		m_Position(0.0f, 0.0f),
		m_Rotation(0.0f),
		m_Scale(1, 1) {
	}

	void Transformable2D::translate(const Vector2f& _translation) {
		m_Position += _translation;
	}
	void Transformable2D::setTranslate(const Vector2f& _translation) {
		m_Position = _translation;
	}

	void Transformable2D::rotate(float _rotation) {
		m_Rotation += _rotation;
	}
	void Transformable2D::setRotation(float _rotation) {
		m_Rotation = _rotation;
	}

	void Transformable2D::scale(const Vector2f& _scale) {
		m_Scale.x *= _scale.x;
		m_Scale.y *= _scale.y;
	}
	void Transformable2D::setScale(const Vector2f& _scale) {
		m_Scale = _scale;
	}

	void Transformable2D::resetTransformable(void) {
		m_Position = Vector2f();
		m_Scale = Vector2f(1.0f, 1.0f);
		m_Rotation = 0.0f;
	}

	const Vector2f& Transformable2D::getPosition(void) const {
		return m_Position;
	}
	float Transformable2D::getRotation(void) const {
		return m_Rotation;
	}
	const Vector2f& Transformable2D::getScale(void) const {
		return m_Scale;
	}
	
	Vector2f Transformable2D::transformPoint(const Vector2f& _point) const {
		return Vector2f(
				_point.x * (std::cosf(TO_RADIANS(m_Rotation)) - std::sinf(TO_RADIANS(m_Rotation))) * m_Scale.x,
				_point.y * (std::cosf(TO_RADIANS(m_Rotation)) + std::sinf(TO_RADIANS(m_Rotation))) * m_Scale.y) 
			+ m_Position;
	}

}