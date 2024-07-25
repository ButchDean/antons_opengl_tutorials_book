#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string.h>

const char* shaderfns[] = {
  "test1.frag",
  "test1.vert",
  "test2.frag",
  "test2.vert"
};

struct fileptr {
  FILE* fsfptr, *vsfptr;
} sdrfileptrs[2];

int main() {
  GLFWwindow* window = NULL;
  const GLubyte* renderer;
  const GLubyte* version;
  GLuint vao1, vao2;
  GLuint vbo1, vbo2;
  const int READ_SIZE = 500;

  sdrfileptrs[0].fsfptr = fopen(shaderfns[0], "r");
  sdrfileptrs[0].vsfptr = fopen(shaderfns[1], "r");
  sdrfileptrs[1].fsfptr = fopen(shaderfns[2], "r");
  sdrfileptrs[1].vsfptr = fopen(shaderfns[3], "r");

  /* Geometry for each triangle making up the quad. */
  GLfloat points0[9] = {-0.5f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f};
  GLfloat points1[9] = {0.5f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, 0.5f, 0.0f};

  char vertex_shader[2][READ_SIZE];
  char fragment_shader[2][READ_SIZE];

  for(int i = 0; i < 2; i++) {
    memset(vertex_shader[i], '\0', READ_SIZE);
    memset(fragment_shader[i], '\0', READ_SIZE);
  }

  while(!feof(sdrfileptrs[0].fsfptr))
    fread(fragment_shader[0], READ_SIZE, 1, sdrfileptrs[0].fsfptr);

  while(!feof(sdrfileptrs[0].vsfptr))
    fread(vertex_shader[0], READ_SIZE, 1, sdrfileptrs[0].vsfptr);

  fclose(sdrfileptrs[0].fsfptr);
  fclose(sdrfileptrs[0].vsfptr);
  fclose(sdrfileptrs[1].fsfptr);
  fclose(sdrfileptrs[1].vsfptr);

  const char* pvertex_shader = vertex_shader[0];
  const char* pfragment_shader = fragment_shader[0];

  printf("%s", pfragment_shader);
  printf("%s", pvertex_shader);

  GLuint vert_shader[2], frag_shader[2];
  GLuint shader_programme[2];

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

  /* First VAO */
  glGenVertexArrays(1, &vao1);
  glBindVertexArray(vao1);
  glBindBuffer(GL_ARRAY_BUFFER, vbo1);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  glEnableVertexAttribArray(0);

  /* Second VAO */
  glGenVertexArrays(1, &vao2);
  glBindVertexArray(vao2);
  glBindBuffer(GL_ARRAY_BUFFER, vbo2);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  glEnableVertexAttribArray(1);

  /* First vertex shader */
  vert_shader[0] = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vert_shader[0], 1, &pvertex_shader, NULL);
  glCompileShader(vert_shader[0]);
  frag_shader[0] = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(frag_shader[0], 1, &pfragment_shader, NULL);
  glCompileShader(frag_shader[0]);
  shader_programme[0] = glCreateProgram();
  glAttachShader(shader_programme[0], frag_shader[0]);
  glAttachShader(shader_programme[0], vert_shader[0]);
  glLinkProgram(shader_programme[0]);

   /* Second vertex shader */
/*  vert_shader[1] = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vert_shader[1], 1, &pvertex_shader1, NULL);
  glCompileShader(vert_shader[1]);
  frag_shader[1] = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(frag_shader[1], 1, &pfragment_shader1, NULL);
  glCompileShader(frag_shader[1]);
  shader_programme[1] = glCreateProgram();
  glAttachShader(shader_programme[1], frag_shader[1]);
  glAttachShader(shader_programme[1], vert_shader[1]);
  glLinkProgram(shader_programme[1]); */

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.6f, 0.6f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shader_programme[0]);
    glBindVertexArray(vao1);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    //glBindVertexArray(vao2);
    //glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  glfwTerminate();
  return 0;
}
