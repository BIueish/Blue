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

        void render(int x=0, int y=0);

    private:
        unsigned int loadTexture(const char* path, bool pixel);

        const char* vertexShader = "#version 330 core\n \
                                    layout (location = 0) in vec3 pos;\n \
                                    layout (location = 1) in vec2 aTexPos;\n \
                                    out vec2 texPos;\n \
                                    uniform vec3 translate;\n \
                                    void main()\n \
                                    { \n\
                                        gl_Position = vec4(pos+translate, 1.0);\n \
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