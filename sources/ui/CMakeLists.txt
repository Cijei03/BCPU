add_executable(${UI_VERSION})

target_sources(${UI_VERSION} PRIVATE
	"app_core-ui.cpp"
)

target_link_libraries(${UI_VERSION} PRIVATE
	${PROJECT_NAME}
	SDL3
)

add_dependencies(${UI_VERSION} ${PROJECT_NAME})