#pragma once

#include <GLEW/glew.h>

#include <fstream>
#include <string>
#include <array>
#include <vector>

#include "message_system.h"

namespace Tiwaz::Graphic::Shader
{
	class Shader
	{
	public:
		Shader(const GLenum & shader_type);
		~Shader();

		void CompileShader(const std::string & file_path);

		void AttachShader(const GLuint & program_ID);
		void DetachShader(const GLuint & program_ID);

		const GLuint ShaderID() { return m_shader_ID; }

	private:
		GLenum m_shader_type;
		GLuint m_shader_ID = 0;

		bool m_is_compiled = false;
	};

	class ShaderProgram
	{
	public:
		ShaderProgram();
		virtual ~ShaderProgram();

		void CreateProgram(const std::array<std::string, 6>& file_paths);

		void Use();
		void Unuse();

		const GLuint UniformLocation(const std::string& uniform_name);

		const GLuint ProgramID() { return m_program_ID; }

	protected:
		void CompileProgram(const std::array<std::string, 6>& file_paths);
		void LinkProgram();

		GLuint m_program_ID = 0;

		std::vector<Shader*> m_shaders;

		bool m_is_compiled = false;
		bool m_is_linked = false;
	};
}