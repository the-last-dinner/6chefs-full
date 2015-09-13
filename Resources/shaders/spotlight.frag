varying vec4 v_fragmentColor;

uniform vec4 shadowColor;

void main()
{
    gl_FragColor = vec4(shadowColor.r, shadowColor.g, shadowColor.b, 1.0 - v_fragmentColor.a);
}
