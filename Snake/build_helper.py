from sys import argv
from os import path, remove as rm_file
from shutil import copytree as copy_dir, copy as copy_file, rmtree as rm_dir


"""
Usage:

argv[1] = "$(SolutionDir)"
argv[2] = "$(TargetDir)"

"""


solution_dir = argv[1]
target_dir   = argv[2]

glfw_dll       = "glfw3.dll"
glfw_source    = path.join(solution_dir, "../glfw")
opengl_dll     = "opengl32.dll"
opengl_source  = path.join(solution_dir, "../opengl")
shaders_path   = "Shaders"
shaders_source = path.join(solution_dir, shaders_path)
shaders_target = path.join(target_dir, shaders_path)


def remove(_path: str) -> None:
    if path.isdir(_path):
        rm_dir(_path)
    elif path.exists(_path):
        rm_file(_path)
    

# copy/replace shaders
remove(shaders_target)
copy_dir(shaders_source, shaders_target)

# copy/replace glfw dll
remove(path.join(target_dir, glfw_dll))
copy_file(path.join(glfw_source, glfw_dll), path.join(target_dir, glfw_dll))

# may later also add opengl dll to build

