#ifndef INCLUDED_SYSTEM_TRANSFORMABLE_2D_HPP_
#define INCLUDED_SYSTEM_TRANSFORMABLE_2D_HPP_

#include <System/Vector2.hpp>
#include <System/Mat4x4.hpp>

////////////////////////////////////////////////////////////
///
///	\namespace	System
///
////////////////////////////////////////////////////////////
namespace System {
	////////////////////////////////////////////////////////////
	///
	///	\brief	Class to represent a 2D transformable object
	///
	////////////////////////////////////////////////////////////
	class Transformable2D {
	public:
		////////////////////////////////////////////////////////////
		///
		///	\brief	Constructor
		///
		////////////////////////////////////////////////////////////
		Transformable2D(void);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Adds a translation
		///
		///	\param	The translation
		///
		////////////////////////////////////////////////////////////
		void translate(const Vector2f& _translation);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Sets the translation
		///
		///	\param	The translation
		///
		////////////////////////////////////////////////////////////
		void setTranslate(const Vector2f& _translation);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Adds a rotation around the z axis
		///
		///	\param	The rotation value
		///
		////////////////////////////////////////////////////////////
		void rotate(float _rotation);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Sets the rotation around the z axis
		///
		///	\param	The rotation value
		///
		////////////////////////////////////////////////////////////
		void setRotation(float _rotation);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Scales the transformation
		///
		///	\param	The scale factors
		///
		////////////////////////////////////////////////////////////
		void scale(const Vector2f& _scale);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Sets the scale of the transformation
		///
		///	\param	The new scale
		///
		////////////////////////////////////////////////////////////
		void setScale(const Vector2f& _scale);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Resets the transformable
		///
		////////////////////////////////////////////////////////////
		void resetTransformable(void);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets the position 
		///
		///	\return	The position
		///
		////////////////////////////////////////////////////////////
		const Vector2f& getPosition(void) const;
		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets the rotatation
		///
		///	\return	The rotation
		///
		////////////////////////////////////////////////////////////
		float getRotation(void) const;
		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets the scale
		///
		///	\return	The scale
		///
		////////////////////////////////////////////////////////////
		const Vector2f& getScale(void) const;

		////////////////////////////////////////////////////////////
		///
		///	\brief	Transforms a point for the current transform
		///
		///	\param	The point to transform
		///
		///	\return	The transformed point
		///
		////////////////////////////////////////////////////////////
		Vector2f transformPoint(const Vector2f& _point) const;

	private:
		Vector2f		m_Position;			///<	Accumulated position
		float			m_Rotation;			///<	Accumulated rotation
		Vector2f		m_Scale;			///<	Accumulated scale
	};
}

#endif // INCLUDED_SYSTEM_TRANSFORMABLE_2D_HPP_