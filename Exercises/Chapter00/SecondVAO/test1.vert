#version 410

layout(location = 0) in vec3 lower_triangle_vertices;

void main () {
    gl_Position = vec4(lower_triangle_vertices, 1.0);
}
