#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/string_cast.hpp>
#include "color.hpp"
#include "cubemap.hpp"
#include "material.hpp"
#include "texture2d.hpp"
#include "window.hpp"

blimp::Window::Window(std::string title, int width, int height) {
    this -> width = width;
    this -> height = height;
    this -> title = title;
    this -> setBackgroundColor(new blimp::Color(blimp::Color::TEAL));
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
    glfwWindowHint(GLFW_SAMPLES, 4);  // number of MSAA samples

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

    // register GLFW callbacks
    this -> setKeyCallback(this, &keyCallbackWrapper);
    this -> setFbSizeCallback(this, &fbSizeCallbackWrapper);
    this -> setMouseMoveCallback(this, &mouseMoveCallbackWrapper);

    // if the cursor lock was requested before, but has failed,
    // lock it now, when the window has been initialized
    if (this -> cursorLockRequested && !this -> cursorLocked) {
        this -> lockCursor();
    }

    // enable depth testing
    glEnable(GL_DEPTH_TEST);

    // enable multisampling
    glEnable(GL_MULTISAMPLE);

    // compile the shader program for the scene if it
    // uses a textured background
    if (this -> scene -> getTexture() != nullptr) {
        this -> compileSceneBackgroundProgram();
    }

    this -> lastFrameTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    while (!glfwWindowShouldClose(this -> window)) {
        glfwPollEvents();

        // clear the screen
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

void blimp::Window::setFbSizeCallback(blimp::Window *t, GLFWwindowsizefun callback) {
    glfwSetWindowUserPointer(t -> window, this);
    glfwSetWindowSizeCallback(t -> window, callback);
}

void blimp::Window::setMouseMoveCallback(blimp::Window *t, GLFWcursorposfun callback) {
    glfwSetWindowUserPointer(t -> window, this);
    glfwSetCursorPosCallback(t -> window, callback);
}

void blimp::Window::setTitle(std::string title) {
    this -> title = title;  //! @todo check if needed
    glfwSetWindowTitle(this -> window, this -> title.c_str());
}

void blimp::Window::setScene(Scene* scene) {
    this -> scene = scene;
}

void blimp::Window::setCamera(Camera* camera) {
    this -> camera = camera;
}

void blimp::Window::setBackgroundColor(Color* color) {
    this -> backgroundColor = color;
}

blimp::Color* blimp::Window::getBackgroundColor() {
    return this -> backgroundColor;
}

//! @todo maybe introduce a new class for scene shader programs
GLuint blimp::Window::compileSceneBackgroundProgram() {
    const GLchar* vertexShaderSource;
    const GLchar* fragmentShaderSource;

    if (scene -> getTexture() -> getTextureType() == Texture::TEXTURE_TYPE_2D) {
        vertexShaderSource = 
            "#version 330 core\n"
            "layout (location = 0) in vec3 aPosition;\n"
            "layout (location = 3) in vec2 aTexCoord;\n"
            "out vec2 vTexCoord;\n"
            "void main() {\n"
            "   gl_Position = vec4(aPosition, 1.0);\n"
            "   vTexCoord = aTexCoord;\n"
            "}\n";

        fragmentShaderSource =
            "#version 330 core\n"
            "in vec2 vTexCoord;\n"
            "out vec4 oColor;\n"
            "uniform sampler2D uTexture;\n"
            "void main() {\n"
            "   oColor = texture(uTexture, vec2(vTexCoord.x, 1.0f - vTexCoord.y));\n"
            "}\n";
    } else if (scene -> getTexture() -> getTextureType() == Texture::TEXTURE_TYPE_CUBEMAP) {
        vertexShaderSource = 
            "#version 330 core\n"
            "layout (location = 0) in vec3 aPosition;\n"
            "out vec3 vTexCoord;\n"
            "uniform mat4 uProjectionMatrix;\n"
            "uniform mat4 uViewMatrix;\n"
            "void main() {\n"
            "   gl_Position = uProjectionMatrix * uViewMatrix * vec4(aPosition, 1.0);\n"
            "   vTexCoord = aPosition;\n"
            "}\n";

        fragmentShaderSource =
            "#version 330 core\n"
            "in vec3 vTexCoord;\n"
            "out vec4 oColor;\n"
            "uniform samplerCube uTexture;\n"
            "void main() {\n"
            "   oColor = texture(uTexture, vTexCoord);\n"
            "}\n";
    }

    // compile shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // check for errors
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "Error compiling scene background vertex shader:" << std::endl << infoLog << std::endl;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "Error compiling scene background fragment shader:" << std::endl << infoLog << "hh" << std::endl;
    }

    // link shaders
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // check for errors
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cerr << "Error linking scene background shader program:" << std::endl << infoLog << std::endl;
    }

    // delete shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    this -> sceneProgram = program;
    return program;
}

void blimp::Window::drawSceneBackground() {
    // load and activate the texture
    GLuint texture = loadTexture(scene -> getTexture());
    glActiveTexture(GL_TEXTURE0 + texture);

    int textureType = scene -> getTexture() -> getTextureType();

    // load the program
    glUseProgram(this -> sceneProgram);

    // bind the texture depending on the type
    if (textureType == Texture::TEXTURE_TYPE_2D)
        glBindTexture(GL_TEXTURE_2D, texture);
    else if (textureType == Texture::TEXTURE_TYPE_CUBEMAP) {
        glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
    }
    
    // vertices for a fullscreen quad
    GLfloat vertices[] {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         1.0f,  1.0f, 0.0f,

        -1.0f, -1.0f, 0.0f,
         1.0f,  1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f
    };
    
    // texture coordinates for a fullscreen quad
    GLfloat texCoords[] {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,

        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
    };

    // vertices for a cube
    GLfloat cubeVertices[] {
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
  
        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
  
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
   
        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
  
        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,
  
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

    // create a VAO
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBOPos, VBOTex;

    // position
    glGenBuffers(1, &VBOPos);
    glBindBuffer(GL_ARRAY_BUFFER, VBOPos);
    if (textureType == Texture::TEXTURE_TYPE_2D) {
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    } else if (textureType == Texture::TEXTURE_TYPE_CUBEMAP) {
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
    }
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // texture coordinates
    glGenBuffers(1, &VBOTex);
    glEnableVertexAttribArray(3);
    glBindBuffer(GL_ARRAY_BUFFER, VBOTex);
    if (textureType == Texture::TEXTURE_TYPE_2D) {
        glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    }

    // unbind buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // set texture
    glUniform1i(glGetUniformLocation(this -> sceneProgram, "uTexture"), texture);

    // if we are drawing a skybox, also
    // set the view and projection matrices
    if (textureType == Texture::TEXTURE_TYPE_CUBEMAP) {
        GLint uViewMatrix = glGetUniformLocation(this -> sceneProgram, "uViewMatrix");
        GLint uProjectionMatrix = glGetUniformLocation(this -> sceneProgram, "uProjectionMatrix");

        // remove the translatoin components from the view matrix
        // so that the skybox doesn't move when the camera does.
        glm::mat4 viewMatrix = glm::mat4(glm::mat3(this -> camera -> getViewMatrix()));

        glUniformMatrix4fv(uViewMatrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));
        glUniformMatrix4fv(uProjectionMatrix, 1, GL_FALSE, glm::value_ptr(this -> camera -> getProjectionMatrix()));
    }

    // render
    glDisable(GL_DEPTH_TEST);  // even though the background will be drawn on Z = 0, it won't occlude distant objects
    glUseProgram(this -> sceneProgram);
    glBindVertexArray(VAO);
    if (textureType == Texture::TEXTURE_TYPE_2D) {
        glDrawArrays(GL_TRIANGLES, 0, 6);
    } else if (textureType == Texture::TEXTURE_TYPE_CUBEMAP) {
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    glBindVertexArray(0);
    glEnable(GL_DEPTH_TEST);
    
    // free
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBOPos);
    glDeleteBuffers(1, &VBOTex);
}

GLuint blimp::Window::compileMaterial(Material* material) {
    // check if the program has already been compiled
    if (this -> programs[material] != 0) {
        return this -> programs[material];
    }

    GLuint vertexShader;
    GLuint fragmentShader;

    // try to compile the vertex shader
    const char* vertexShaderSource = material -> getVertexShader() -> generateSource() -> c_str();
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, (GLchar* const*)(&vertexShaderSource), NULL);
    glCompileShader(vertexShader);

    // get compilation info
    //! @todo always get info log to account for the possibility of warnings
    GLint success;
    GLchar infoLog[10000];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertexShader, 10000, NULL, infoLog);
        std::cout << std::endl << "Error compiling vertex shader:" << std::endl << infoLog << std::endl;
        std::cout << "source:\n" << (*material -> getVertexShader() -> generateSource()) << std::endl << std::endl;
        return 0;  // signal failure
    }

    // try to compile the fragment shader
    const char* fragmentShaderSource = material -> getFragmentShader() -> generateSource() -> c_str();
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, (GLchar* const*)(&fragmentShaderSource), NULL);
    glCompileShader(fragmentShader);

    // get compilation info
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragmentShader, 10000, NULL, infoLog);
        std::cout << std::endl << "Error compiling fragment shader:" << std::endl << infoLog << std::endl;
        std::cout << "source:\n" << (*material -> getFragmentShader() -> generateSource()) << std::endl << std::endl;
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
    // *material -> getVertexShader() = "";
    // *material -> getFragmentShader() = "";

    this -> programs[material] = program;

    return program;
}

GLuint blimp::Window::loadTexture(blimp::Texture* texture) {
    // if a texture has already been loaded, return its texture unit
    if (this -> textures[texture] != 0) {
        return this -> textures[texture];
    }

    GLuint texUnit;

    if (texture -> getTextureType() == Texture::TEXTURE_TYPE_2D) {
        Texture2D* texture2D = (Texture2D*) texture;

        glGenTextures(1, &texUnit);
        glBindTexture(GL_TEXTURE_2D, texUnit);

        //! @todo make these configurable via TextureOptions
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            texture2D -> getWidth(),
            texture2D -> getHeight(),
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            texture2D -> getData()    
        );

        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    } else if (texture -> getTextureType() == Texture::TEXTURE_TYPE_CUBEMAP) {
        Cubemap* cubemap = (Cubemap*) texture;

        glGenTextures(1, &texUnit);
        glBindTexture(GL_TEXTURE_CUBE_MAP, texUnit);

        // retrieve the faces
        Texture2D* faces[6] = {
            cubemap -> getPX(),
            cubemap -> getNX(),
            cubemap -> getPY(),
            cubemap -> getNY(),
            cubemap -> getPZ(),
            cubemap -> getNZ()
        };

        for (GLuint i = 0; i < 6; i++) {
            glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0,
                GL_RGBA,
                faces[i] -> getWidth(),
                faces[i] -> getHeight(),
                0,
                GL_RGBA,
                GL_UNSIGNED_BYTE,
                faces[i] -> getData()
            );
        }

        //! @todo make these configurable via TextureOptions
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }

    this -> textures[texture] = texUnit;
    return texUnit;
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

void blimp::Window::render(Scene* scene, Camera* camera) {
    // draw background if defined by the scene
    // (default to black)
    //! @todo allow color backgrounds
    //! @todo only do this once per scene background change, not on every render
    if (scene -> getTexture() == nullptr) {
        // get the background color
        Color* c = this -> getBackgroundColor();
        glClearColor(c -> getR(), c -> getG(), c -> getB(), 1.0f);
    } else {
        this -> drawSceneBackground();
    }

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
            // camera position
            GLint uCameraPos = glGetUniformLocation(program, "uCameraPos");
            if (uCameraPos != -1) {
                glUniform3f(
                    uCameraPos,
                    camera -> getTranslation().x,
                    camera -> getTranslation().y,
                    camera -> getTranslation().z
                );
            }

            // material shininess
            GLint uMatShininess = glGetUniformLocation(program, "uMatShininess");
            if (uMatShininess != -1) {
                glUniform1f(
                    uMatShininess,
                    material -> getShininess()
                );
            }

            // material specular
            GLint uMatSpecular = glGetUniformLocation(program, "uMatSpecular");
            if (uMatSpecular != -1) {
                glUniform1f(
                    uMatSpecular,
                    material -> getSpecular()
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
            GLfloat* texCoords = geometry -> getTexCoords();
            int vertexCount = geometry -> getVertexCount();

            // create a VAO
            GLuint VAO;
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);

            // send the vertices to the GPU
            GLuint VBOPos, VBOCol, VBONorm, VBOTex;

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

            // texture coordinates
            glGenBuffers(1, &VBOTex);
            glEnableVertexAttribArray(3);
            glBindBuffer(GL_ARRAY_BUFFER, VBOTex);
            glBufferData(GL_ARRAY_BUFFER, vertexCount * 2 * sizeof(GLfloat), texCoords, GL_STATIC_DRAW);
            glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);

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

            if (mesh -> getTexture() != nullptr) {
                //! @todo use multiple texture units for different textures (to speed up rendering etc.)
                GLuint texture = loadTexture(mesh -> getTexture());

                glUniform1i(glGetUniformLocation(program, "uTexture"), texture);
                glUniform1i(glGetUniformLocation(program, "uUseTexture"), 1);
                glUniform1f(glGetUniformLocation(program, "uTextureScaleS"), mesh -> getTextureOptions() -> getScaleS());
                glUniform1f(glGetUniformLocation(program, "uTextureScaleT"), mesh -> getTextureOptions() -> getScaleT());
                glActiveTexture(GL_TEXTURE0 + texture);
                glBindTexture(GL_TEXTURE_2D, texture);

                // set texture parameters
                //! @todo set only if not not setting the same/default values
                glTexParameteri(
                    GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S,
                    mesh -> getTextureOptions() -> getWrapModeS()
                );

                glTexParameteri(
                    GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T,
                    mesh -> getTextureOptions() -> getWrapModeT()
                );

                glTexParameteri(
                    GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER,
                    mesh -> getTextureOptions() -> getMinFilterMode()
                );

                glTexParameteri(
                    GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER,
                    mesh -> getTextureOptions() -> getMagFilterMode()
                );

            } else {
                glUniform1i(glGetUniformLocation(program, "uUseTexture"), 0);
            }

            // render
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, vertexCount);
            glBindVertexArray(0);

            // delete buffers
            glDeleteBuffers(1, &VBOPos);
            glDeleteBuffers(1, &VBOCol);
            glDeleteBuffers(1, &VBONorm);
            glDeleteBuffers(1, &VBOTex);
            glDeleteVertexArrays(1, &VAO);
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

void blimp::Window::updateViewport() {
    glViewport(0, 0, this -> width, this -> height);
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

void blimp::Window::fbSizeCallbackWrapper(GLFWwindow* window, int width, int height) {
    blimp::Window* win = (blimp::Window*) glfwGetWindowUserPointer(window); 
    win -> fbSizeCallback(width, height);
}

void blimp::Window::fbSizeCallback(int width, int height) {

    if (width != 0 && height != 0) {
        this -> width = width;
        this -> height = height;
    }
    
    this -> updateViewport();
}

void blimp::Window::mouseMoveCallbackWrapper(GLFWwindow* window, double xPos, double yPos) {
    blimp::Window* win = (blimp::Window*) glfwGetWindowUserPointer(window); 
    win -> mouseMoveCallback(xPos, yPos);
}

void blimp::Window::mouseMoveCallback(double xPos, double yPos) {
    // the default cursor position callback will do nothing
}

void blimp::Window::lockCursor() {
    this -> cursorLockRequested = true;

    // try to lock the cursor immediately,
    // if it fails, presume that the window is not yet initialized
    // and that the initialization routine will handle the locking request later
    if (this -> window == NULL) {
        return;
    }

    glfwSetInputMode(this -> window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    this -> cursorLocked = true;
}

void blimp::Window::unlockCursor() {
    this -> cursorLockRequested = false;

    if (this -> window == NULL) {
        return;
    }

    glfwSetInputMode(this -> window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    this -> cursorLocked = false;
}

void blimp::Window::toggleCursorLock() {
    if (this -> cursorLocked) {
        this -> unlockCursor();
    } else {
        this -> lockCursor();
    }
}

void blimp::Window::enableWireframeMode() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    this -> wireframeMode = true;
}

void blimp::Window::disableWireframeMode() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    this -> wireframeMode = false;
}

void blimp::Window::toggleWireframeMode() {
    if (this -> wireframeMode) {
        this -> disableWireframeMode();
    } else {
        this -> enableWireframeMode();
    }
}

void blimp::Window::init() {
    // enable OpenGL debugging
    // glEnable(GL_DEBUG_OUTPUT);
    // glDebugMessageCallback(&this -> openGLMessageCallback, 0);
}

void blimp::Window::update() {
    
}

float blimp::Window::getFPS(float smoothingFactor) {
    // calculate FPS by smoothing
    float smoothedFPS = (this -> previousFramesPerSecond * smoothingFactor) + (this -> currentFramesPerSecond * (1 - smoothingFactor));
    return smoothedFPS;
}

// for debugging OpenGL errors
void GLAPIENTRY blimp::Window::openGLMessageCallback(
    GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam
) {
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
        ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
        type, severity, message );
}