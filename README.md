# Dependencies for OpenGL (GLFW3 and glad)

Among the general problems and frustrations with cross-platform construction of OpenGL applications is linking against the libraries in a flexible way.  GLFW3 and glad both offer CMakeLists within their repositories, and may thus be handled as a base for building applications (both for testing, and for real-world applications).

Note: This CMakeLists follows the defaults and just exposes them as a pair.  It's designed to be used to make life easier (e.g. I use it for rapidly dropping prototypes/tests together).  *You will probably want to switch to dynamic/shared compilation of GLFW, disable docs, tests, and examples if you don't need/want them.*

## Building

### Git

    # Fetch
    git clone https://github.com/awstanley/deps-glfw-glad
    cd deps-glfw-glad
    git submodule init
    git submodule update --remote --merge


### Setting up the build

    # Build out of the tree
    cd ..
    mkdir build-deps-glfw-glad # or whatever suits
    cd build-deps-glfw-glad
    cmake ../deps-glfw-glad

Then use your toolchain as normal.

## Updating

From within the project:

    git submodule update --remote --merge

If you are embedded within another project, the above command will work if it is a git repository.

## Use

As with my other deps projects, I've configured this to use some macro structures to make our lives easier.  

GLFW options are exposed; use them to determine shared/static.  glad lacks this support so there is no real reason to support triggering it here.

Other glfw and glad options should be tweaked as needed; as a part of the public release I'm not forcing anything here in this package.  (At one point I was.)

## Embedding

Embedding is trivial.  Directories are exported as `GLFW_DIRECTORY` and `GLAD_DIRECTORY`; libraries are exported as `GLFW_LIBRARY` and `GLAD_LIBRARY`.  Depending on your platform and configuration how this follows will vary; typically CMake will make it completely trivial (which is the intent here).

## Sample

The sample is a trivial GLFW3 sample using glad.  By default it is disabled but may be enabled using `DEPS_GLFW_GLAD_BUILDSAMPLE`.  It exists mostly how the library is linked (which is the same from a PARENT_SCOPE as it is from an included project).

## Licence

As I've been asked, consider this public domain (it's just a CMakeLists file!); licences for libraries used obviously vary, and at the time of writing they are both under the MIT.  (Check respective `LICENCE` or `COPYING` files).

If public domain isn't available for you (for whatever legal reason), consider this under MIT.