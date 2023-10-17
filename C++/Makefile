all: release

release:
	cmake -S . -B build -G Ninja -D CMAKE_EXPORT_COMPILE_COMMANDS=1 -D CMAKE_BUILD_TYPE=Release
	cd build && ninja

debug:
	cmake -S . -B debug -G Ninja -D CMAKE_EXPORT_COMPILE_COMMANDS=1 -D CMAKE_BUILD_TYPE=RelWithDebInfo
	cd debug && ninja

clean:
	rm -rf build debug
