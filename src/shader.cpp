#include "shader.hpp"

sg::ShaderCode::ShaderCode(const char* path, ShaderType stype){
  type = stype;
  success = true;

  std::ifstream file;
  file.open(path);

  if (!file.is_open()){
    success = false;
    log = "Unable to open file";
    return;
  }

  std::string line;
  std::string code;

  bool found = false;
  while (std::getline(file, line)){
    if (!found && ((type == VERTEX && line == "#vertex shader") || (type == FRAGMENT && line == "#fragment shader"))){
      found = true;
      continue;;
    }else if (found && ((type == FRAGMENT && line == "#vertex shader") || (type == VERTEX && line == "#fragment shader"))){
      found = false;
      continue;
    }

    if (found){
      code += line + '\n';
    }
  }

  file.close();

  if (code == ""){
    success = false;
    log = "No shader type found";
    return;
  }

  const char* glCode = code.c_str();

  if (type == VERTEX) ID = glCreateShader(GL_VERTEX_SHADER);
  if (type == FRAGMENT) ID = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(ID, 1, &glCode, NULL);
  glCompileShader(ID);

  glGetShaderiv(ID, GL_COMPILE_STATUS, &success);

  if (!success){
    if (type == VERTEX)
      log = (char*)"ERROR::SHADER::VERTEX::COMPILATION_FAILED\n";
    else if (type == FRAGMENT)
      log = (char*)"ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n";

    char infoLog[512];
    glGetShaderInfoLog(ID, 512, NULL, infoLog);

    log += infoLog;
    return;
  }
}

sg::ShaderCode::~ShaderCode(){
  glDeleteShader(ID);
}


sg::Shader::Shader(const char* vpath, const char* fpath){
  ShaderCode vert(vpath, VERTEX);
  ShaderCode frag(fpath, FRAGMENT);

  if (!vert.success)
    log += vert.log;
  if (!frag.success)
    log += frag.log;

  compile(vert.ID, frag.ID);
}

sg::Shader::Shader(const char* path){
  ShaderCode vert(path, VERTEX);
  ShaderCode frag(path, FRAGMENT);

  if (!vert.success)
    log += vert.log;
  if (!frag.success)
    log += frag.log;

  compile(vert.ID, frag.ID);
}

sg::Shader::Shader(ShaderCode vcode, ShaderCode fcode){
  compile(vcode.ID, fcode.ID);
}

sg::Shader::~Shader(){
  glDeleteProgram(ID);
}

void sg::Shader::use(){
  glUseProgram(ID);
}

void sg::Shader::compile(unsigned int idv, unsigned int idf){
  ID = glCreateProgram();
  glAttachShader(ID, idv);
  glAttachShader(ID, idf);
  glLinkProgram(ID);

  char infoLog[512];
  glGetProgramiv(ID, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(ID, 512, NULL, infoLog);
    log += "ERROR::SHADER::PROGRAM::LINKING_FAILED\n";
    log += infoLog;
  }
}

void sg::Shader::setInt(const char* name, int value){
  use();
  glUniform1i(glGetUniformLocation(ID, name), value); 
}
