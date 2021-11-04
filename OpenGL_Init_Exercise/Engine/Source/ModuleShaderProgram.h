#pragma once
#include "Module.h"

class Application;

class ModuleShaderProgram : public Module
{
public:
	ModuleShaderProgram();

	bool Init();

	void CreateProgram(unsigned int vertex_shader_id, unsigned int fragment_shader_id) const;

	void LoadProgramSource(const char* file_name) const;

	unsigned int CompileShader(unsigned int type, const char* source);
	
	unsigned int GetProgramId();

	~ModuleShaderProgram();

private:
	unsigned int program_id;
	unsigned int vertex_shader_id;
	unsigned int fragment_shader_id;
};

