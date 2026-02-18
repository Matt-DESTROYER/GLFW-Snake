BUILD_TYPE="Release"
PROJECT_ROOT=$(pwd)

# configure GLFW
cmake -S ./glfw -B ./glfw/build \
	-DCMAKE_BUILD_TYPE=$BUILD_TYPE \
	-DCMAKE_INSTALL_PREFIX=./glfw/install \
	-DBUILD_SHARED_LIBS=OFF \
	-DGLFW_BUILD_EXAMPLES=OFF \
	-DGLFW_BUILD_TESTS=OFF \
	-DGLFW_BUILD_DOCS=OFF \
	-DGLFW_INSTALL=ON \
	# -A x64 # for Windows

# build and install GLFW
cmake --build ./glfw/build --config $BUILD_TYPE
cmake --install ./glfw/build --config $BUILD_TYPE

# configure Snake
cmake -S ./Snake -B ./Snake/build \
	-DCMAKE_BUILD_TYPE=$BUILD_TYPE \
	-DGLFW_INCLUDE_DIR="$PROJECT_ROOT/glfw/install/include" \
	-DGLFW_LIB_DIR="$PROJECT_ROOT/glfw/install/lib" \
	# -A x64 # for Windows

# build Snake
cmake --build ./Snake/build \
	--config $BUILD_TYPE \
	--target Snake

cp -r Snake/Assets/ Snake/build/
cp -r Snake/Shaders/ Snake/build/

cd Snake/build/

zip Snake.zip Snake Assets/ Shaders/
