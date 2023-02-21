file(GLOB SOURCE_FILES "*.cpp")
file(GLOB HEADER_FILES "*.h")

add_executable(whysko ${SOURCE_FILES} ${HEADER_FILES})
