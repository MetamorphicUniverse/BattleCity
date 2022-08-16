#include "Shader_Program.h"

Renderer::Shader_Program::Shader_Program(Shader_Program&& shaderProgram) noexcept
{
	m_ID = shaderProgram.m_ID;
	m_IsCompiled = shaderProgram.m_IsCompiled;

	shaderProgram.m_ID = 0;
	shaderProgram.m_IsCompiled = false;
}

Renderer::Shader_Program::Shader_Program(const std::string& vertexShader, const std::string& fragmentShader)
{
	// Create vertex shader
	GLuint vertexShaderID;
	if (!createShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID)) {
		std::cerr <<"VERTEX SHADER Compile time error" << std::endl;
		return;
	}
	// Create fragmetn shader
	GLuint fragmentShaderID;
	if (!createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID)) {
		std::cerr << "FRAGMENT SHADER Compile time error" << std::endl;
		glDeleteShader(vertexShaderID);
		return;
	}
	// Attaching shaders programs to drivers
	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertexShaderID);
	glAttachShader(m_ID, fragmentShaderID);
	glLinkProgram(m_ID);
	// 
	GLint success;
	glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[1024];
		glGetShaderInfoLog(m_ID, 1024, nullptr, infoLog);
		std::cerr << "ERROR::SHADER: Link Time Error:\n" << infoLog << std::endl;
	}
	else
	{
		m_IsCompiled = true;
	}

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}


Renderer::Shader_Program::~Shader_Program()
{
	glDeleteProgram(m_ID);
}


	Renderer::Shader_Program& Renderer::Shader_Program::operator=(Shader_Program&& shaderProgram) noexcept
	{
		glDeleteProgram(m_ID);
		m_ID = shaderProgram.m_ID;
		m_IsCompiled = shaderProgram.m_IsCompiled;

		shaderProgram.m_ID = 0;
		shaderProgram.m_IsCompiled = false;
		return *this;
	}



void Renderer::Shader_Program::use() const
{
	glUseProgram(m_ID);
}

bool Renderer::Shader_Program::createShader(const std::string& shaderSource, const GLenum shaderType, GLuint& shaderID)
{
	shaderID = glCreateShader(shaderType);
	const char* code = shaderSource.c_str();
	glShaderSource(shaderID, 1, &code, nullptr);
	glCompileShader(shaderID);

	GLint compileStatus;
	glGetShaderiv( shaderID, GL_COMPILE_STATUS, &compileStatus);
	if (!compileStatus) {
		GLchar infoLog[1024];
		glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
		std::cerr << "ERROR::SHADER: Compile Time Error:\n" << infoLog << std::endl;
		return false;
	}
	return true;
}
