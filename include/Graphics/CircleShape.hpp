#ifndef INCLUDED_GRAPHICS_CIRCLE_SHAPE_HPP_
#define INCLUDED_GRAPHICS_CIRCLE_SHAPE_HPP_

#include <Graphics/Renderable.hpp>
#include <Graphics/VertexArray.hpp>
#include <System/Transformable2D.hpp>

////////////////////////////////////////////////////////////
///
///	\namespace Graphics
///
////////////////////////////////////////////////////////////
namespace Graphics {
	class CircleShape : public Renderable, public System::Transformable2D {
	public:
		////////////////////////////////////////////////////////////
		///
		///	\brief	Constructor
		///
		///	\param	The radius of the circle
		///
		////////////////////////////////////////////////////////////
		CircleShape(float _radius);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Constructor
		///
		///	\param	The radius of the circle
		///
		///	\param	The number of segments
		///
		////////////////////////////////////////////////////////////
		CircleShape(float _radius, unsigned int _segments);


		////////////////////////////////////////////////////////////
		///
		///	\brief	Renders the circle
		///
		///	\param	The window to render to
		///
		///	\param	The render states to use
		///
		////////////////////////////////////////////////////////////
		virtual void render(const Window::Window& _window, RenderData _renderData) const override;

		////////////////////////////////////////////////////////////
		///
		///	\brief	Sets the number of segments for the circle
		///
		///	\param	The number of segments
		///
		////////////////////////////////////////////////////////////
		void setNumberOfSegments(unsigned int _number);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Sets the radius of the circle
		///
		///	\param	The radius
		///
		////////////////////////////////////////////////////////////
		void setRadius(float _radius);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Sets the colour of the circle
		///
		///	\param	The colour
		///
		////////////////////////////////////////////////////////////
		void setColour(Colour _colour);

	private:
		void regenerateVerticies(void);

	private:
		float				m_Radius;				///<	The radius
		unsigned int		m_NumberSegments;		///<	The number of segments
		VertexArray			m_VertexArray;			///<	The vertex array
		Colour				m_Colour;				///<	The colour
	};
}

#endif // INCLUDED_GRAPHICS_CIRCLE_SHAPE_HPP_