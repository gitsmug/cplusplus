# Project directories that contain makefiles.
PROJ_DIRS := project1 project2

# Call make clean in specified project directories.
.PHONY: clean $(PROJ_DIRS)
clean: $(PROJ_DIRS)

$(PROJ_DIRS):
	$(MAKE) clean -C $@