import re,sys


def removecomments(text):
    return re.sub('//.*?\n|/\*.*?\*/', '', text, flags=re.S|re.M)

def removestrings(text):
	return re.sub('\'.*?\'|\".*?\"', '', text, flags=re.S|re.M)

# keyword = ['else','goto','return','typedef']
def count_lines():
	input_file  = open(sys.argv[1],"r")
	for i, l in enumerate(input_file):
		pass
	
	input_file.close()
	return i + 1

def count_blank_lines():
	input_file  = open(sys.argv[1],"r")
	count=0
	for l in input_file:
		if(l.isspace()):
			count+=1
	
	input_file.close()
	return count

def count_macro():
	input_file  = open(sys.argv[1],"r")
	count = 0
	for l in input_file:
		if(re.match('^[\ \t]*#[\ \t]*define',l)):
			count+=1
	
	input_file.close()
	return count

def count_comments_type1():
	input_file  = open(sys.argv[1],"r")
	count = 0
	for l in input_file:
		if(re.match('^.*?//',l)):
			count+=1
	input_file.close()
	return count

def count_comments_type2():
	input_file  = open(sys.argv[1],"r")
	count  = 0
	for l in input_file:
		if(re.match('^.*?//.*\/\*',l)):
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
	input_file.close()
	return count

def count_variables():
	input_file  = open(sys.argv[1]).read()
	input_file=removestrings(input_file)
	input_file=removecomments(input_file)
	input_file = input_file.splitlines()
	# print (input_file)
	count=0
	for l in input_file:
		if(re.match('^.*(auto\s*|const\s*|unsigned\s*|extern\s*|signed\s*|register\s*|volatile\s*|static\s*|void\s*|short\s*|long\s*|char\s*|int\s*|float\s*|double\s*|_Bool\s*|complex\s*)(\s+\*?\*?\s*)([a-zA-Z_][a-zA-Z0-9_]*)\s*[\[;,=)]',l)):
			count+=1
	return count


def count_function_declarations():
	input_file  = open(sys.argv[1]).read()
	input_file=removestrings(input_file)
	input_file=removecomments(input_file)
	input_file = input_file.splitlines()
	f = "".join(input_file)

	pattern = re.compile(r'(([a-zA-Z_][a-zA-Z_0-9]*[\ \*]*?){2,}\(([^!@#$+%^;\{\}]*?)\)\s*?;)', re.MULTILINE| re.DOTALL)
	pattern2 = re.compile(r'((=\s*[a-zA-Z_][a-zA-Z_0-9]*[\ \*]*?){1,}\(([^!@#$+%^;\{\}]*?)\)\s*?;)', re.MULTILINE| re.DOTALL)
	
	return len(re.findall(pattern, f)) - len(re.findall(pattern2, f))
	

def count_function_definitions():
	input_file  = open(sys.argv[1]).read()
	input_file=removestrings(input_file)
	input_file=removecomments(input_file)
	input_file = input_file.splitlines()
	f = "".join(input_file)
	pattern = re.compile(r'(([a-zA-Z_][a-zA-Z_0-9]*[\ \*]*?){2,}\(([^!@#$+%^;{}]*?)\)(?!\s*;))[\s]*{', re.MULTILINE|re.DOTALL)
	

	return len(re.findall(pattern, f))
	
	
def main():
	
	if len(sys.argv) != 3:
		print("Usage: python main.py <input_filename> <output_filename>", file=sys.stderr)
		exit()
	
	out_file = open(sys.argv[2],'w')
	
	number_of_lines = count_lines()
	# print(number_of_lines)

	number_of_blank_lines = count_blank_lines()
	# print(number_of_blank_lines)

	number_of_macros = count_macro()
	# print(number_of_macros)

	number_of_comments1 = count_comments_type1()
	# print(number_of_comments1)

	number_of_comments2 = count_comments_type2()
	# print(number_of_comments2)

	total_comments = number_of_comments1+number_of_comments2

	number_variables = count_variables()
	# print(number_variables)

	number_of_func_def = count_function_definitions()
	# print(number_of_func_def)

	number_of_func_declaration = count_function_declarations()
	# print(number_of_func_declaration)

	out_file.write("1) Source code statements : " + str(number_of_lines) + "\n")
	out_file.write("2) Comments               : " + str(total_comments) + "\n")
	out_file.write("3) Blank Lines            : " + str(number_of_blank_lines) + "\n")
	out_file.write("4) Macro Definitions      : " + str(number_of_macros) + "\n")
	out_file.write("5) Variable Declarations  : " + str(number_variables) + "\n")
	out_file.write("6) Function Declarations  : " + str(number_of_func_declaration) + "\n")
	out_file.write("7) Function Definitions   : " + str(number_of_func_def))
	out_file.close()

if __name__  == "__main__":
	main()	