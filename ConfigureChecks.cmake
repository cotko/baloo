include(CheckIncludeFile)
include(CheckIncludeFiles)
include(CheckSymbolExists)

# Look for extended attributes headers to verify there is support for it in at
# least some file systems supported by the operating system. We currently
# assume the functionality is in libc itself.

# Linux and OS X.
check_include_files("sys/types.h;sys/xattr.h" HAVE_SYS_XATTR_H)

# DragonFly BSD, FreeBSD and NetBSD.
check_include_files("sys/types.h;sys/extattr.h" HAVE_SYS_EXTATTR_H)

if (NOT (HAVE_SYS_XATTR_H OR HAVE_SYS_EXTATTR_H))
    message(FATAL_ERROR "Baloo requires extended attributes support in the operating system, but no headers have been found.")
endif ()

# Check whether malloc_trim(3) is supported.
check_include_file("malloc.h" HAVE_MALLOC_H)
check_symbol_exists(malloc_trim "malloc.h" HAVE_MALLOC_TRIM)
