# Mother Fucker, this turns it into a static library whith a .a extension which has been working
# You include static libraries the same way, with the .h and link on compilation
# Thanks for explaining that fuckwads
add_executable(MakeTable MakeTable.cxx)


# add the command to generate the source code
add_custom_command (
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Table.h
  COMMAND MakeTable ${CMAKE_CURRENT_BINARY_DIR}/Table.h
  DEPENDS MakeTable
)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

# add the main library
add_library(MathFunctions mysqrt.cxx ${CMAKE_CURRENT_BINARY_DIR}/Table.h  )

# MathFunctions is defined above using mysqrt.css, we use that here
install (TARGETS MathFunctions DESTINATION "${MAKE_INSTALL_DIR}/include")

# THIS bullshit right here, means it's using the actual file, I needed to create it
# it may seem like a small thing but I was stuck on it for a while.
# It takes the file, MathFunctions.h and installs it into a dir, include
# but only when make install is called
# But you still have to manually create that file which the dumb fuck tutorial didn't mention
install (FILES MathFunctions.h DESTINATION "${MAKE_INSTALL_DIR}/include")