#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "window.hpp"

blimp::Window::Window(std::string title, int width, int height) {
    this -> width = width;
    this -> height = height;
    this -> title = title;
}


void blimp::Window::run() {
    // initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);  // hide window initially

    GLFWwindow* window = glfwCreateWindow(this -> width, this -> height, this -> title.c_str(), nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    this -> window = window;

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
    }

    // set viewport
    glViewport(0, 0, this -> width, this -> height);

    this -> window = window;

    // use the default key callback
    this -> setKeyCallback(this, &defaultKeyCallback);

    while (!glfwWindowShouldClose(this -> window)) {
        glfwPollEvents();

        // clear the screen
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        this -> render(this -> scene, this -> camera);

        glfwSwapBuffers(this -> window);
    }

    glfwTerminate();
}

void blimp::Window::setKeyCallback(blimp::Window *t, GLFWkeyfun callback) {
    glfwSetKeyCallback(t -> window, callback);
}

void blimp::Window::setScene(Node* scene) {
    this -> scene = scene;
}

void blimp::Window::setCamera(Camera* camera) {
    this -> camera = camera;
}

GLuint blimp::Window::compileMaterial(Material* material) {
    // check if the program has already been compiled
    if (this -> programs[material] != 0) {
        return this -> programs[material];
    }

    GLuint vertexShader;
    GLuint fragmentShader;

    // try to compile the vertex shader
    const char* vertexShaderSource = material -> getVertexShader() -> c_str();
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, (GLchar* const*)(&vertexShaderSource), NULL);
    glCompileShader(vertexShader);

    // get compilation info
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << std::endl << "Error compiling vertex shader:" << std::endl << infoLog << std::endl;
        std::cout << "source: " << (*material -> getVertexShader()) << std::endl << std::endl;
        return 0;  // signal failure
    }

    // try to compile the fragment shader
    const char* fragmentShaderSource = material -> getFragmentShader() -> c_str();
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, (GLchar* const*)(&fragmentShaderSource), NULL);
    glCompileShader(fragmentShader);

    // get compilation info
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << std::endl << "Error compiling fragment shader:" << std::endl << infoLog << std::endl;
        std::cout << "source: " << (*material -> getFragmentShader()) << std::endl << std::endl;
        return 0;
    }

    // try to link program
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // get linking info
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "Error linking program:" << std::endl << infoLog << std::endl;
        return 0;
    }

    // delete the shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    this -> programs[material] = program;
    return program;
}

void blimp::Window::render(Node* scene, Camera* camera) {
    // sort the nodes in the scene by material
    // this may speed up the rendering process as it will reduce the number of glUseProgram calls needed
    MatNodeMap nodesByMaterial = this -> sortNodesByMaterial(scene);
    ProgramMap programs = ProgramMap();

    // prepare the scene
    for (MatNodePair pair: nodesByMaterial) {
        Material* material = pair.first;
        std::vector<Node*> nodes = pair.second;

        // compile the material's shaders
        GLuint program = this -> compileMaterial(material);
        programs[material] = program;
        // std::cout << "compiled program " << program << " for material " << material << std::endl;

        // prepare nodes
        for (Node* node: nodes) {
            // check if geometry is defined
            if (node -> getGeometry() == nullptr) {
                continue;
            }

            // get vertices
            Geometry* geometry = node -> getGeometry();
            GLfloat* vertices = geometry -> getVertices();
            GLfloat* colors = geometry -> getColors();
            int vertexCount = geometry -> getVertexCount();

            // create a VAO
            GLuint VAO;
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);

            // send the vertices to the GPU
            GLuint VBOPos, VBOCol;

            // position
            glGenBuffers(1, &VBOPos);
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, VBOPos);
            glBufferData(GL_ARRAY_BUFFER, vertexCount * 3 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

            // color
            glGenBuffers(1, &VBOCol);
            glEnableVertexAttribArray(1);
            glBindBuffer(GL_ARRAY_BUFFER, VBOCol);
            glBufferData(GL_ARRAY_BUFFER, vertexCount * 4 * sizeof(GLfloat), colors, GL_STATIC_DRAW);
            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);

            // unbind buffers
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);

            // set the program
            glUseProgram(program);

            // uniforms
            GLint uModelMatrix = glGetUniformLocation(program, "uModelMatrix");
            GLint uViewMatrix = glGetUniformLocation(program, "uViewMatrix");
            GLint uProjectionMatrix = glGetUniformLocation(program, "uProjectionMatrix");
            glUniformMatrix4fv(uModelMatrix, 1, GL_FALSE, glm::value_ptr(node -> getGlobalTransformationMatrix()));
            glUniformMatrix4fv(uViewMatrix, 1, GL_FALSE, glm::value_ptr(camera -> getViewMatrix()));
            glUniformMatrix4fv(uProjectionMatrix, 1, GL_FALSE, glm::value_ptr(camera -> getProjectionMatrix()));

            // render
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, vertexCount);
            glBindVertexArray(0);
        }
    }

}

MatNodeMap blimp::Window::sortNodesByMaterial(blimp::Node* root) {
    MatNodeMap nodesByMaterial = MatNodeMap();

    // get all the nodes in the scene
    std::vector<Node*> nodes = root -> traverseChildren();

    for (Node* node : nodes) {
        Material* material = node -> getMaterial();

        // if the material is not in the map, create a new vector
        if (nodesByMaterial.find(material) == nodesByMaterial.end()) {
            nodesByMaterial[material] = std::vector<Node*>();
        }

        // add the node to the vector of nodes with the same material
        nodesByMaterial[material].push_back(node);
    }

    return nodesByMaterial;
}

void blimp::Window::defaultKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        std::cout << "Closing window" << std::endl;
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}