#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

struct Shader {
	public:
		unsigned int ID;

		Shader(const char* vertexPath, const char* fragmentPath){
			// get shader code
			const char* vertexCode;
			const char* fragmentCode;



			// compile shader
			unsigned int vertexId, fragmentId;

			vertexId = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertexId, 1, &vertexCode, NULL);
			glCompileShader(vertexId);
			checkCompileErrors(vertexId, "VERTEX");

			fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragmentId, 1, &fragmentCode, NULL);
			glCompileShader(fragmentId);
			checkCompileErrors(fragmentId, "FRAGMENT");

			ID = glCreateProgram();
			glAttachShader(ID, vertexId);
			glAttachShader(ID, fragmentId);
			glLinkProgram(ID);
			checkCompileErrors(ID, "PROGRAM");

			glDeleteShader(vertexId);
			glDeleteShader(fragmentId);
		}

		Shader(const char* shaderPath){
			Shader(shaderPath, shaderPath);
		}

		void use(){ 
			glUseProgram(ID); 
		}
		void setBool(const char* name, bool value){         
			glUniform1i(glGetUniformLocation(ID, name), (int)value); 
		}
		void setInt(const char* name, int value){ 
			glUniform1i(glGetUniformLocation(ID, name), value); 
		}
		void setFloat(const char* name, float value){ 
			glUniform1f(glGetUniformLocation(ID, name), value); 
		}
		void setVec2(const char* name, const glm::vec2 &value){ 
			glUniform2fv(glGetUniformLocation(ID, name), 1, &value[0]); 
		}
		void setVec2(const char* name, float x, float y) const{ 
			glUniform2f(glGetUniformLocation(ID, name), x, y); 
		}
		void setVec3(const char* name, const glm::vec3 &value){ 
			glUniform3fv(glGetUniformLocation(ID, name), 1, &value[0]); 
		}
		void setVec3(const char* name, float x, float y, float z){ 
			glUniform3f(glGetUniformLocation(ID, name), x, y, z); 
		}
		void setVec4(const char* name, const glm::vec4 &value){ 
			glUniform4fv(glGetUniformLocation(ID, name), 1, &value[0]); 
		}
		void setVec4(const char* name, float x, float y, float z, float w){ 
			glUniform4f(glGetUniformLocation(ID, name), x, y, z, w); 
		}
		void setMat2(const char* name, const glm::mat2 &mat){
			glUniformMatrix2fv(glGetUniformLocation(ID, name), 1, GL_FALSE, &mat[0][0]);
		}
		void setMat3(const char* name, const glm::mat3 &mat){
			glUniformMatrix3fv(glGetUniformLocation(ID, name), 1, GL_FALSE, &mat[0][0]);
		}
		void setMat4(const char* name, const glm::mat4 &mat){
			glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, &mat[0][0]);
		}

	private:
		void checkCompileErrors(GLuint shader, std::string type){
			GLint success;
			GLchar infoLog[1024];
			if (type != "PROGRAM"){
				glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
				if (!success){
					glGetShaderInfoLog(shader, 1024, NULL, infoLog);
					std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << std::endl;
				}
			}else{
				glGetProgramiv(shader, GL_LINK_STATUS, &success);
				if (!success){
					glGetProgramInfoLog(shader, 1024, NULL, infoLog);
					std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << std::endl;
				}
			}
		}
};
#endif
