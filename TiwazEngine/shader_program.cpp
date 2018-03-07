#include "shader_program.h"

namespace Tiwaz::Graphic::Shader
{
	Shader::Shader(const GLenum & shader_type) : m_shader_type(shader_type)
	{
		m_shader_ID = glCreateShader(m_shader_type);
	}

	Shader::~Shader()
	{
		if (m_shader_ID != 0)
		{
			glDeleteShader(m_shader_ID);
		}
	}

	void Shader::CompileShader(const std::string & file_path)
	{
		std::ifstream file("data/shaders/" + file_path);
		if (file.fail())
		{
			Log(LogSystem::TIWAZ_ERROR, "SHADER", "Failed to find shader file, with following path:\n" + file_path);
		}

		std::string fileContents;
		std::string line;

		while (std::getline(file, line))
		{
			fileContents.append(line + "\n");
		}

		file.close();

		const GLchar* contentsPtr = fileContents.c_str();
		glShaderSource(m_shader_ID, 1, &contentsPtr, nullptr);

		glCompileShader(m_shader_ID);

		GLint success = 0;
		glGetShaderiv(m_shader_ID, GL_COMPILE_STATUS, &success);

		if (success == GL_FALSE)
		{
			m_is_compiled = false;

			GLint maxLength = 0;
			glGetShaderiv(m_shader_ID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(m_shader_ID, maxLength, &maxLength, infoLog.data());

			glDeleteShader(m_shader_ID);

			std::string log = infoLog.data();
			Log(LogSystem::TIWAZ_ERROR, "SHADER", "Failed to compile shader, with following log:\n" + log);

			infoLog.clear();
		}

		m_is_compiled = true;
	}

	void Shader::AttachShader(const GLuint & program_ID)
	{
		if (m_is_compiled)
		{
			glAttachShader(program_ID, m_shader_ID);
		}
	}

	void Shader::DetachShader(const GLuint & program_ID)
	{
		glDetachShader(program_ID, m_shader_ID);
	}

	ShaderProgram::ShaderProgram()
	{
	}

	ShaderProgram::~ShaderProgram()
	{
		m_shaders.clear();

		if (m_program_ID != 0)
		{
			glDeleteProgram(m_program_ID);
		}
	}

	void ShaderProgram::CreateProgram(const std::array<std::string, 6>& file_paths)
	{
		CompileProgram(file_paths);
		LinkProgram();
	}

	void ShaderProgram::Use()
	{
		if (m_is_compiled && m_is_linked)
		{ 
			glUseProgram(m_program_ID);
		}
	}

	void ShaderProgram::Unuse()
	{
		glUseProgram(0);
	}

	const GLuint ShaderProgram::UniformLocation(const std::string & uniform_name)
	{
		GLuint location = glGetUniformLocation(m_program_ID, uniform_name.c_str());
		if (location == GL_INVALID_INDEX)
		{
			Log(LogSystem::TIWAZ_ERROR, "SHADER", "Uniform " + uniform_name + " not found in shader program!");
		}

		return location;
	}

	void ShaderProgram::CompileProgram(const std::array<std::string, 6>& file_paths)
	{
		std::string temp_string;

		for (size_t i = 0; i < file_paths.size(); ++i)
		{
			temp_string = file_paths[i];

			if (temp_string != "")
			{
				switch (i)
				{
				case 0:
					m_shaders.emplace_back(new Shader(GL_VERTEX_SHADER));
					break;
				case 1:
					m_shaders.emplace_back(new Shader(GL_TESS_CONTROL_SHADER));
					break;
				case 2:
					m_shaders.emplace_back(new Shader(GL_TESS_EVALUATION_SHADER));
					break;
				case 3:
					m_shaders.emplace_back(new Shader(GL_GEOMETRY_SHADER));
					break;
				case 4:
					m_shaders.emplace_back(new Shader(GL_FRAGMENT_SHADER));
					break;
				case 5:
					m_shaders.emplace_back(new Shader(GL_COMPUTE_SHADER));
					break;
				}

				m_shaders.back()->CompileShader(temp_string);
			}

			temp_string.clear();
		}

		m_is_compiled = true;
	}

	void ShaderProgram::LinkProgram()
	{
		m_program_ID = glCreateProgram();

		for (Shader* shader : m_shaders)
		{
			shader->AttachShader(m_program_ID);
		}

		glLinkProgram(m_program_ID);

		GLint isLinked = 0;
		glGetProgramiv(m_program_ID, GL_LINK_STATUS, &isLinked);

		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_program_ID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_program_ID, maxLength, &maxLength, infoLog.data());

			for (Shader* shader : m_shaders)
			{
				shader->DetachShader(m_program_ID);
			}

			for (Shader* shader : m_shaders)
			{
				delete shader;
				shader = nullptr;
			}

			glDeleteProgram(m_program_ID);

			std::string log = infoLog.data();
			Log(LogSystem::TIWAZ_ERROR, "SHADER_PROGRAM", "Failed to link program, with following log:\n" + log);

			infoLog.clear();
		}

		glValidateProgram(m_program_ID);

		GLint isValid = 0;
		glGetProgramiv(m_program_ID, GL_VALIDATE_STATUS, &isValid);

		if (isValid == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_program_ID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_program_ID, maxLength, &maxLength, infoLog.data());

			for (Shader* shader : m_shaders)
			{
				shader->DetachShader(m_program_ID);
			}

			for (Shader* shader : m_shaders)
			{
				delete shader;
				shader = nullptr;
			}

			glDeleteProgram(m_program_ID);

			std::string log = infoLog.data();
			Log(LogSystem::TIWAZ_ERROR, "SHADER_PROGRAM", "Failed to link program, with following log:\n" + log);

			infoLog.clear();
		}

		for (Shader* shader : m_shaders)
		{
			shader->DetachShader(m_program_ID);
		}

		for (Shader* shader : m_shaders)
		{
			delete shader;
			shader = nullptr;
		}

		m_is_linked = true;
	}
}