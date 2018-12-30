Explore make, makefile composition, and project structure.

Default makefile builds static-linkable lib of src.  makefile_tests builds unit test driver and
statically-links it against the output from src. This seems pretty good, but I'm going to
explore separating the stuff represented by dirs src and test into their own "project" dirs
like I'm used to in a Visual Studio domain of thinking.

gcc-based library creation:
https://renenyffenegger.ch/notes/development/languages/C-C-plus-plus/GCC/create-libraries/index