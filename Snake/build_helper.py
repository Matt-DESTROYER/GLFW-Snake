from sys import argv
from os import path, remove as rm_file, listdir as list_dir
from shutil import copytree as copy_dir, copy as copy_file, rmtree as rm_dir


"""
Usage:

argv[1] = "$(SolutionDir)"
argv[2] = "$(TargetDir)"

"""


solution_dir: str   = argv[1]
target_dir: str     = argv[2]

shaders_path: str   = "./Shaders"
shaders_source: str = path.join(solution_dir, shaders_path)
shaders_target: str = path.join(target_dir, shaders_path)

assets_path: str    = "./Assets"
assets_source: str  = path.join(solution_dir, assets_path)
assets_target: str  = path.join(target_dir, assets_path)


def remove(_path: str) -> None:
    """
    Delete a file or folder if it exists.
    """
    if path.isdir(_path):
        rm_dir(_path)
    elif path.exists(_path):
        rm_file(_path)
    

def copy_or_replace(source: str, target: str) -> None:
    """
    Copies a folder or file to target destination, removing
    any pre-existing folder with the same name.
    """
    remove(target)
    copy_dir(source, target)


# remove build artifacts
AUTO_REMOVE_EXTENSIONS = (".lib", ".exp")
for file in list_dir(target_dir):
    if path.isfile(file):
        print(f"Found file: {file}")
        if any(file.endswith(extension)\
           for extension in AUTO_REMOVE_EXTENSIONS):
            remove(file)

# copy/replace shaders and assets
copy_or_replace(shaders_source, shaders_target)
copy_or_replace(assets_source, assets_target)

