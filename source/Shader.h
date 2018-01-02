#pragma once
#include "StdInclude.h"

#include <set>
#include <string>

class Shader {
public:
	Shader(const std::string& vshPath, const std::string& fshPath, bool bindLocation = false) :
        Shader(vshPath, fshPath, bindLocation, std::set<std::string>()) {}
	Shader(const std::string& vshPath, const std::string& fshPath, bool bindLocation, std::set<std::string> defines);

	inline void bind() { glUseProgramObjectARB(shaderProgram); }
	static inline void unbind() { glUseProgramObjectARB(0); }
	void release();

	bool setUniform(const char* uniform, float value);
	bool setUniform(const char* uniform, int value);
	bool setUniform(const char* uniform, float v0, float v1, float v2, float v3);
	bool setUniform(const char* uniform, float* value);

private:
	GLhandleARB loadShader(const std::string& filename, unsigned int mode, std::set<std::string> defines);
	void checkErrors(GLhandleARB res, int status, const std::string& errorMessage);

	GLhandleARB shaderFragment;
	GLhandleARB shaderVertex;
	GLhandleARB shaderProgram;
};
