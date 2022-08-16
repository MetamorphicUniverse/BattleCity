#pragma once
#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <iostream>
#include <string>
#include "glad/glad.h"

namespace Renderer {

	class Shader_Program {
	public:
		// Con/Des'ors:
		Shader_Program() = delete;
		Shader_Program(Shader_Program&) = delete;
		Shader_Program(Shader_Program&& shaderProgram) noexcept;
		Shader_Program(const std::string& vertexShader, const std::string& fragmentShader);
		~Shader_Program();
		// Op'ors:
		Shader_Program& operator= (const Shader_Program&) = delete;
		Shader_Program& operator= (Shader_Program&& shaderProgram) noexcept;
		// Met's:
		bool IsCompiled() const { return m_IsCompiled; }
		void use()const;

	private:
		bool createShader(const std::string& shaderSource, const GLenum shaderType, GLuint& shaderID);
		bool m_IsCompiled = 0;
		GLuint m_ID = 0;
	};











}

#endif