#include "polygons.hpp"
#include<glm/glm.hpp>
#include<vector>

using namespace glm;

//Line Code
class Line {
    int shaderProgram;
    unsigned int VBO, VAO;
    std::vector<float> vertices;
    vec3 startPoint;
    vec3 endPoint;
    mat4 MVP;
    vec3 lineColor;
public:
    Line(vec3 start, vec3 end) {

        startPoint = start;
        endPoint = end;
        lineColor = vec3(1, 1, 1);
        MVP = mat4(1.0f);

        const char* vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "uniform mat4 MVP;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = MVP * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\0";
        const char* fragmentShaderSource = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "uniform vec3 color;\n"
            "void main()\n"
            "{\n"
            "   FragColor = vec4(color, 1.0f);\n"
            "}\n\0";

        // vertex shader
        int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        // check for shader compile errors

        // fragment shader
        int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        // check for shader compile errors

        // link shaders
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        // check for linking errors

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        vertices = {
             start.x, start.y, start.z,
             end.x, end.y, end.z,

        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

    }

    int setMVP(mat4 mvp) {
        MVP = mvp;
        return 1;
    }

    int setColor(vec3 color) {
        lineColor = color;
        return 1;
    }

    int draw() {
        glUseProgram(shaderProgram);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "MVP"), 1, GL_FALSE, &MVP[0][0]);
        glUniform3fv(glGetUniformLocation(shaderProgram, "color"), 1, &lineColor[0]);

        glBindVertexArray(VAO);
        glLineWidth(10.0f);
        glDrawArrays(GL_LINES, 0, 2);
        return 1;
    }

    ~Line() {

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteProgram(shaderProgram);
    }
};


cube::cube(GLfloat x, GLfloat y, GLfloat z,GLfloat edgelength){
  GLfloat halfLength = edgelength/2;
  data[0] =  x - halfLength;
  data[1] =  y + halfLength;
  data[2] =  z + halfLength;

  data[3] =  x + halfLength;
  data[4] =  y + halfLength;
  data[5] =  z + halfLength;

  data[6] =  x - halfLength;
  data[7] =  y - halfLength;
  data[8] =  z + halfLength;

  data[9] =  x + halfLength;
  data[10] = y - halfLength;
  data[11] = z + halfLength;

  data[12] = x - halfLength;
  data[13] = y + halfLength;
  data[14] = z - halfLength;

  data[15] = x + halfLength;
  data[16] = y + halfLength;
  data[17] = z - halfLength;

  data[18] = x - halfLength;
  data[19] = y - halfLength;
  data[20] = z - halfLength;

  data[21] = x + halfLength;
  data[22] = y - halfLength;
  data[23] = z - halfLength;
};
cube::~cube(){
};
GLfloat* cube::getVertexData(){
  return data;
};
GLuint* cube::getIndexData(){
  return indices;
};
