# Compile new :

cmake ../GLImac-Template 
make && ./TP1/TP1_exo1_triangle_blanc
make && ./TP1/TP1_exo2_triangle_couleurs
make && ./TP1/TP1_exo3_structure_vertex
make && ./TP1/TP1_exo4_quad_draw
make && ./TP1/TP1_exo5_circle_draw
make && ./TP1/TP1_exo6_circle_ibo_draw

make && ./TP2/TP2_exo1_shaders
make && ./TP2/TP2_exo2_triangleGenerique grey2D.vs.glsl grey2D.fs.glsl
cmake ../GLImac-Template && make && ./TP2/TP2_exo2_triangleGenerique procedural.vs.glsl procedural.fs.glsl

cmake ../GLImac-Template && make && ./TP2/TP2_exo3_mandelbrot
cmake ../GLImac-Template && ./TP2/TP2_exo3_mandelbrot

cmake ../GLImac-Template && make && ./TP2/TP2_exo4

# Penser a commenter CMakeLists.txt