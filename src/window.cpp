#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/string_cast.hpp>
#include "window.hpp"

blimp::Window::Window(std::string title, int width, int height) {
    this -> width = width;
    this -> height = height;
    this -> title = title;
}

void blimp::Window::run() {
    init();

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
    // glfwSetWindowUserPointer(window, this);

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

    // register key callback
    this -> setKeyCallback(this, &keyCallbackWrapper);

    // enable depth testing
    glEnable(GL_DEPTH_TEST);

    this -> lastFrameTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    while (!glfwWindowShouldClose(this -> window)) {
        glfwPollEvents();

        // clear the screen
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        this -> update();
        this -> render(this -> scene, this -> camera);

        uint64_t now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        float previousFPS = this -> previousFramesPerSecond;  // the value stored from before
        float currentFPS;  // the FPS that will be calculated from the last render

        if (now - this -> lastFrameTime == 0) {
            currentFPS = previousFPS;
        } else {
            currentFPS = 1000.0f / (now - this -> lastFrameTime);
        }

        this -> previousFramesPerSecond = this -> currentFramesPerSecond;
        this -> currentFramesPerSecond = currentFPS;
        this -> lastFrameTime = now;

        glfwSwapBuffers(this -> window);
    }

    glfwTerminate();
}

void blimp::Window::close() {
    glfwSetWindowShouldClose(this -> window, true);
}

void blimp::Window::setKeyCallback(blimp::Window *t, GLFWkeyfun callback) {
    glfwSetWindowUserPointer(t -> window, this);
    glfwSetKeyCallback(t -> window, callback);
}

void blimp::Window::setTitle(std::string title) {
    this -> title = title;  //!< @todo check if needed
    glfwSetWindowTitle(this -> window, this -> title.c_str());
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
    //! @todo always get info log to account for the possibility of warnings
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
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
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
    *material -> getVertexShader() = "";
    *material -> getFragmentShader() = "";

    this -> programs[material] = program;

    return program;
}

blimp::LightsData blimp::Window::getLights(std::vector<Node*>* nodes) {
    ALights aLights = ALights();
    DLights dLights = DLights();
    PLights pLights = PLights();
    SLights sLights = SLights();

    for (Node* node: *nodes) {
        int nodeType = node -> getNodeType();

        if (nodeType == Node::NODE_TYPE_AMBIENT_LIGHT) {
            aLights.push_back((AmbientLight*) node);
        } else if (nodeType == Node::NODE_TYPE_DIRECTIONAL_LIGHT) {
            dLights.push_back((DirectionalLight*) node);
        } else if (nodeType == Node::NODE_TYPE_POINT_LIGHT) {
            pLights.push_back((PointLight*) node);
        } else if (nodeType == Node::NODE_TYPE_SPOT_LIGHT) {
            sLights.push_back((SpotLight*) node);
        } 
    }

    return LightsData(aLights, dLights, pLights, sLights);
}

void blimp::Window::render(Node* scene, Camera* camera) {
    // retrieve all nodes in the scene
    std::vector<Node*> nodes = scene -> traverseChildren();

    // sort the meshes in the scene by material
    // this may speed up the rendering process as it will reduce the number of glUseProgram calls needed
    MatMeshMap meshesByMaterial = this -> groupMeshesByMaterial(&nodes);
    ProgramMap programs = ProgramMap();

    // get all lights in the scene
    LightsData lightsData = this -> getLights(&nodes);

    // prepare the scene
    for (MatMeshPair pair: meshesByMaterial) {
        Material* material = pair.first;
        std::vector<Mesh*> meshes = pair.second;

        // compile the material's shaders
        GLuint program = this -> compileMaterial(material);

        // if compilation/linking failed, exit
        if (program == 0) {
            exit(0);
        }

        programs[material] = program;

        // set the program
        glUseProgram(program);

        // lights
        if (material -> usesLights()) {
            // uniform locations
            GLint uNumALights = glGetUniformLocation(program, "uNumALights");
            GLint uNumDLights = glGetUniformLocation(program, "uNumDLights");
            GLint uNumPLights = glGetUniformLocation(program, "uNumPLights");
            GLint uNumSLights = glGetUniformLocation(program, "uNumSLights");
            int nALights = lightsData.countAmbientLights();
            int nDLights = lightsData.countDirectionalLights();
            int nPLights = lightsData.countPointLights();
            int nSLights = lightsData.countSpotLights();
            glUniform1i(uNumALights, nALights);
            glUniform1i(uNumDLights, nDLights);
            glUniform1i(uNumPLights, nPLights);
            glUniform1i(uNumSLights, nSLights);

            GLint uALights = glGetUniformLocation(program, "uALights");
            GLint uDLights = glGetUniformLocation(program, "uDLights");
            GLint uPLights = glGetUniformLocation(program, "uPLights");
            GLint uSLights = glGetUniformLocation(program, "uSLights");

            // ambient lights (should only be one in the scene though)
            ALights* aLights = lightsData.getAmbientLights();
            for (int i = 0; i < nALights; i++) {
                AmbientLight* light = aLights -> at(i);
                Color* lightColor = light -> getColor();
                float lightIntensity = light -> getIntensity();

                GLint uALightsIColor = glGetUniformLocation(program, std::string("uALights[" + std::to_string(i) + "].color").c_str());
                GLint uALightsIIntensity = glGetUniformLocation(program, std::string("uALights[" + std::to_string(i) + "].intensity").c_str());

                // set uniforms
                glUniform3f(
                    uALightsIColor,
                    lightColor -> getR(),
                    lightColor -> getG(),
                    lightColor -> getB()
                );
                glUniform1f(
                    uALightsIIntensity,
                    lightIntensity
                );
            }

            // directional lights
            DLights* dLights = lightsData.getDirectionalLights();
            for (int i = 0; i < nDLights; i++) {
                DirectionalLight* light = dLights -> at(i);
                Color* lightColor = light -> getColor();
                glm::vec3 lightPos = glm::vec3(light -> getGlobalTransformationMatrix()[3]);
                float lightIntensity = light -> getIntensity();
                
                GLint uDLightsIColor = glGetUniformLocation(program, std::string("uDLights[" + std::to_string(i) + "].color").c_str());
                GLint uDLightsIPosition = glGetUniformLocation(program, std::string("uDLights[" + std::to_string(i) + "].position").c_str());
                GLint uDLightsIIntensity = glGetUniformLocation(program, std::string("uDLights[" + std::to_string(i) + "].intensity").c_str());

                // set uniforms
                glUniform3f(
                    uDLightsIColor,
                    lightColor -> getR(),
                    lightColor -> getG(),
                    lightColor -> getB()
                );
                glUniform3f(
                    uDLightsIPosition,
                    lightPos.x,
                    lightPos.y,
                    lightPos.z
                );
                glUniform1f(
                    uDLightsIIntensity,
                    lightIntensity
                );
            }

            // point lights
            PLights* pLights = lightsData.getPointLights();
            for (int i = 0; i < nPLights; i++) {
                PointLight* light = pLights -> at(i);
                Color* lightColor = light -> getColor();
                glm::vec3 lightPos = glm::vec3(light -> getGlobalTransformationMatrix()[3]);
                float lightIntensity = light -> getIntensity();
                float lightAttenuation = light -> getAttenuation();

                GLint uPLightsIColor = glGetUniformLocation(program, std::string("uPLights[" + std::to_string(i) + "].color").c_str());
                GLint uPLightsIPosition = glGetUniformLocation(program, std::string("uPLights[" + std::to_string(i) + "].position").c_str());
                GLint uPLightsIIntensity = glGetUniformLocation(program, std::string("uPLights[" + std::to_string(i) + "].intensity").c_str());
                GLint uPLightsIAttenuation = glGetUniformLocation(program, std::string("uPLights[" + std::to_string(i) + "].attenuation").c_str());

                // set uniforms
                glUniform3f(
                    uPLightsIColor,
                    lightColor -> getR(),
                    lightColor -> getG(),
                    lightColor -> getB()
                );
                glUniform3f(
                    uPLightsIPosition,
                    lightPos.x,
                    lightPos.y,
                    lightPos.z
                );
                glUniform1f(
                    uPLightsIIntensity,
                    lightIntensity
                );
                glUniform1f(
                    uPLightsIAttenuation,
                    lightAttenuation
                );
            }

            // spot lights
            SLights* sLights = lightsData.getSpotLights();
            for (int i = 0; i < nSLights; i++) {
                SpotLight* light = sLights -> at(i);
                Color* lightColor = light -> getColor();
                glm::vec3 lightPos = glm::vec3(light -> getGlobalTransformationMatrix()[3]);
                glm::vec3 lightDir = light -> getForwardDirection();
                float lightIntensity = light -> getIntensity();
                float inner = light -> getInnerCutoff();
                float outer = light -> getOuterCutoff();

                GLint uSLightsIColor = glGetUniformLocation(program, std::string("uSLights[" + std::to_string(i) + "].color").c_str());
                GLint uSLightsIPosition = glGetUniformLocation(program, std::string("uSLights[" + std::to_string(i) + "].position").c_str());
                GLint uSLightsIDirection = glGetUniformLocation(program, std::string("uSLights[" + std::to_string(i) + "].direction").c_str());
                GLint uSLightsIIntensity = glGetUniformLocation(program, std::string("uSLights[" + std::to_string(i) + "].intensity").c_str());
                GLint uSLightsIInner = glGetUniformLocation(program, std::string("uSLights[" + std::to_string(i) + "].inner").c_str());
                GLint uSLightsIOuter = glGetUniformLocation(program, std::string("uSLights[" + std::to_string(i) + "].outer").c_str());

                // set uniforms
                glUniform3f(
                    uSLightsIColor,
                    lightColor -> getR(),
                    lightColor -> getG(),
                    lightColor -> getB()
                );
                glUniform3f(
                    uSLightsIPosition,
                    lightPos.x,
                    lightPos.y,
                    lightPos.z
                );
                glUniform3f(
                    uSLightsIDirection,
                    lightDir.x,
                    lightDir.y,
                    lightDir.z
                );
                glUniform1f(
                    uSLightsIIntensity,
                    lightIntensity
                );
                glUniform1f(
                    uSLightsIInner,
                    inner
                );
                glUniform1f(
                    uSLightsIOuter,
                    outer
                );
            }

            // other lighting-related uniforms
            GLint uCameraPos = glGetUniformLocation(program, "uCameraPos");
            if (uCameraPos != -1) {
                glUniform3f(
                    uCameraPos,
                    camera -> getTranslation().x,
                    camera -> getTranslation().y,
                    camera -> getTranslation().z
                );
            }
        }

        // prepare meshes
        for (Mesh* mesh: meshes) {
            // check if geometry is defined
            // if (mesh -> getGeometry() == nullptr) {
            //     continue;
            // }

            // get vertices
            Geometry* geometry = mesh -> getGeometry();
            GLfloat* vertices = geometry -> getVertices();
            GLfloat* colors = geometry -> getColors();
            GLfloat* normals = geometry -> getNormals();
            int vertexCount = geometry -> getVertexCount();

            // create a VAO
            GLuint VAO;
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);

            // send the vertices to the GPU
            GLuint VBOPos, VBOCol, VBONorm;

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

            // normals
            glGenBuffers(1, &VBONorm);
            glEnableVertexAttribArray(2);
            glBindBuffer(GL_ARRAY_BUFFER, VBONorm);
            glBufferData(GL_ARRAY_BUFFER, vertexCount * 3 * sizeof(GLfloat), normals, GL_STATIC_DRAW);
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

            // unbind buffers
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);


            // uniforms
            GLint uModelMatrix = glGetUniformLocation(program, "uModelMatrix");
            GLint uViewMatrix = glGetUniformLocation(program, "uViewMatrix");
            GLint uProjectionMatrix = glGetUniformLocation(program, "uProjectionMatrix");
            glUniformMatrix4fv(uModelMatrix, 1, GL_FALSE, glm::value_ptr(mesh -> getGlobalTransformationMatrix()));
            glUniformMatrix4fv(uViewMatrix, 1, GL_FALSE, glm::value_ptr(camera -> getViewMatrix()));
            glUniformMatrix4fv(uProjectionMatrix, 1, GL_FALSE, glm::value_ptr(camera -> getProjectionMatrix()));

            // render
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, vertexCount);
            glBindVertexArray(0);
        }
    }

}

MatMeshMap blimp::Window::groupMeshesByMaterial(std::vector<Node*>* nodes) {
    MatMeshMap meshesByMaterial = MatMeshMap();

    for (Node* node : *nodes) {
        // skip if the current node is not a mesh
        if (node -> getNodeType() != Node::NODE_TYPE_MESH) {
            continue;
        }

        Mesh* mesh = (Mesh*) node;
        Material* material = mesh -> getMaterial();

        // if the material is not in the map, create a new vector
        if (meshesByMaterial.find(material) == meshesByMaterial.end()) {
            meshesByMaterial[material] = std::vector<Mesh*>();
        }

        // add the node to the vector of nodes with the same material
        meshesByMaterial[material].push_back(mesh);
    }

    return meshesByMaterial;
}

void blimp::Window::keyCallbackWrapper(GLFWwindow* window, int key, int scancode, int action, int mode) {
    blimp::Window* win = (blimp::Window*) glfwGetWindowUserPointer(window); 
    win -> keyCallback(key, scancode, action, mode);
}

void blimp::Window::keyCallback(int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        std::cout << "Closing window" << std::endl;
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

void blimp::Window::init() {

}

void blimp::Window::update() {
    
}

float blimp::Window::getFPS(float smoothingFactor) {
    // calculate FPS by smoothing
    float smoothedFPS = (this -> previousFramesPerSecond * smoothingFactor) + (this -> currentFramesPerSecond * (1 - smoothingFactor));
    return smoothedFPS;
}