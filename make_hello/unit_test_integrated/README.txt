Explore make, makefile composition, and project structure.

Test stucture:  A disadvantage in how the test structure is set up is that we
could accidentally make compiler options, etc. different in makefile and makefile_tests.
If that happened we could potentially be running tests against something that wasn't
built for release and end up releasing what would technically be an untested release
build.  Oops!

There's also the mess of using preprocessor stuff to ensure there's only one main() when
there's no separate driver project for the release code.

We might be able to protect against an accident like that by always building a lib/module
and testing against that.  For example, the master makefile that builds the release candidate
would build a lib. Building the test stuff would call the master makefile, then its own test
stuff to link to it. To do something like that there may have to be another project to act
as a dev driver for the release code.

gcc-based library creation:
https://renenyffenegger.ch/notes/development/languages/C-C-plus-plus/GCC/create-libraries/index