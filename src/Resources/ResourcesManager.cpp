#include "ResourcesManager.h"
#include "../Renderer/Shader_Program.h"
#include <sstream>
#include <fstream>
#include <iostream>

// Constructor()
//===================================================================================================
ResourcesManager::ResourcesManager(const std::string& resPath)
{
	size_t found = resPath.find_last_of("/\\");
	m_Path = resPath.substr(0,found);

}

// public: .loadShaders()
//===================================================================================================
std::shared_ptr<Renderer::Shader_Program> ResourcesManager::loadShaders(const std::string shaderName, const std::string& vertexPath, const std::string& fragmentPath)
{
	std::string vertexString = readFile(vertexPath);
	if (vertexString.empty()) {
		std::cerr << "No vertex shader" << std::endl;
		return nullptr;
	}
	std::string fragmentString = readFile(fragmentPath);
	if (fragmentString.empty()) {
		std::cerr << "No fragment shader" << std::endl;
		return nullptr;
	}
	std::shared_ptr<Renderer::Shader_Program>& newShader = m_ShaderPrograms.emplace(shaderName, std::make_shared <Renderer::Shader_Program>(vertexString, fragmentString)).first->second;
	if (newShader->IsCompiled()) {
		return newShader;
	}
	std::cerr << "Can't load shader program:\n"
		<< "Vertex: " << vertexPath
		<< "Fragment: " << fragmentPath << std::endl;
	return nullptr;
}

// public: .getShader()
//===================================================================================================
std::shared_ptr<Renderer::Shader_Program> ResourcesManager::getShader(const std::string shaderName)
{
	ShaderProgramsMap::const_iterator it = m_ShaderPrograms.find(shaderName);
	if (it != m_ShaderPrograms.end())
	{
		return it->second;
	}
	std::cerr << "Can't find the shader program: " << shaderName << std::endl;
	return nullptr;
}

// private: .readFile()
//===================================================================================================
std::string ResourcesManager::readFile(const std::string& relativePath)
{
	std::ifstream inp;
	std::stringstream sb;
	inp.open(m_Path + "/" + relativePath.c_str(), std::ios::in | std::ios::binary);
	if (!inp.is_open()) {
		std::cerr << "ResourcesManager can't open file path" << std::endl;
		exit(-5);
	}
	else {
		
		sb << inp.rdbuf();
	}
	inp.close();


	return sb.str();
}

//===================================================================================================