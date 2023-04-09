main : main.o camera.o program.o entity.o assets.o matrix_utils.o cutscenes.o arena.o player.o rect.o
		g++ -o main main.o camera.o program.o entity.o assets.o \
		matrix_utils.o cutscenes.o arena.o player.o rect.o \
		 -lX11 -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17

camera.o : ../src/camera.cpp ../src/camera.h ../src/matrix_utils.h ../src/program.h
		g++ -c ../src/camera.cpp
program.o : ../src/program.cpp ../src/program.h ../src/entity.h ../include/olcPixelGameEngine.h ../src/assets.h ../src/cutscenes.h \
			../src/arena.h
		g++ -c ../src/program.cpp
entity.o : ../src/entity.cpp ../src/entity.h ../include/olcPixelGameEngine.h ../src/program.h ../src/matrix_utils.h \
			../src/rect.h ../src/collision_utils.h
		g++ -c ../src/entity.cpp
main.o : ../src/main.cpp ../src/program.h ../src/camera.h
		g++ -c ../src/main.cpp
assets.o: ../src/assets.cpp ../src/assets.h ../include/olcPixelGameEngine.h
		g++ -c ../src/assets.cpp
matrix_utils.o: ../src/matrix_utils.cpp ../src/matrix_utils.h
		g++ -c ../src/matrix_utils.cpp
cutscenes.o: ../src/cutscenes.cpp ../src/cutscenes.h ../src/entity.h ../include/olcPixelGameEngine.h ../src/camera.h ../src/program.h
		g++ -c ../src/cutscenes.cpp
arena.o: ../src/arena.cpp ../src/arena.h ../src/entity.h ../include/olcPixelGameEngine.h ../src/player.h ../src/collision_utils.h
		g++ -c ../src/arena.cpp
player.o: ../src/player.cpp ../src/player.h ../src/entity.h ../src/program.h ../include/olcPixelGameEngine.h ../src/arena.h
		g++ -c ../src/player.cpp
rect.o: ../src/rect.cpp ../src/rect.h ../include/olcPixelGameEngine.h
		g++ -c ../src/rect.cpp
clean :
		rm main main.o camera.o program.o entity.o assets.o matrix_utils.o cutscenes.o arena.o player.o rect.o
