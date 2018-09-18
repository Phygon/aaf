# PATHS
ENV_PATH=$(pwd)
BUILD_PATH="$ENV_PATH/build"
OUTPUT_PATH="$ENV_PATH/bin"
SOURCE_PATH="$ENV_PATH"

# CLEANING
rm -rf $BUILD_PATH
rm -rf $OUTPUT_PATH

# BUILDING
mkdir -p $BUILD_PATH
mkdir -p $OUTPUT_PATH
pushd $BUILD_PATH
cmake -G "Xcode" "$SOURCE_PATH"
cmake --build . --target ALL_BUILD --config Release
popd
