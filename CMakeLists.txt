cmake_minimum_required(VERSION 3.14)
cmake_policy(VERSION 3.14)

project("biztonsag"
    LANGUAGES
        CXX
    VERSION
        0.1.0
)

include(GNUInstallDirs)

set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
include(CPack)

option(BIZTONSAG_BUILD_TESTS "Build optional tests (requires GTest)" ON)
option(BIZTONSAG_BUILD_DOCS "Build documentation (requires doxygen)" ON)

enable_testing()

if(BIZTONSAG_BUILD_TESTS)
    if(NOT BIZTONSAG_MAXIMUM_TEST_STANDARD)
        set(BIZTONSAG_MAXIMUM_TEST_STANDARD 17
            CACHE STRING "The maximum C++ standard to use for tests (default: 17)"
        )
    endif()

    foreach(supported_version IN ITEMS 14 17 20)
        if(${supported_version} LESS_EQUAL ${BIZTONSAG_MAXIMUM_TEST_STANDARD})
            message(STATUS "Enabling C++${supported_version} tests")
            list(APPEND test_standards ${supported_version})
        endif()
    endforeach()

    if(NOT test_standards)
        message(WARNING "No supported standards for tests")
    endif()

    find_package(GTest CONFIG REQUIRED)
    function(create_test_std name std_version)
        set(real_name "${name}_${std_version}")
        add_executable(${real_name} ${ARGN})
        target_link_libraries(${real_name}
            GTest::gtest
            GTest::gtest_main
            biztonsag
        )
        set_target_properties(${real_name} PROPERTIES
            CXX_EXTENSIONS OFF
        )
        target_compile_features(${real_name} PRIVATE
            cxx_std_${std_version}
        )
        add_test(${real_name} ${real_name} "--gtest_output=xml:${CMAKE_CURRENT_BINARY_DIR}/${real_name}_results.xml")
    endfunction()

    function(create_test name)
        foreach(std_version IN LISTS test_standards)
            create_test_std(${name} ${std_version} ${ARGN})
        endforeach()
    endfunction()
else()
    function(create_test name)
        #do nothing
    endfunction()
endif()

add_library(biztonsag INTERFACE)
target_include_directories(biztonsag
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_compile_features(biztonsag
    INTERFACE
        cxx_std_14
)

function(add_headers)
    foreach(target
        biztonsag
    )
        foreach(header IN LISTS ARGN)
            set(full_header_path "${CMAKE_CURRENT_SOURCE_DIR}/include/biztonsag/${header}")
            list(APPEND all_headers ${full_header_path})
            target_sources(${target}
                INTERFACE
                    $<BUILD_INTERFACE:${full_header_path}>
                    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/biztonsag/${header}>
            )
        endforeach()
    endforeach()
    install(FILES ${all_headers}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/biztonsag
        COMPONENT ${devComponent}
    )
endfunction()

add_subdirectory(examples)
add_subdirectory(test)

add_headers(
    arithmetic.hpp
    bitop.hpp
    comparable.hpp
    create_macro.hpp
    incr.hpp
    logical.hpp
    orderable.hpp
    traits.hpp
    wrapped.hpp
)

if(BIZTONSAG_BUILD_DOCS)
    find_program(DOXYGEN "doxygen")
    if(DOXYGEN)
        message(STATUS "doxygen location: ${DOXYGEN}")
        find_program(DOT "dot")
        if(DOT)
            message(STATUS "dot location: ${DOT}")
            set(HAVE_DOT "YES")
        else()
            set(HAVE_DOT "NO")
        endif()
        configure_file(doxyfile.in "${CMAKE_CURRENT_BINARY_DIR}/doxyfile" @ONLY)

        add_custom_target(docs)
        add_custom_command(TARGET docs
            COMMAND "${DOXYGEN}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        )
        install(DIRECTORY
                    "${CMAKE_CURRENT_BINARY_DIR}/doc/html"
            DESTINATION ${CMAKE_INSTALL_DOCDIR}
        )
    else()
        message(WARNING "Couldn't find doxygen, disabling documentation")
    endif()
endif()

install(TARGETS
        biztonsag
    EXPORT BiztonsagConfig
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

export(TARGETS
        biztonsag
    NAMESPACE Bitzonsag::
    FILE "${CMAKE_CURRENT_BINARY_DIR}/BiztonsagConfig.cmake"
)
install(EXPORT
        BiztonsagConfig
    DESTINATION "${CMAKE_INSTALL_DATADIR}/Biztonsag/cmake"
    NAMESPACE Bitzonsag::
)
install(FILES
        COPYING
    DESTINATION ${CMAKE_INSTALL_DOCDIR}
)
