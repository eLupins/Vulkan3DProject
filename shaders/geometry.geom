#version 450
layout (points) in;
layout (line_strip, max_vertices = 6) out;

void main() {    
    gl_Position = gl_in[0].gl_Position + vec4(-0.1, 1.0, 0.3, 0.5); 
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4( 6.1, -0.6, -20.2 , 300.0);
    EmitVertex();
    
    EndPrimitive();
}  