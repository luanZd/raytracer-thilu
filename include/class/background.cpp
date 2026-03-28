#include "../background.hpp" 

Background::Background(const std::vector<Color>& colors) {
    if (colors.size() == 4) {
        corners[bl] = colors[0];
        corners[tl] = colors[1];
        corners[tr] = colors[2];
        corners[br] = colors[3];
    }
}

Color Background::lerp(const Color &A, const Color &B, float t) const {
    Color resultado;
    
    resultado.r = A.r * (1.0f - t) + B.r * t;
    
    resultado.g = A.g * (1.0f - t) + B.g * t;
    
    resultado.b = A.b * (1.0f - t) + B.b * t;
    
    return resultado;
}

Color Background::sampleUV(float u, float v) const {
    
    // Passo 1: Interpolação na linha de baixo (Horizontal - eixo U)
    // Mistura o canto Inferior-Esquerdo com o Inferior-Direito
    Color cor_baixo = lerp(corners[bl], corners[br], u);
    
    // Passo 2: Interpolação na linha de cima (Horizontal - eixo U)
    // Mistura o canto Superior-Esquerdo com o Superior-Direito
    Color cor_cima = lerp(corners[tl], corners[tr], u);
    
    // Passo 3: Interpolação final (Vertical - eixo V)
    // Mistura o resultado de baixo com o resultado de cima!
    Color cor_final = lerp(cor_baixo, cor_cima, v);
    
    return cor_final;
}