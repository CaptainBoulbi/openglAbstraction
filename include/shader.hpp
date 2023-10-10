#ifndef SG_SHADER_HPP
#define SG_SHADER_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace sg{

  enum ShaderType{
    VERTEX, FRAGMENT
  };

  struct ShaderCode{
    unsigned int ID;
    ShaderType type;

    int success;
    std::string log;

    ShaderCode(const char* path, ShaderType stype);
    ~ShaderCode();
  };

  struct Shader{
    unsigned int ID;

    int success;
    std::string log;

    Shader(const char* vpath, const char* fpath);
    Shader(const char* path);
    Shader(ShaderCode vcode, ShaderCode fcode);
    ~Shader();
    void use();

    void setInt(const char* name, int value);

    private:
    void compile(unsigned int idv, unsigned int idf);
  };

}

#endif
