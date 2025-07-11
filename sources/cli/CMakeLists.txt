add_executable(${CLI_VERSION})

target_sources(${CLI_VERSION} PRIVATE
	"app_core-cli.cpp"
)

target_link_libraries(${CLI_VERSION} PRIVATE
	${PROJECT_NAME}
)

add_dependencies(${CLI_VERSION} ${PROJECT_NAME})