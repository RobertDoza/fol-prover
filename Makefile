EXECUTABLE = test

$(EXECUTABLE): main.cpp
	g++ $< -o $@

.PHONY: clean

clean:
	rm -f *.o $(EXECUTABLE)

