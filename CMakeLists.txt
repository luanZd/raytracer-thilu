# 1. Versão mínima e Nome do Projeto
cmake_minimum_required(VERSION 3.10)
project(RayTracer_Thilu VERSION 1.0 DESCRIPTION "PBRT-style Ray Tracer" LANGUAGES CXX)

# 2. Exigir C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 3. Mapear TODOS os ficheiros .cpp com base na tua árvore de diretórios
set(SOURCES
    src/main.cpp
    
    # As implementações das tuas classes
    include/class/background.cpp
    include/class/film.cpp
    include/class/param.cpp
    include/class/parser.cpp
    include/class/util.cpp
    
    # A implementação do Pugixml
    ext/pugixml/src/pugixml.cpp
)

# 4. Criar o nosso programa final chamado "rt3"
add_executable(rt3 ${SOURCES})

# 5. Dizer ao compilador onde encontrar os ficheiros de cabeçalho (.hpp)
target_include_directories(rt3 PRIVATE
    ${CMAKE_SOURCE_DIR}/include        # Para encontrares os teus .hpp
    ${CMAKE_SOURCE_DIR}/ext            # Para encontrares o <glm/glm.hpp>
    ${CMAKE_SOURCE_DIR}/ext/pugixml/src # Para encontrares o "pugixml.hpp"
)