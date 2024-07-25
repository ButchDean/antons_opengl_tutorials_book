#version 410

layout(location = 1) in vec3 upper_triangle_vertices;

void main () {
    gl_Position = vec4(upper_triangle_vertices, 1.0);
}
