#include <Graphics/VertexArray.hpp>

#include <Window/OpenGL.hpp>

namespace Graphics {

	VertexArray::VertexArray(void) :
		VertexArray(0) {

	}
	VertexArray::VertexArray(unsigned int _vertexCount) :
		m_Verticies(_vertexCount) {

	}
	VertexArray::~VertexArray(void) {
		clear();
	}

	void VertexArray::clear(void) {

		glDeleteBuffers(1, &m_VBO);
		glDeleteVertexArrays(1, &m_VAO);
	}

	void VertexArray::create(void) {
		clear();

		float *data = reinterpret_cast<float *>(m_Verticies.data());

		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * getVertexCount(), data, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(0 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(7 * sizeof(float)));
	}

	unsigned int VertexArray::getVertexCount(void) const {
		return m_Verticies.size();
	}

	void VertexArray::addVertex(const Vertex& _vertex) {
		m_Verticies.push_back(_vertex);
	}

	void VertexArray::render(const Window::Window& _window, RenderData _RenderData) const {
		glBindVertexArray(m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, getVertexCount());
	}
}