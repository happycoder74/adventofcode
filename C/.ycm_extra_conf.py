import subprocess

glib_flags = subprocess.check_output(["pkg-config", "--cflags", "glib-2.0"])
glib_flags = glib_flags.decode('utf-8').strip().split()

cflags = [
            "-x",
            "c",
            "-Wall",
            "-Wextra",
            "-Werror",
            "-I./include",
            "-isystem/usr/include",
            "-isystem/usr/local/include"
        ]

flags = cflags + glib_flags


def Settings(**kwargs):
    return {
        "flags": flags
    }
