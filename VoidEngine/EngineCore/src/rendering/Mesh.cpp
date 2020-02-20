//STD Headers

//Library Headers
#include "glad/glad.h"

//Void Engine Headers
#include "rendering/Mesh.h"
#include "rendering/BufferLayout.h"

namespace core {
	Mesh::Mesh(
		const std::vector<float>& vertices, 
		const std::vector<uint32_t>& indices, 
		const std::vector<TexturePtr>& textures
		) : MaterialColor(192.0f/255, 190.0f/255, 191.0f/255), 
		    Textures(textures) {
		
		m_VertexArray.reset(VertexArray::Create());
		m_VertexBuffer.reset(VertexBuffer::Create(vertices.data(), (uint32_t)vertices.size()));
		m_IndexBuffer.reset(IndexBuffer::Create(indices.data(), (uint32_t)indices.size()));

		BufferLayout meshLayout = {
			{ShaderDataType::FLOAT_3, "a_Position"},
			{ShaderDataType::FLOAT_3, "a_Normal"},
			{ShaderDataType::FLOAT_2, "a_TexPos"}
		};

		m_VertexBuffer->SetLayout(meshLayout);

		m_VertexArray->LinkVertexBuffer(m_VertexBuffer);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);
	}

	void Mesh::Draw(ShaderProgram* shader) const {
		unsigned diffuseNr = 1;
		unsigned specularNr = 1;
		if (shader == nullptr) {
			return;
		}

		if (Textures.size() > 0) {
			for (unsigned int i = 0; i < Textures.size(); i++)
			{
				glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
				// retrieve texture number (the N in diffuse_textureN)
				std::string number;
				auto type = Textures[i]->GetType();
				std::string typeString;

				if (type == TextureType::DIFFUSE) {
					typeString = "texture_diffuse";
					number = std::to_string(diffuseNr++);
				}
				else if (type == TextureType::SPECULAR) {
					typeString = "texture_specular";
					number = std::to_string(specularNr++);
				}

				shader->SetUniform(("material." + typeString + number).c_str(), (int)i);
				glBindTexture(GL_TEXTURE_2D, Textures[i]->GetTextureID());
			}
			glActiveTexture(GL_TEXTURE0);
		}
		else {
			//Unbinds any texture from previous draw calls
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		
		//A diffuseNr of one after the loop above implies there were no diffuse textures
		if (diffuseNr == 1) {
			//Therefore we should set the shader's default diffuse color
			shader->SetUniform("material.base_diffuse", MaterialColor);
		}

		// draw mesh
		m_VertexArray->Bind();
		glDrawElements(GL_TRIANGLES, (GLuint)m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, 0);
		m_VertexArray->Unbind();
	}

	void Mesh::Initialize() {
		for (auto& texture : Textures) {
			texture->Initialize();
		}
	}

	void Mesh::SetMaterialDiffuse(math::Color color) {
		MaterialColor = color;
	}

}