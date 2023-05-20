#pragma once
#include <vector>
#include "GL/glew.h"

#define ASSERT(x) if (!(x)) __debugbreak();

struct VertexBufferAttribution
{
	unsigned int type;
	unsigned int count;
	unsigned int normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT:          return 4;
			case GL_UNSIGNED_INT:   return 4;
			case GL_UNSIGNED_BYTE:  return 1;
		default:
			ASSERT(false);
			return 0;
		}	
	}
};

class VertexBufferLayout
{

private:
	std::vector<VertexBufferAttribution> m_attributions;
	unsigned int m_Stride;

public:
	VertexBufferLayout()
		: m_Stride(0) {};

	template<typename T>
	void Push(unsigned int count)
	{
		//static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		m_attributions.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += VertexBufferAttribution::GetSizeOfType(GL_FLOAT) * count;
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_attributions.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += VertexBufferAttribution::GetSizeOfType(GL_UNSIGNED_INT) * count;
	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_attributions.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += VertexBufferAttribution::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
	}

	inline const std::vector<VertexBufferAttribution> GetAttributions() const { return m_attributions; }
	inline const unsigned int GetStride() const { return m_Stride; }
};
