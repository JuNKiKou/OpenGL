#include "VertexArray.h"
#include "Renderer.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vBuffer, const VertexBufferLayout& layout)
{
	//bind vertex array
	Bind();

	//bind vertex buffer
	vBuffer.Bind();

	// set layout
	unsigned int offset = 0;
	const auto& attributions = layout.GetAttributions();
	for (int i = 0; i < attributions.size(); i++)
	{
		const auto& attribution = attributions[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, attribution.count, attribution.type, attribution.normalized, layout.GetStride(), (const void*)offset));
		offset += VertexBufferAttribution::GetSizeOfType(attribution.type) * attribution.count;
	}

}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}
