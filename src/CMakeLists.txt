file(GLOB SOURCE_FILES "*.cpp")
file(GLOB HEADER_FILES "*.h")

file(GLOB ACTORS_SOURCE_FILES "entities/*.cpp")
file(GLOB ACTORS_HEADER_FILES "entities/*.h")

file(GLOB ENGINE_SOURCE_FILES "engine/*.cpp")
file(GLOB ENGINE_HEADER_FILES "engine/*.h")

file(GLOB SCENES_SOURCE_FILES "scenes/*.cpp")
file(GLOB SCENES_HEADER_FILES "scenes/*.h")

file(GLOB WORLD_SOURCE_FILES "world/*.cpp")
file(GLOB WORLD_HEADER_FILES "world/*.h")


add_executable(whysko
        ${SOURCE_FILES} ${HEADER_FILES}
        ${ACTORS_SOURCE_FILES} ${ACTORS_HEADER_FILES}
        ${ENGINE_SOURCE_FILES} ${ENGINE_HEADER_FILES}
        ${SCENES_SOURCE_FILES} ${SCENES_HEADER_FILES}
        ${WORLD_SOURCE_FILES} ${WORLD_HEADER_FILES})
