# A python script to generate GLAPI.hpp and GLAPI.cpp files

import sys

HEADER_FNAME = "inc/Graphics/gl/GLAPI.hpp"
SRC_FNAME = "src/Graphics/gl/GLAPI.cpp"

glapiHeaderHDR =   ("#ifndef GLAPI_HPP\n"
                    "#define GLAPI_HPP\n"
                    "#include <GL/glext.h>\n\n"
                    )
glapiHeaderFTR =   "\n#endif //GLAPI_HPP\n"
glapiHeaderFunction = "extern %s %s;\n"
glapiSourceHDR = "#include <GL/gl.h>\n#include <GL/glext.h>\n#include <OS.hpp>\n#include <SDL2/SDL_video.h>\n\n"
glapiFuncPtr = "%s %s;\n"
# Makes 'PFNGLGENBUFFERSPROC' form 'glGenBuffers'
def makeProcTypeFromName(name):
    procType = "PFN" + name.upper() + "PROC"
    return procType

def makeLoadFunction(procs):
    function = "void GLAPI_load() {\n\n"
    stmt1 = "\t%s = (%s)SDL_GL_GetProcAddress(\"%s\");\n\n"
    stmt2 = "\tif(!%s)\n\t\t OS::get()->Log(\"[GLAPI_load()] Error getting address of %s\\n\");\n\n"
    for func in procs:
        func = func[:-1]
        function+= stmt1 % (func, makeProcTypeFromName(func), func)
        function+= stmt2 % (func, func)
    
    function += "}\n"
    print function
    return function

def writeHeader(lines):
    out = open(HEADER_FNAME, 'w')
    out.write(glapiHeaderHDR)
    for line in lines:
        line = line[:-1]
        ln = glapiHeaderFunction % (makeProcTypeFromName(line), line)
#        print ln
        out.write(ln)
    out.write(glapiHeaderFTR)
    out.close()

def writeSource(lines):
    out = open(SRC_FNAME, 'w')
    out.write(glapiSourceHDR);
    for line in lines:
        line = line[:-1]
        ln = glapiFuncPtr % (makeProcTypeFromName(line),line)
        out.write(ln)
    
    out.write("\n")
    out.write(makeLoadFunction(lines))
    out.close()

def main():
    if len(sys.argv)<2:
        print "To few arguments passed"
        sys.exit()
    try:
        inputFile = open(sys.argv[1], 'r')
    except IOError as e:
        print "Error opening "+sys.argv[1]
        sys.exit()
    
    glProcs = inputFile.readlines()
    writeHeader(glProcs)  
    writeSource(glProcs)

if __name__ == "__main__":
    main()
