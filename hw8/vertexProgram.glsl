uniform float t;
uniform float mode;
const float pi = 3.1415926535;

varying float u, v;
varying float vertexX;
varying float vertexY;

void main()
{
    // Convert from the [-5,5]x[-5,5] range provided into radians
    // between 0 and 2*theta
    // convert the coordinates such that u and v are between 0 and 2pi
    u = (gl_Vertex.x + 5.0) / 10.0 * 2.0 * pi;
    v = (gl_Vertex.y + 5.0) / 10.0 * 2.0 * pi;

    // Height for waves: Let f(x,y) = cos(x^2 + y^2 + 5t)
    float height = cos(gl_Vertex.x * gl_Vertex.x + gl_Vertex.y * gl_Vertex.y + 5.0*t);
    gl_Position = gl_ModelViewProjectionMatrix * vec4(gl_Vertex.x, 0.1 * height,gl_Vertex.y,1.0);
    
    vertexX = gl_Vertex.x;
    vertexY = gl_Vertex.y;

    // Then, Dx = 2xsin(x^2 + y^2 + 5t)
    // and , Dy = 2ysin(x^2 + y^2 + 5t)
    float sinTerm = 0.1 * sin(gl_Vertex.x * gl_Vertex.x + gl_Vertex.y * gl_Vertex.y + 5.0 * t);
    float normX = 2.0 * gl_Vertex.x * sinTerm;
    float normY = 2.0 * gl_Vertex.y * sinTerm;
    
    // normalize the normal, and map to [0,1]
    float normalizedNormX = normX/(normX*normX + normY*normY + 1.0);
    float normalizedNormY = normY/(normX*normX + normY*normY + 1.0);

    // modify GL_TexCoord[0] (for sky) such that the texture coord is the normal, 
    // to simulate the water being reflected
    gl_TexCoord[0].s = (normalizedNormX + 1.0)/2.0;
    gl_TexCoord[0].t = (normalizedNormY + 1.0)/2.0;
    gl_TexCoord[0].p = (1.0/(normX*normX + normY*normY + 1.0) + 1.0)/2.0;

    // modify GL_TexCoord[1] (for leafs) by mapping u,v coords to [0,1], so we 
    // can just lay leafs on top.
    gl_TexCoord[1].s = u/(2.0 * pi);
    gl_TexCoord[1].t = v/(2.0 * pi);
}
