#pragma once

#ifndef RESOURCESMANAGER_H
#define RESOURCESMANAGER_H

#include <string>
#include <memory>
#include <map>


namespace Renderer {
	class Shader_Program;
}

class ResourcesManager {
public:
	ResourcesManager() = delete;
	ResourcesManager(ResourcesManager&) = delete;
	ResourcesManager(ResourcesManager&&) = delete;
	ResourcesManager(const std::string& resPath);
	~ResourcesManager() = default;

	ResourcesManager& operator= (const ResourcesManager&) = delete;
	ResourcesManager& operator= (ResourcesManager&&) = delete;

	std::shared_ptr<Renderer::Shader_Program> loadShaders(const std::string shaderName, const std::string& vertexPath, const std::string& fragmentPath);
	std::shared_ptr<Renderer::Shader_Program> getShader(const std::string shaderName);
	void loadTexture(const std::string& textureName, const std::string& texturePath);

private:
	typedef std::map<const std::string, std::shared_ptr<Renderer::Shader_Program>> ShaderProgramsMap;
	ShaderProgramsMap m_ShaderPrograms;
	std::string m_Path;

	std::string readFile(const std::string& relativePath);
};


#endif // !RESOURCESMANAGER_H
