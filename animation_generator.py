import subprocess
import sys
import time

scripts_dir = sys.argv[1]
process1 = subprocess.Popen(["python3", "producerS.py", scripts_dir])
process2 = subprocess.Popen(["python3", "local_compiler.py"])
process3 = subprocess.Popen(["python3", "consumerG.py"])

process1.wait()
process2.wait()
process3.wait()








