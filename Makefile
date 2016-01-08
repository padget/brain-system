.PHONY: clean All

All:
	@echo "----------Building project:[ brain - Debug ]----------"
	@"$(MAKE)" -f  "brain.mk"
clean:
	@echo "----------Cleaning project:[ brain - Debug ]----------"
	@"$(MAKE)" -f  "brain.mk" clean
