main: blueCollectOriginal.cpp blueCollectSingleSole.cpp blueCollectBothSoles.cpp
		g++ -o originalSole blueCollectOriginal.cpp 
		g++ -o singleSole blueCollectSingleSole.cpp 
		g++ -o bothSoles blueCollectBothSoles.cpp
clean:
		rm -rf originalSole singleSole bothSoles

