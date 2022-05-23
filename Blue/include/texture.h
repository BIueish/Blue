#ifndef TEXTURE_H
#define TEXTURE_H

namespace blue
{

    class Texture
    {
    public:
        unsigned int VBO;
        unsigned int EBO;
        unsigned int VAO;
        unsigned int textureID;
        int width;
        int height;
        unsigned int shader;

        Texture(const char* path, bool pixel=false);

        ~Texture();

        void render(int x=0, int y=0, int dwidth=-1, int dheight=-1, int degrees=0);

    private:
        unsigned int loadTexture(const char* path, bool pixel);

        const char* vertexShader = "#version 330 core\n \
                                    layout (location = 0) in vec3 pos;\n \
                                    layout (location = 1) in vec2 aTexPos;\n \
                                    out vec2 texPos;\n \
                                    uniform vec3 translate;\n \
                                    uniform vec3 scale;\n \
                                    uniform mat4 rotate;\n \
                                    uniform vec2 centre;\n \
                                    void main()\n \
                                    { \n vec4 pos2 = ((vec4((pos+vec3(1.0, -1.0, 0.0))*scale, 1.0)-vec4(centre, 0.0, 0.0))*rotate)-vec4(vec2(1.0, -1.0)-centre, 0.0, 0.0);\n \
                                        gl_Position = pos2+vec4(translate, 0.0);\n \
                                        texPos = aTexPos;\n \
                                    }";

        const char* fragmentShader = "#version 330 core \n\
                                    in vec2 texPos; \n\
                                    out vec4 fragOut; \n\
                                    uniform sampler2D aTexture; \n\
                                    void main() \n\
                                    { \n\
                                        fragOut = texture(aTexture, texPos); \n\
                                    }  ";
    
    };

}

#endif