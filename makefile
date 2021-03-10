main: main.cpp Skybox.o JPGTools.o Hittable.o ChequeredPlane.o ProgressBar.o PPMtools.o Light.o Renderer.o Ray.o Camera.o Matrix.o Vector.o Sphere.o Material.o Collision.o
	g++ main.cpp Skybox.o JPGTools.o Hittable.o ChequeredPlane.o ProgressBar.o PPMtools.o Light.o Renderer.o Ray.o Camera.o Matrix.o Vector.o Sphere.o Material.o Collision.o -o main

Skybox.o: Skybox.cpp
	g++ Skybox.cpp -c

ChequeredPlane.o: ChequeredPlane.cpp
	g++ ChequeredPlane.cpp -c

Ray.o: Ray.cpp
	g++ Ray.cpp -c

Vector.o: Vector.cpp
	g++ Vector.cpp -c

Matrix.o: Matrix.cpp
	g++ Matrix.cpp -c

PPMtools.o: PPMtools.cpp
	g++ PPMtools.cpp -c

JPGTools.o: JPGTools.cpp
	g++ JPGTools.cpp -c

Sphere.o: Sphere.cpp
	g++ Sphere.cpp -c

Camera.o: Camera.cpp
	g++ Camera.cpp -c

Renderer.o: Renderer.cpp
	g++ Renderer.cpp -c

Light.o: Light.cpp
	g++ Light.cpp -c

Material.o: Material.cpp
	g++ Material.cpp -c

Hittable.o: Hittable.cpp
	g++ Hittable.cpp -c

ProgressBar.o: ProgressBar.cpp
	g++ ProgressBar.cpp -c

Collision.o: Collision.cpp
	g++ Collision.cpp -c

clean:
	rm *.o
