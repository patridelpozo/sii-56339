CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT (TENIS)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)

SET(COMMON_SRCS
    src/Esfera.cpp
    src/Plano.cpp
    src/Raqueta.cpp
    src/Vector2D.cpp
)

#Ejecutable del Servidor
ADD_EXECUTABLE(servidor src/servidor.cpp src/MundoServidor.cpp ${COMMON_SRCS})

TARGET_LINK_LIBRARIES(servidor glut GL GLU pthread)

#Ejecutable del Cliente
ADD_EXECUTABLE(cliente src/cliente.cpp src/MundoCliente.cpp ${COMMON_SRCS})

TARGET_LINK_LIBRARIES(cliente glut GL GLU)



ADD_EXECUTABLE(logger src/logger.cpp)

ADD_EXECUTABLE(bot src/bot.cpp src/Esfera.cpp src/Raqueta.cpp src/Plano.cpp src/Vector2D.cpp)
TARGET_LINK_LIBRARIES(bot GL GLU glut pthread)
