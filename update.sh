#!/bin/bash
cd uppercase
for file in $(ls); do
    sed -i '' -e 's:(struct uc_program\* program, struct uc_datum_stack\* dstack, struct uc_char_stack\* cstack):(\n\tstruct uc_program\* program,\n\tstruct uc_datum_stack\* dstack,\n\tstruct uc_char_stack\* cstack,\n\tstruct uc_vartable* vtable):' $file
done

# (struct uc_program\* program, struct uc_datum_stack\* dstack, struct uc_char_stack\* cstack)
# 