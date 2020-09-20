// #include "glee/GLee.h"
#include <GL/glew.h>

#include "glslshader.h"
#include "targa.h"
#include "tree.h"

//for matrix calculation
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

//An auto_ptr frees it's memory automatically
auto_ptr<GLSLProgram> Tree::m_alphaTestProgram = auto_ptr<GLSLProgram>();
GLuint Tree::m_treeTexID = 0;
GLuint Tree::m_vertexBuffer = 0;
GLuint Tree::m_texCoordBuffer = 0;

const string TreeTexturePath = "data/beech.tga";

Tree::Tree(float x, float y, float z):
x(x),
y(y),
z(z)
{
    
}

void Tree::initializeVBOs() 
{
    GLfloat vertex [] = { 
        -1.0f, 0.0f, 0.0f, //First Square vertex
         1.0f, 0.0f, 0.0f,
        -1.0f, 2.0f, 0.0f,
         1.0f, 2.0f, 0.0f,  //Last Square vertex
         0.0f, 0.0f, 1.0f, //First Square vertex
         0.0f, 0.0f,-1.0f,
         0.0f, 2.0f, 1.0f,  //Last Square vertex
         0.0f, 2.0f,-1.0f,
         
    };

    GLfloat texCoord [] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,        
        0.0f, 1.0f,
        1.0f, 1.0f,
    };

    glGenBuffers(1, &m_vertexBuffer); //Generate a buffer for the vertices
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer); //Bind the vertex buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8 * 3, &vertex[0], GL_STATIC_DRAW); //Send the data to OpenGL

    glGenBuffers(1, &m_texCoordBuffer); //Generate a buffer for the vertices
    glBindBuffer(GL_ARRAY_BUFFER, m_texCoordBuffer); //Bind the vertex buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8 * 2, &texCoord[0], GL_STATIC_DRAW); //Send the data to OpenGL
}

bool Tree::initialize() 
{
    if (m_treeTexID == 0) {
        //Only load the tree texture once if there is no texture ID already
        TargaImage treeTexture;
        if (!treeTexture.load(TreeTexturePath)) {
            return false;
        }

        glGenTextures(1, &m_treeTexID);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_treeTexID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        //We load the texture with an alpha channel (RGBA)
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA8, treeTexture.getWidth(), 
                      treeTexture.getHeight(), GL_RGBA, GL_UNSIGNED_BYTE, 
                      treeTexture.getImageData());

        m_alphaTestProgram = auto_ptr<GLSLProgram>(
                                   new GLSLProgram("data/alphaTest.vert", 
                                                   "data/alphaTest.frag"));

        if (!m_alphaTestProgram->initialize()) 
        {
            std::cerr << "Could not initialize the shaders" << std::endl;
            return false;
        }

        m_alphaTestProgram->bindAttrib(0, "a_Vertex");
        m_alphaTestProgram->bindAttrib(1, "a_TexCoord");
        m_alphaTestProgram->linkProgram();

        initializeVBOs();
    }

    //If the texture and program have already been initialized
    //we don't do anything
    return true;
}

void Tree::render(glm::mat4 matrix)
{
    //glPushMatrix();
    //glTranslatef(x, y, z);
    float dArray[16] = {0.0};
    glm::mat4 pMat4 = matrix;
     pMat4 = glm::translate(pMat4, glm::vec3(x,y,z));
    //glGetFloatv(GL_MODELVIEW_MATRIX, modelviewMatrix);
    //glGetFloatv(GL_PROJECTION_MATRIX, projectionMatrix);
    
    const float *pSource = (const float*)glm::value_ptr(pMat4);
    
    for (int i = 0; i < 16; ++i)
    dArray[i] = pSource[i];
    
    float model[16] = { 1.0f,0.0f,0.0f,0.0f,0.0f,.906f,.422f,0.0f,0.0f,-.422f,.906f,0.0f,0.0f,1.13f,-45.0f,1.0f };
    float project[16] = {1.53,0,0,0,0,2.05,0,0,0,0,-1.02,-1,0,0,-2.02,0};
    
    m_alphaTestProgram->bindShader();
    m_alphaTestProgram->sendUniform4x4("modelview_matrix", dArray);
    m_alphaTestProgram->sendUniform4x4("projection_matrix", project);

    glBindTexture(GL_TEXTURE_2D, m_treeTexID);

    glDisable(GL_CULL_FACE);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glVertexAttribPointer((GLint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_texCoordBuffer);
    glVertexAttribPointer((GLint)1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);   
    glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);   

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    glEnable(GL_CULL_FACE);

    //glPopMatrix();
}
