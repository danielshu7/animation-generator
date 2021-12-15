import os
import sys

# read mega script
mega_script = sys.argv[1]
file_path = mega_script + ".txt"
text_file = open(file_path, "r")
contents = text_file.read()
text_file.close()



contents = contents.replace("screen 1024 1024", "screen 512 512")
text_file = open(file_path, "w")
text_file.write(contents)
text_file.close()
