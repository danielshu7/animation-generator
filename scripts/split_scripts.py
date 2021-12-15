import os
import sys

# read mega script
mega_script = sys.argv[1]
file_path = mega_script + ".txt"
text_file = open(file_path, "r")
contents = text_file.read()
text_file.close()

path = os.getcwd() + "/" + mega_script
if not os.path.exists(path):
    os.mkdir(path)

script_list = contents.split("##########")
num = 0
for script in script_list:
    if num <= 25:
        new_file = open(path + "/" + chr(ord('a')+num) + ".txt", "w")
    elif num <= 51:
        new_file = open(path + "/z" + chr(ord('a') + num % 26) + ".txt", "w")
    else:
        print("Too many scripts")
        break
    new_file.write(script)
    new_file.close()
    num += 1
