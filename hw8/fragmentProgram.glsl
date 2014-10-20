uniform float t;
uniform float mode;
varying float u, v;

varying float vertexX;
varying float vertexY;

uniform sampler2D sky;
uniform sampler2D leaf;

const float pi = 3.1415926535;

void main()
{
  if (mode == 0.0) {
    // "Per-Vertex" mode. Here, we have already set the TexCoords in the vertex 
    // shader, so just set the color to be the interpolated value
    vec4 skyPerVertex = texture2D(sky, vec2(gl_TexCoord[0]));
    vec4 leafPerVertex = texture2D(leaf, vec2(gl_TexCoord[1]));

    // grab the alpha value of the leaf, and then blend
    float alpha = leafPerVertex.a; 
    vec4 blendResult = (alpha * leafPerVertex + (1.0-alpha) * skyPerVertex);

    gl_FragColor = blendResult;
  } else {
    // "Per-fragment" mode. Take the interpolated values for vertexX, vertexY 
    // calculate the normal here, and then set the color accordingly.
    float X = vertexX;
    float Y = vertexY;

    // Height for waves same as vertex mode: let f(x,y) = cos(x^2 + y^2 + 5t)
    // Then, Dx = 2xsin(x^2 + y^2 + 5t)
    // and , Dy = 2ysin(x^2 + y^2 + 5t)
    float sinTerm = 0.1 * sin(X * X + Y * Y + 5.0 * t);
    float normX = 2.0 * X * sinTerm;
    float normY = 2.0 * Y * sinTerm;

    // normalize the normal, and map to [0,1]
    float normalizedNormX = normX/sqrt(normX*normX + normY*normY + 1.0);
    float normalizedNormY = normY/sqrt(normX*normX + normY*normY + 1.0);
    vec4 sky = texture2D(sky, vec2((normalizedNormX + 1.0)/2.0, (normalizedNormY + 1.0)/2.0));

    // convert leaf TexCoords to range [0,1], so we can just lay leaves on top
    // note that u,v are interpolated between vertices
    vec4 leaf = texture2D(leaf, vec2(u/(2.0*pi), v/(2.0*pi)));

    // grab the alpha value from the leaves to blend
    float alpha = leaf.a;
    vec4 blend = (alpha * leaf + (1.0-alpha) * sky);
    gl_FragColor = blend;
  }
}
