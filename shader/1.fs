#version 330 core

out vec4 FragColor;
in vec2 TexCoord;
//uniform sampler2D ourTexture;

void main(){
	FragColor = vec3(0.2f, 0.3f, 0.3f); //texture(ourTexture, TexCoord);
}

//#version 330 core
//out vec4 FragColor;
//  
//in vec3 ourColor;
//in vec2 TexCoord;
//
//uniform sampler2D ourTexture;
//
//void main()
//{
//    FragColor = texture(ourTexture, TexCoord);
//}
