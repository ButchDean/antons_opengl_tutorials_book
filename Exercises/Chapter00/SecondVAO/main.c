/******************************************************************************\
| OpenGL 4 Example Code.                                                       |
| Accompanies written series "Anton's OpenGL 4 Tutorials"                      |
| Email: anton at antongerdelan dot net                                        |
| First version 27 Jan 2014                                                    |
| Dr Anton Gerdelan, Trinity College Dublin, Ireland.                          |
| See individual libraries for separate legal notices                          |
|******************************************************************************|
| "Hello Triangle". Just the basics.                                           |
| If you're on Apple un-comment the version number code at the beginning. It   |
| will give you the latest, even if you say 3.2!                               |
| This uses the libraries GLEW and GLFW3 to start GL. Download and compile     |
| these first. Linking them might be a pain, but you'll need to master this.   |
\******************************************************************************/

#include <GL/glew.h>    /* include GLEW and new version of GL on Windows */
#include <GLFW/glfw3.h> /* GLFW helper library */
#include <stdio.h>

int main() {
  GLFWwindow* window = NULL;
  const GLubyte* renderer;
  const GLubyte* version;
  GLuint vao1, vao2;
  GLuint vbo1, vbo2;
  FILE* fsfptr, *vsfptr;
  const int READ_SIZE = 500;

  fsfptr = fopen("test.frag", "r");
  vsfptr = fopen("test.vert", "r");

  /* geometry to use. these are 3 xyz points (9 floats total) to make a triangle */
  GLfloat points0[9] = {-0.5f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f};
  GLfloat points1[9] = {0.5f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, 0.5f, 0.0f};

  /* these are the strings of code for the shaders
  the vertex shader positions each vertex point */
  char vertex_shader[READ_SIZE];

  /* the fragment shader colours each fragment (pixel-sized area of the
  triangle) */
  char fragment_shader[READ_SIZE];

  while(!feof(fsfptr))
    fread(fragment_shader, READ_SIZE, 1, fsfptr);

  while(!feof(vsfptr))
    fread(vertex_shader, READ_SIZE, 1, vsfptr);

  fclose(fsfptr);
  fclose(vsfptr);

  /* fragment_shader[READ_SIZE - 1] = 0;
  vertex_shader[READ_SIZE - 1] = 0; */

  const char* pvertex_shader = vertex_shader;
  const char* pfragment_shader = fragment_shader;

  printf("%s", pfragment_shader);
  printf("%s", pvertex_shader);

  /* GL shader objects for vertex and fragment shader [components] */
  GLuint vert_shader, frag_shader;
  /* GL shader programme object [combined, to link] */
  GLuint shader_programme;

  /* start GL context and O/S window using the GLFW helper library */
  if (!glfwInit()) {
    fprintf(stderr, "ERROR: could not start GLFW3\n");
    return 1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(640, 480, "Hello Quad (Second VAO)", NULL, NULL);
  if (!window) {
    fprintf(stderr, "ERROR: could not open window with GLFW3\n");
    glfwTerminate();
    return 1;
  }
  glfwMakeContextCurrent(window);

  glewExperimental = GL_TRUE;
  glewInit();


  renderer = glGetString(GL_RENDERER); /* get renderer string */
  version  = glGetString(GL_VERSION);  /* version as a string */
  printf("Renderer: %s\n", renderer);
  printf("OpenGL version supported %s\n", version);

  glEnable(GL_DEPTH_TEST); /* enable depth-testing */

  glDepthFunc(GL_LESS);

  glGenBuffers(1, &vbo1);
  glBindBuffer(GL_ARRAY_BUFFER, vbo1);
  glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), points0, GL_STATIC_DRAW);

  glGenBuffers(1, &vbo2);
  glBindBuffer(GL_ARRAY_BUFFER, vbo2);
  glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), points1, GL_STATIC_DRAW);

  glGenVertexArrays(1, &vao1);
  glBindVertexArray(vao1);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vbo1);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

  /* Second VAO */
  glGenVertexArrays(1, &vao2);
  glBindVertexArray(vao2);
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, vbo2);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

  vert_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vert_shader, 1, &pvertex_shader, NULL);
  glCompileShader(vert_shader);
  frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(frag_shader, 1, &pfragment_shader, NULL);
  glCompileShader(frag_shader);
  shader_programme = glCreateProgram();
  glAttachShader(shader_programme, frag_shader);
  glAttachShader(shader_programme, vert_shader);
  glLinkProgram(shader_programme);

  while (!glfwWindowShouldClose(window)) {
    
    glClearColor(0.6f, 0.6f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shader_programme);
    glBindVertexArray(vao1);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(vao2);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  glfwTerminate();
  return 0;
}
