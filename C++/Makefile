.PHONY: clean-build clean-debug release debug

all: release

release:
	cmake -S . -B build -G Ninja -D CMAKE_EXPORT_COMPILE_COMMANDS=1 -D CMAKE_BUILD_TYPE=Release
	ninja -C build

debug:
	cmake -S . -B debug -G Ninja -D CMAKE_EXPORT_COMPILE_COMMANDS=1 -D CMAKE_BUILD_TYPE=RelWithDebInfo
	ninja -C build

release-library:
	cmake -S . -B build -G Ninja -D CMAKE_EXPORT_COMPILE_COMMANDS=1 -D CMAKE_BUILD_TYPE=Release
	ninja -C build aoc++

debug-library:
	cmake -S . -B debug -G Ninja -D CMAKE_EXPORT_COMPILE_COMMANDS=1 -D CMAKE_BUILD_TYPE=RelWithDebInfo
	ninja -C debug aoc++

clean-build:
	rm -rf build

clean-debug:
	rm -rf debug

clean-all: clean-debug clean-build
