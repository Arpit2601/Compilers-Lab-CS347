import re,sys


# output_file = open()

def count_lines():
	input_file  = open("input.txt","r")
	for i, l in enumerate(input_file):
		pass
	return i + 1

def count_blank_lines():
	input_file  = open("input.txt","r")
	count=0
	for l in input_file:
		if(l.isspace()):
			count+=1
	return count

def count_macro():
	input_file  = open("input.txt","r")
	count = 0
	for l in input_file:
		if(re.match('#[\ \\t]*define',l)):
			count+=1
	return count

def count_comments():
	input_file  = open("input.txt","r")

def count_variables():
	input_file  = open("input.txt","r")

def count_function_declarations():
	input_file  = open("input.txt","r")

def count_function_definitions():
	input_file  = open("input.txt","r")

def main():
	# number_of_lines = count_lines()
	# print(number_of_lines)

	# number_of_blank_lines = count_blank_lines()
	# print(number_of_blank_lines)

	number_of_macros = count_macro()
	print(number_of_macros)
if __name__  == "__main__":
	main()	