#ifndef BOGLGP_TREE_H
#define BOGLGP_TREE_H

#include <string>
#include <vector>
#include <memory>

#include <GL/glew.h>
//#include "glee/GLee.h"

//for matrix calculation
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

using std::string;
using std::vector;
using std::auto_ptr;

class GLSLProgram;

class Tree {
private:
    static auto_ptr<GLSLProgram> m_alphaTestProgram;
    static GLuint m_treeTexID;

    static GLuint m_vertexBuffer;
    static GLuint m_texCoordBuffer;

    float modelviewMatrix[16];
    float projectionMatrix[16];
    vector<float> normalMatrix;

    static void initializeVBOs();

    float x, y, z;

public:
    Tree(float x, float y, float z);
    Tree(const Tree& t) {
        x = t.x;
        y = t.y;
        z = t.z;
    }

    Tree& operator=(const Tree& t) {
        x = t.x;
        y = t.y;
        z = t.z;

        return *this;
    }

    static bool initialize();
    void render(glm::mat4 matrix);
    
};

#endif
