#!/bin/bash

function update_char_stack {
	sed -i 's/_state(struct uc_program *program)/_state(struct uc_program *program, struct uc_char_stack *cstack)/g' $1
	sed -i 's/uc_char_stack_push(/uc_char_stack_push(cstack/g' $1
	sed -i 's/uc_char_stack_get_string(/uc_char_stack_get_string(cstack/g' $1
	sed -i 's/uc_char_stack_get_integer(/uc_char_stack_get_integer(cstack/g' $1
	sed -i 's/uc_char_stack_get_float(/uc_char_stack_get_float(cstack/g' $1
	sed -i 's/uc_char_stack_clear(/uc_char_stack_clear(cstack/g' $1
}

function update {
	update_char_stack $1
}

MODULES='data system math'
for module in $MODULES; do
	FILES=$(ls $module | grep -E '\.(h|c)');
	for file in $FILES; do
		update "$module/$file"
	done
done
