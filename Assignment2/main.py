import re,sys


def removecomments(text):
    return re.sub('//.*?\n|/\*.*?\*/', '', text, flags=re.S|re.M)

def removestrings(text):
	return re.sub('\'.*?\'|\".*?\"', '', text, flags=re.S|re.M)

def count_lines():
	input_file  = open(sys.argv[1],"r")
	count=0
	for l in input_file:
			count+=1

	input_file.close()
	return count

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



def count_comments():
	with open(sys.argv[1]) as file:
		lines = []
		for line in file:
			line=removestrings(line)
			lines.append(line)
	
	comment_count=0
	flag=0		 		# indicates if a  /* comment is already present but has not ended 	
	new_lines=[] 		# list of all lines which are not a part of a multiline comment
	for line in lines:  # deals with all multiline comments 
		present=0		# indicates if a comment is beginning or ending on this line
		for i in range(len(line)-1, 0, -1):
			if line[i]=='/' and line[i-1]=='*':
				comment_count+=1
				present=1
				flag=0

				break
			elif line[i]=='*' and line[i-1]=='/':
				comment_count+=1
				present=1
				flag=1

				break
		
		if present==0 and flag==1:
			comment_count+=1
		if not (present==1 or (present==0 and flag==1)):
			new_lines.append(line)

	for line in new_lines:   #deals with all single line comments
		if(re.match('^.*\/\/',line)):
			comment_count+=1

	return comment_count


def count_variables():
	input_file  = open(sys.argv[1]).read()
	input_file=removestrings(input_file)
	input_file=removecomments(input_file)
	input_file = input_file.splitlines()
	
	pattern = re.compile(r'^\s*(auto\s*|const\s*|unsigned\s*|extern\s*|signed\s*|register\s*|volatile\s*|static\s*|void\s*|short\s*|long\s*|char\s*|int\s*|float\s*|double\s*|_Bool\s*|complex\s*|bool\s*)[\s\*]*([a-zA-Z_][a-zA-Z0-9_]*[\s\*]*)*\s*[\[;,=]')
	pattern2 = re.compile(r'^\s*(struct\s*|union\s*|enum\s*)([a-zA-Z_][a-zA-Z_0-9]*[\s\*]*)([a-zA-Z_][a-zA-Z_0-9]*[\s\*]*)*[=,;\[]')
	pattern3 = re.compile(r'[;\}]\s*(auto\s*|const\s*|unsigned\s*|extern\s*|signed\s*|register\s*|volatile\s*|static\s*|void\s*|short\s*|long\s*|char\s*|int\s*|float\s*|double\s*|_Bool\s*|complex\s*|bool\s*)[\s\*]*([a-zA-Z_][a-zA-Z0-9_]*[\s\*]*)*\s*[\[;,=]')
	pattern4 = re.compile(r'[;\}]\s*(struct\s*|union\s*|enum\s*)([a-zA-Z_][a-zA-Z_0-9]*[\s\*]*)([a-zA-Z_][a-zA-Z_0-9]*[\s\*]*)*[=,;\[]')
	pattern5 = re.compile(r'for[\ \t]*\([\ \t]*(auto\s*|const\s*|unsigned\s*|extern\s*|signed\s*|register\s*|volatile\s*|static\s*|void\s*|short\s*|long\s*|char\s*|int\s*|float\s*|double\s*|_Bool\s*|complex\s*|bool\s*)')
	
	count=0
	for l in input_file:
		if(re.match(pattern,l) or re.match(pattern2,l) or re.search(pattern3,l) or re.search(pattern4,l) or re.search(pattern5,l)):
			count+=1
		
	return count


def count_function_declarations():
	input_file  = open(sys.argv[1]).read()
	input_file=removestrings(input_file)
	input_file=removecomments(input_file)
	input_file = input_file.splitlines()
	lines = []
	for l in input_file:
		if(not re.match('^[\ \t]*#',l)):
			lines.append(l)
	f = "".join(lines)
	new_f = ""
	for elem in range(0,len(f)):
		new_f+=f[elem]
		if(f[elem]==';'):
			new_f += "\n"
		if(f[elem]=='}'):
			new_f+= "\n"
		if(f[elem]=='{'):
			new_f+= "\n"

	new_f = new_f.splitlines()
	pattern = re.compile(r'(([\t\ ]*[a-zA-Z_][a-zA-Z_0-9]*[\ \*]+?)([a-zA-Z_][a-zA-Z_0-9]*[\ \*]*?){1,}\(([^!@#$+%^;\{\}\/\-\=\<\>\|\&\[\:\]]*?)\)\s*?;)')
	count = 0
	for l in new_f:
		# print(l)
		flag = 0
		if(re.match(pattern,l)):
			if "return" in re.match(pattern,l).group().split(" "):
				flag = 1
			if(re.search(r'else\s+if', l)):
				flag = 1
			if(flag == 0):
				count+=1
	return count
	

def count_function_definitions():
	input_file  = open(sys.argv[1]).read()
	input_file=removestrings(input_file)
	input_file=removecomments(input_file)
	input_file = input_file.splitlines()
	f = "".join(input_file)
	pattern = re.compile(r'(([a-zA-Z_][a-zA-Z_0-9]*[\ \*]+?)([a-zA-Z_][a-zA-Z_0-9]*[\ \*]*?){1,}\(([^!@#$+%^;\{\}\/\-\=\<\>\|\&\[\:\]]*?)\)(?!\s*;))[\s]*{', re.MULTILINE|re.DOTALL)
	match_list = re.findall(pattern,f)
	count = 0
	for mt in match_list:
		if(not re.search(r'else\s+if', mt[0])):
			count+=1
	return count

def main():
	
	if len(sys.argv) != 3:
		print("Usage: python main.py <input_filename> <output_filename>", sys.stderr)
		exit()
	
	out_file = open(sys.argv[2],'w')
	
	number_of_lines = count_lines()

	number_of_blank_lines = count_blank_lines()

	number_of_macros = count_macro()

	total_comments = count_comments()

	number_variables = count_variables()

	number_of_func_def = count_function_definitions()

	number_of_func_declaration = count_function_declarations()

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
