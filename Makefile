OBJS = Main.o SFApp.o SFBoundingBox.o SFEvent.o SFAsset.o
CC = g++ -std=c++11
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

all: SuperSub

SuperSub: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o SuperSub -lSDL -lSDL_image

Main.o: ./src/SFCommon.h ./src/Main.cpp ./src/SFApp.h ./src/SFMath.h
	$(CC) $(CFLAGS) ./src/Main.cpp

SFApp.o:  ./src/SFApp.h ./src/SFApp.cpp ./src/SFCommon.h ./src/SFEvent.h
	$(CC) $(CFLAGS) ./src/SFApp.cpp

SFEvent.o: ./src/SFEvent.h ./src/SFEvent.cpp
	$(CC) $(CFLAGS) ./src/SFEvent.cpp

SFAsset.o: ./src/SFAsset.h ./src/SFAsset.cpp ./src/SFCommon.h ./src/SFEvent.h ./src/SFBoundingBox.h
	$(CC) $(CFLAGS) ./src/SFAsset.cpp

SFBoundingBox.o: ./src/SFBoundingBox.h ./src/SFBoundingBox.cpp ./src/SFMath.h
	$(CC) $(CFLAGS) ./src/SFApp.cpp

clean:
	rm -rf *.o
