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
		if(re.match('[ \\t]#[ \\t]*define',l)):
			count+=1
	return count

def count_comments_type1():
	input_file  = open("input.txt","r")
	count = 0
	for l in input_file:
		if(re.match('^.*//',l)):
			count+=1
	return count
def count_comments_type2():
	input_file  = open("input.txt","r")
	count  = 0
	for l in input_file:
		if(re.match('^.*?//.*\/\*',l)
			continue
		if(re.match('^.*?\/\*',l)):
			count+=1
			if(re.match('^.*?\/\*.*\*\/',l)):
				continue
			for l2 in input_file:
				if(re.match('^.*?//',l2)):
					count-=1
				if(re.match('^.*?\*\/',l2)):
					count+=1
					break
				if(re.match('^.*//',l2)):
					count = count
				else:
					count+=1
	return count

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

	# number_of_macros = count_macro()
	# print(number_of_macros)

	number_of_comments1 = count_comments_type1()
	print(number_of_comments1)

	number_of_comments2 = count_comments_type2()
	print(number_of_comments2)

if __name__  == "__main__":
	main()	