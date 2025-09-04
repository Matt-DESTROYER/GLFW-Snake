BUILD_TYPE="Release"

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
	-DGLFW_INCLUDE_DIR=./glfw/install/include \
	-DGLFW_LIB_DIR=./glfw/install/lib \
	# -A x64 # for Windows

# build Snake
cmake --build ./Snake/build \
	--config $BUILD_TYPE \
	--target Snake
